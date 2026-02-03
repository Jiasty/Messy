#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <exception>
#include <thread>

#include <string>


double Division(int a, int b)
{
	// 当b == 0时抛出异常
	if (b == 0)
	{
		// 异常对象
		std::string err("type:string  Division by zero condition!");
		// throw "Division by zero condition!";  
		throw err; // e是局部对象，抛出的是e的拷贝
	}
	else
		return ((double)a / (double)b);
}
void Func()
{
	try
	{
		int len, time;
		std::cin >> len >> time;
		std::cout << Division(len, time) << std::endl;
	}
	catch (const std::string& errmsg)
	{
		std::cout << "***********" << std::endl; // 捕获的就近原则
		std::cout << errmsg << std::endl;
	}
	catch (...)
	{
		std::cout << "unkown exception" << std::endl;
	}
}

void test1()
{
	bool flag = true;
	while (flag)
	{
		try
		{
			Func();
		}
		catch (const char* errmsg)
		{
			std::cout << errmsg << std::endl;
		}
		catch (const std::string& errmsg)
		{
			std::cout << errmsg << std::endl;
		}
		catch (...) // 捕获任意类型异常
		{
			std::cout << "unkown exception" << std::endl;
		}
	}
}

/////////////////////////////////

// 抛出派生类对象，用基类捕获
class Exception
{
public:
	Exception(const std::string& errmsg, int id)
		:_ErrorMessage(errmsg)
		,_id(id)
	{}

	virtual std::string what() const  // TOLEARN
	{
		return _ErrorMessage;
	}


protected:
	std::string _ErrorMessage;
	int _id;
};

class SqlException : public Exception  // TOLEARN
{
public:
	SqlException(const std::string& errmsg, int id, const std::string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}
	virtual std::string what() const
	{
		std::string str = "SqlException:";
		str += _ErrorMessage;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const std::string _sql;
};

class CacheException : public Exception
{
public:
	CacheException(const std::string& errmsg, int id)
		:Exception(errmsg, id)
	{}
	virtual std::string what() const
	{
		std::string str = "CacheException:";
		str += _ErrorMessage;
		return str;
	}
};

class HttpServerException : public Exception
{
public:
	HttpServerException(const std::string& errmsg, int id, const std::string& type)
		:Exception(errmsg, id)
		, _type(type)
	{}
	virtual std::string what() const
	{
		std::string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _ErrorMessage;
		return str;
	}
private:
	const std::string _type;
};

void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}
	//throw "xxxxxx";
}

void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}
	CacheMgr();
}


void test2()
{
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		try {
			HttpServer();
		}
		catch (const Exception& e) // 这里捕获父类对象就可以
		{
			// 多态
			std::cout << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Unkown Exception" << std::endl;
		}
	}
}


// 多层异常控制(控制流)

int div()
{
	int a, b;
	std::cin >> a >> b;
	if (b == 0)
		throw std::invalid_argument("除0错误");
	return a / b;
}

void Func()
{
	// 1、如果p1这里new 抛异常会如何？
	// 2、如果p2这里new 抛异常会如何？
	// 3、如果div调用这里又会抛异常会如何？
	// int* p1 = new int[];
	// int* p2 = new int[];
	// std::cout << div() << std::endl;
	// delete[] p1;
	// delete[] p2;

	// [步骤 1] 分配 p1 成功 (假设地址 0x100)
	int* p1 = new int[10];
	int* p2 = nullptr;
	try
	{
		// [步骤 2] 尝试分配 p2... 失败！抛出 std::bad_alloc 异常
		// 注意：一旦这里抛出异常，CPU 立即停止顺序执行
		// 不会进入内层的 try，也不会执行内层的 catch
		// @@@而是直接寻找最近的匹配的 catch 块@@@
		p2 = new int[10];

		// ... (中间这一大坨代码全部被跳过) ...
		try
		{
			std::cout << div() << std::endl;
		}
		catch (...)
		{
			// div()可能抛异常，p1和p2都申请了资源，得释放
			delete[] p1;
			p1 = nullptr; // 置空防止外层catch双重释放p1 ！！！
			std::cout << "delete[] p1" << std::endl;
			delete[] p2;
			p2 = nullptr;
			std::cout << "delete[] p2" << std::endl;
			throw;
		}
	}
	catch (...) // [步骤 3] 捕获到 p2 分配失败的异常
	{
		// [步骤 4] 执行清理
		delete[] p1; // p2抛异常，p1已申请资源，不释放则资源泄露
		p1 = nullptr;
		std::cout << "delete[] p1" << std::endl;

		// [步骤 5] 再次抛出异常！
		// 关键点：这一行代码执行瞬间，Func 函数宣告“死亡”！
		// 控制流直接飞出 Func 函数，飞回到调用 Func() 的地方（比如 main 函数）。
		throw;
	}

	// ==========================================
	// 下面是“死亡区域” (Unreachable Code)
	// 因为上面的 throw 已经把函数终结了，
	// 所以在 p2 失败的这个分支里，CPU 永远走不到这里！
	// ==========================================

	delete[] p1;
	std::cout << "delete[] p1" << std::endl;
	delete[] p2;
	std::cout << "delete[] p2" << std::endl;
}
void test3()
{
	try
	{
		Func();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


int main()
{
	// test1();
	// test2();
	test3();


	return 0;
}