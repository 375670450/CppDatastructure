#include "CppSkipList.h"

#ifdef _WIN32				// time measure functions depend on platforms
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <iostream>
#include <vector>
using namespace std;

void generate_array ( vector<int> & vec, size_t size ) {
	vec.clear ( );

	for ( int i = 0; i < size; i++ )
		vec.push_back (i + 1);

	std::shuffle (vec.begin ( ), vec.end ( ), mt19937 (random_device{ }( )));

	return;
}

void test (const vector<int> & vec) {

	SkipList<int> lis;

	cout << "Test Size = " << vec.size ( ) << "\n";

#ifdef _WIN32
	LARGE_INTEGER li;
	__int64 start = 0, elapsed = 0;
	double freq;

	QueryPerformanceFrequency (&li);
	freq = double (li.QuadPart) / 1000.0;

	QueryPerformanceCounter (&li);
	start = li.QuadPart;
#else
	struct timeval t1, t2;
	double elapsed;

	gettimeofday (&t1, NULL);
#endif
	/*
		Test for insertion
	*/
	for ( auto item : vec ) {
		lis.Insert (item);
	}

#ifdef _WIN32
	QueryPerformanceCounter (&li);
	elapsed = ( li.QuadPart - start ) / freq;
#else
	gettimeofday (&t2, NULL);
	elapsed = ( t2.tv_sec - t1.tv_sec ) * 1000.0;      // sec to ms
	elapsed += ( t2.tv_usec - t1.tv_usec ) / 1000.0;   // us to ms
#endif
	
	cout << "Insert Time: " << elapsed << "ms" << endl;


	/*
		Test for deletion
	*/
#ifdef _WIN32

	QueryPerformanceCounter (&li);
	start = li.QuadPart;
#else
	gettimeofday (&t1, NULL);

#endif // DEBUG

	for ( auto item : vec ) {
//		lis.Search (item);
		lis.Search ( vec.at(item >> 1) ); 
	}


#ifdef _WIN32
	QueryPerformanceCounter (&li);
	elapsed = ( li.QuadPart - start ) / freq;
#else
	gettimeofday (&t2, NULL);
	elapsed = ( t2.tv_sec - t1.tv_sec ) * 1000.0;      // sec to ms
	elapsed += ( t2.tv_usec - t1.tv_usec ) / 1000.0;   // us to ms
#endif

	cout << "Search Time: " << elapsed << "ms" << endl;
	
	/*
		Test for deletion
	*/
#ifdef _WIN32

	QueryPerformanceCounter (&li);
	start = li.QuadPart;
#else
	gettimeofday (&t1, NULL);

#endif // DEBUG

	for ( auto item : vec ) {
		lis.Delete (item);
	}

#ifdef _WIN32
	QueryPerformanceCounter (&li);
	elapsed = ( li.QuadPart - start ) / freq;
#else
	gettimeofday (&t2, NULL);
	elapsed = ( t2.tv_sec - t1.tv_sec ) * 1000.0;      // sec to ms
	elapsed += ( t2.tv_usec - t1.tv_usec ) / 1000.0;   // us to ms
#endif

	cout << "Delete Time: " << elapsed << "ms" << endl;

	cout << "=====================" << endl;
}

int main ( ) {
	
	const vector<int> testCases{ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 
													200000, 300000, 400000, 500000 };

	for ( auto size : testCases ) {
		vector<int> vec;

		generate_array (vec, size);

		test (vec);
	}
	
	system ("pause");

}
