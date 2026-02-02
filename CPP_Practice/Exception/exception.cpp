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

int main()
{
	// test1();
	test2();


	return 0;
}