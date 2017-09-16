#include<iostream>
#include<algorithm>
#include<list>
#include<exception> 
#include<stdexcept> 
#include<string>
//using namespace std;


class queue_exception : public std::exception { // 自定义异常, 用于区分是标准异常还是队列内部的异常 
private:
	std::string msg;

public:

	queue_exception (const std::string & str) : msg (str) { } // 提供两个常用的异常类构造函数 

	queue_exception (const std::exception & e) : std::exception (e) { }

	const char * what ( ) const noexcept {			// 重写exception类的what方法以便区分 
		return ( "queue_exception: " + msg ).c_str ( );
	}

};

template<typename Type>
class my_queue {
private:

	std::list<Type> m_data;				// 用于存储用户数据的数据结构, 封装 

public:

	my_queue ( ) {

	}

	my_queue (const my_queue<Type> & q) {				// 复制构造函数 
		m_data = q.m_data;
	}

	bool empty ( ) const {
		return m_data.empty ( );
	}

	int size ( ) const {
		return m_data.size ( );
	}

	Type front ( ) const {								// 返回队首元素, 无则抛出异常 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");	// 抛出异常后不会继续往下执行m_data.front
														// 而是沿调用栈向上寻找匹配的catch语句
														// 因此这里不需要return nullptr或return 0 
		}

		return m_data.front ( );
	}

	Type back ( ) const {								// 返回队尾元素 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");
		}

		return m_data.back ( );
	}

	void push (const Type & val) {						// 向队尾插入元素 
		try {
			m_data.push_back (val);
		} catch ( const std::exception & e ) {
			throw queue_exception (e);
		}

	}

	void pop ( ) {										// 在队首弹出元素 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");
		}

		m_data.pop_front ( );
	}



};

