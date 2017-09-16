#include<iostream>
#include<algorithm>
#include<list>
#include<exception> 
#include<stdexcept> 
#include<string>
//using namespace std;


class queue_exception : public std::exception { // �Զ����쳣, ���������Ǳ�׼�쳣���Ƕ����ڲ����쳣 
private:
	std::string msg;

public:

	queue_exception (const std::string & str) : msg (str) { } // �ṩ�������õ��쳣�๹�캯�� 

	queue_exception (const std::exception & e) : std::exception (e) { }

	const char * what ( ) const noexcept {			// ��дexception���what�����Ա����� 
		return ( "queue_exception: " + msg ).c_str ( );
	}

};

template<typename Type>
class my_queue {
private:

	std::list<Type> m_data;				// ���ڴ洢�û����ݵ����ݽṹ, ��װ 

public:

	my_queue ( ) {

	}

	my_queue (const my_queue<Type> & q) {				// ���ƹ��캯�� 
		m_data = q.m_data;
	}

	bool empty ( ) const {
		return m_data.empty ( );
	}

	int size ( ) const {
		return m_data.size ( );
	}

	Type front ( ) const {								// ���ض���Ԫ��, �����׳��쳣 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");	// �׳��쳣�󲻻��������ִ��m_data.front
														// �����ص���ջ����Ѱ��ƥ���catch���
														// ������ﲻ��Ҫreturn nullptr��return 0 
		}

		return m_data.front ( );
	}

	Type back ( ) const {								// ���ض�βԪ�� 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");
		}

		return m_data.back ( );
	}

	void push (const Type & val) {						// ���β����Ԫ�� 
		try {
			m_data.push_back (val);
		} catch ( const std::exception & e ) {
			throw queue_exception (e);
		}

	}

	void pop ( ) {										// �ڶ��׵���Ԫ�� 

		if ( m_data.empty ( ) ) {
			throw queue_exception ("queue is empty");
		}

		m_data.pop_front ( );
	}



};

