#pragma once
#include <atomic>
#include <functional>

namespace Jiasty
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			,_count(new std::atomic<int>(1))
		{}

		// 定制删除器  // TODO
		template<class D>
		shared_ptr(T* ptr, D del)
			: _ptr(ptr)
			, _count(new std::atomic<int>(1))
			,_del(del)
		{}

		~shared_ptr()
		{
			release();
		}

		// p2(p1)
		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _count(sp._count)
		{
			++(*_count);
		}

		// p2 = p1
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr) // 防止自己给自己赋值造成野指针
			{
				this->release();

				_ptr = sp._ptr;
				_count = sp._count;
				++(*_count);
			}

			return *this;
		}

		//让智能指针“伪装”成裸指针，让用户用起来感觉和用普通指针一样。
		T& operator*() const
		{
			return *_ptr;
		}

		T* operator->() const
		{
			return _ptr;
		}

		// 脱离当前指向的资源
		void release()
		{
			// 最后一个管理的对象，负责释放资源
			if (--(*_count) == 0)
			{
				// delete _ptr; // TODO: 定制删除器
				_del(_ptr);
				delete _count;
			}
		}

		int use_count() const
		{
			return *_count;
		}

	private:
		T* _ptr;
		std::atomic<int>* _count; // 保证计数器指针指向的资源是原子的
		std::function<void(T*)> _del = [](T* ptr) {delete ptr; }; // 给缺省值防止release时调用空的删除器
	};
}
