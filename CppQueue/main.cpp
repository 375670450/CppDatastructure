
#include<queue>
#include<algorithm>
#include"my_queue.h"

using namespace  std;


int main ( ) {

	my_queue<int> q;									// 测试基本类型int 
	try {
		for ( int i = 0; i < 4; i++ ) {
			q.push (i);
			std::cout << "push:" << q.back ( ) << std::endl;
		}
		for ( int i = 0; i < 5; i++ ) {
			std::cout << "pop:" << q.front ( ) << std::endl;
			q.pop ( );
		}
	} catch ( const queue_exception & e ) {
		std::cout << e.what ( ) << std::endl;
	} catch ( const std::exception & e ) {
		std::cout << e.what ( ) << std::endl;
	}
	std::cout << std::endl;

	my_queue<std::string> q2;								// 测试标准库的提供的引用类型string 
	std::string arr[] = { "aaa","bbb","ccc","ddd" };
	try {
		for ( int i = 0; i < 4; i++ ) {
			q2.push (arr[i]);
			std::cout << "push:" << q2.back ( ) << std::endl;
		}
		for ( int i = 0; i < 5; i++ ) {
			std::cout << "pop:" << q2.front ( ) << std::endl;
			q2.pop ( );
		}
	} catch ( const queue_exception & e ) {
		std::cout << e.what ( ) << std::endl;
	} catch ( const std::exception & e ) {
		std::cout << e.what ( ) << std::endl;
	}
	std::cout << std::endl;

	my_queue<queue_exception> q3;						// 测试自定义类型 
	try {
		for ( int i = 0; i < 4; i++ ) {
			q3.push (queue_exception (arr[i]));
			std::cout << "push:" << q3.back ( ).what ( ) << std::endl;
		}
		for ( int i = 0; i < 5; i++ ) {
			std::cout << "pop:" << q3.front ( ).what ( ) << std::endl;
			q3.pop ( );
		}
	} catch ( const std::exception & e ) {
		std::cout << e.what ( ) << std::endl;
	}
	return 0;
}
