#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <ctime>


template <typename Comparable>
class Pointer {
private:
	Comparable * pointee;
public:
	Pointer(Comparable * rhs = nullptr) : pointee(rhs) {}
	/*bool operator <(const Pointer & p2) const{
		return *pointee < *(p2.pointee);
	} */
	friend bool operator <(const Pointer & p1, const Pointer & p2) {
		return *(p1.pointee) < *(p2.pointee);
	}
	operator Comparable * () const {	// 类型转换, 定义了从Pointer<T> 到 (T*) 的类型转换
		return pointee;
	}
};

template <typename T>
void Print(const std::vector<T> & arr, int width = 0) {
	for each (T var in arr) {
		std::cout << std::setw(width) << var << " ";
	}
	std::cout << std::endl;
}

template<typename T>
std::string ToString(T val) {
	std::stringstream ss;
	std::string result;
	ss << val;
	ss >> result;
	return result;
}

template <typename T>
void GenerateRandomArray(std::vector<T> & arr, int size = 30, int range = 1000) {
	arr.clear( );
	srand(clock( ));
	for ( int i = 0; i < size; i++ ) {
		arr.push_back((T) rand( ) % range);
	}
	return;
}

void GeneratePermutation (std::string & perm, int key) {
	// Given a [key] and turn the permutation [perm] into another permutation
	for ( int mod = 1; mod < perm.length ( ); mod++ ) {
		std::swap (perm[key % mod], perm[mod]);
		key = key / ( mod + 1 );
	}
}



template <typename T, typename Comparator = std::less<T> >
const T & QuickSelect(const std::vector<T> & old_arr, int left, int right,const int rank) {
	// Based on Quick Sort
	if ( rank < 1 || rank > old_arr.size( ) ) {
		return -1;
	}
	Comparator isLessThan;
	std::vector<T> arr = old_arr;
	std::function< T(std::vector<T> &, int, int, int) > QuickFunc;
	QuickFunc =
		[&QuickFunc, &isLessThan] (std::vector<T> & arr, int left, int right, int rank) -> T {
		if ( left == right ) return arr[left];
		int li, ri;
		T pivot = arr[left];
		li = left;	ri = right;
		while ( li < ri ) {
			while ( li < ri && isLessThan(pivot, arr[ri]) ) ri--;
			if ( li < ri ) arr[li++] = arr[ri];
			while ( li < ri && isLessThan(arr[li], pivot) ) li++;
			if ( li < ri ) arr[ri--] = arr[li];
		}
		arr[li] = pivot;
		if ( li+1 == rank ) return pivot;	// li+1 equals to the rank of arr[li](pivot)
		else if ( li+1 < rank ) return QuickFunc(arr, li+1, right, rank-(li+1));
		else if ( li+1 > rank ) return QuickFunc(arr, left, li-1, rank);
	};
	return QuickFunc(arr, left, right - 1, rank);
}

template <typename T, typename Comparator = std::less<T> >
void QuickSort(std::vector<T> & arr, int left, int right) {
	Comparator isLessThan;

	std::function< T(std::vector<T> &, int, int) > Median3;
	std::function< void(std::vector<T> &, int, int) > QuickFunc;
	Median3 =
		[] (std::vector<T> & arr, int left, int right) ->T {
		int mid = (left + right) / 2;

		if ( arr[left] > arr[mid] ) std::swap(arr[left], arr[mid]);
		if ( arr[left] > arr[right] ) std::swap(arr[left], arr[right]);
		if ( arr[mid] > arr[right] ) std::swap(arr[mid], arr[right]);
		// Hide the pivot
		std::swap(arr[left], arr[mid]);
		return arr[left];
	};

	QuickFunc =
		[&QuickFunc, &isLessThan, &Median3] (std::vector<T> & arr, int left, int right) {
		if ( left >= right ) return;
		// T pivot = arr[left];			// Not efficient enough
		T pivot = Median3(arr, left, right);
		
		int li = left, ri = right;
		while ( li < ri ) {
			while ( li < ri && (isLessThan(pivot, arr[ri]) || arr[ri]==pivot) ) ri--;	// 考虑相等的情况以处理含有相同元素的序列
			if ( li < ri ) arr[li++] = arr[ri];
			while ( li < ri && isLessThan(arr[li], pivot) ) li++;
			if ( li < ri ) arr[ri--] = arr[li];
		}
		arr[li] = pivot;
		QuickFunc(arr, left, li - 1);
		QuickFunc(arr, li + 1, right);
	};

	QuickFunc(arr, left, right - 1);
	return;
}

template <typename T, typename Comparator = std::less<T> >
void IntroSort(std::vector<T> & arr, int left, int right) {
	// Mainly base on Quicksort and use Heapsort when N <= Threshold
	Comparator isLessThan;
	
	return;
}

template <typename T, typename Comparator = std::less<T> >
void BubbleSort(std::vector<T> & arr, int left, int right) {
	Comparator isLessThan;
	for ( int rear = right; rear > left; rear-- ) {
		for ( int j = left; j < rear - 1; j++ ) {
			if ( isLessThan(arr[j + 1], arr[j]) ) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
	return;
}

template <typename T, typename Comparator = std::less<T> >
void SelectSort(std::vector<T> & arr, int left, int right) {
	// Exchange sort
	Comparator isLessThan;
	for ( int sorted = left; sorted < right; sorted++ ) {
		int minIndex = sorted;
		for ( int i = sorted + 1; i < right; i++ ) {
			if ( isLessThan(arr[i], arr[minIndex]) ) {
				minIndex = i;
			}
		}
		std::swap(arr[minIndex], arr[sorted]);
	}
	return;
}

template <typename T, typename Comparator = std::less<T> >
void MergeSort(std::vector<T> & arr, int left, int right) {
	// To make these functions' argument lists similar
	// use a lambda expression(actually a function object) instead of a recursive function
	Comparator isLessThan;
	
	std::function< void(std::vector<T>&, std::vector<T>&, int, int) > MergeFunc;
	MergeFunc =
		[&MergeFunc, &isLessThan] (std::vector<T> & arr, std::vector<T>& tmpArr, int left, int right) {
		// Inside is a recursive normal merge function
		if ( left == right ) {
			return;
		}
		int mid = (left + right) / 2;
		MergeFunc(arr, tmpArr, left, mid);
		MergeFunc(arr, tmpArr, mid + 1, right);
		tmpArr.clear( );
		int li = left, ri = mid + 1;
		while ( li <= mid && ri <= right ) {
			if ( isLessThan(arr[li], arr[ri]) ) {
				tmpArr.push_back(arr[li++]);
			} else {
				tmpArr.push_back(arr[ri++]);
			}
		}
		while ( li <= mid ) {
			tmpArr.push_back(arr[li++]);
		}
		while ( ri <= right ) {
			tmpArr.push_back(arr[ri++]);
		}
		for ( int i = 0; i < tmpArr.size( ); i++ ) {
			arr[left + i] = tmpArr[i];
		}
	};

	std::vector<T> tmpArr;
	tmpArr.resize(right-left);
	MergeFunc(arr, tmpArr, left, right - 1);
	return;
}

template <typename T, typename Comparator = std::less<T> >
void InsertSort(std::vector<T> & arr, int left, int right) {
	Comparator isLessThan;
	for ( int rear = left; rear < right; rear++ ) {
		int index = rear;
		T tmp = arr[rear];
		for ( ; index > 0 && isLessThan(tmp, arr[index - 1]); index-- ) {
			arr[index] = arr[index - 1];
		}
		arr[index] = tmp;
	}
	return;
}

template <typename T, typename Comparator = std::less<T> >
void ShellSort(std::vector<T> & arr, int left, int right) {
	Comparator isLessThan;
	for ( int increment = (right-left) >> 1; increment > 0; increment >>= 1 ) {
		for ( int rear = increment; rear < right; rear++ ) {
			// Follow is an insert sort
			T tmp = arr[rear];
			int index = rear;
			for ( ; index >= increment && isLessThan(tmp, arr[index - increment]); // need to ensure (index-increment) >= 0
			index -= increment ) {
				arr[index] = arr[index - increment];
			}
			arr[index] = tmp;
		}
	}
	return;
}

template <typename T, typename Comparator = std::less<T> >
void HeapSort(std::vector<T> & arr, int left, int right) {
	Comparator isLessThan;
	for ( int rear = right - 1; rear >= left; rear-- ) {
		for ( int pos = rear; pos >= left; pos-- ) {
			int child = pos * 2 + 1;
			if ( child > rear )continue;
			if ( child + 1 <= rear && !isLessThan(arr[child + 1], arr[child]) ) {
				child++;
			}
			if ( !isLessThan(arr[child], arr[pos]) ) {
				std::swap(arr[pos], arr[child]);
			}
		}
		std::swap(arr[0], arr[rear]);
	}

	return;
}

template <typename T, typename Comparator = std::less<T> >
void RadixSort(std::vector<T> & arr, int left, int right) {
	// Also called BucketSort
	// Available for POSITIVE INTEGERS only
	// Firstly find the bits(decimal) of the maximum number
	if ( typeid(arr[left]) != typeid(1) ) return;	// if type is not int then quit 
	int maxIndex = 0;
	Comparator isLessThan;
	std::vector<std::string> tmpArr;
	for ( int i = left; i < right; i++ ) {
		if ( arr[i] < 0 ) return;
		if ( arr[maxIndex] < arr[i] ) maxIndex = i;
		tmpArr.push_back(ToString(arr[i]));
	}
	int maxWidth = tmpArr[maxIndex].length( );
	// Push them into buckets
	std::vector<std::string> vec[10];		// Decimal number
	for ( int k = 1; k <= maxWidth; k++ ) {
		for ( int i = 0; i < tmpArr.size( ); i++ ) {
			if ( k > tmpArr[i].length( ) ) {
				vec[0].push_back(tmpArr[i]);
			} else {
				vec[tmpArr[i].at(tmpArr[i].length( ) - k) - '0'].push_back(tmpArr[i]);
			}
		}
		tmpArr.clear( );
		for ( int i = 0; i < 10; i++ ) {
			for ( int j = 0; j < vec[i].size( ); j++ ) {
				tmpArr.push_back(vec[i][j]);
			}
			vec[i].clear( );
		}
	}
	// To ensure the order needed
	arr.clear( );
	if ( isLessThan(1, 2) ) {				
		for ( int i = 0; i < tmpArr.size( ); i++ ) {
			arr.push_back(atoi(tmpArr[i].c_str( )));
		}
	} else {
		for ( int i = tmpArr.size( ) - 1; i >= 0; i-- ) {
			arr.push_back(atoi(tmpArr[i].c_str( )));
		}
	}

	return;
}

template <typename T, typename Comparator = std::less<T> >
void CountSort(std::vector<T> & arr, int left, int right) {
	// Available for those SMALL POSITIVE INTEGERS only
	// First find the maximum number
	Comparator isLessThan;
	std::vector<T> cnts;
	if ( typeid(arr[left]) != typeid(1) ) return;	// if type is not int then quit 
	for ( int i = 0; i < right; i++ ) {
		if ( arr[i] < 0 ) return;
		if ( arr[i] > cnts.size( ) ) cnts.resize(arr[i] + 1);
		cnts[arr[i]]++;
	}
	arr.clear( );
	if ( isLessThan(1, 2) ) {
		for ( int i = 0; i < cnts.size( ); i++ ) {
			while ( cnts[i] ) {
				arr.push_back(i);
				cnts[i]--;
			}
		}
	} else {
		for ( int i = cnts.size( ); i >= 0; i-- ) {
			while ( cnts[i] ) {
				arr.push_back(i);
				cnts[i]--;
			}
		}
	}
	return;
}

template <typename T >
void LargeObjectSort(std::vector<T> & arr, int left, int right) {
	std::vector< Pointer<T> > PtrArr(right - left);
	for ( int i = left; i < right; i++ ) PtrArr[i] = &arr[i];
	QuickSort(PtrArr, left, right);

	for ( int i = left; i < right; i++ ) {
		if ( PtrArr[i] != &arr[i] ) {
			// arr[i] has been moved away
			int j = i, nextj = 0;
			T tmp = arr[j];
			for ( ; PtrArr[j] != &arr[i]; j=nextj ) {
				nextj = PtrArr[j] - &arr[0];
				arr[j] = *PtrArr[j];
				PtrArr[j] = &arr[j];
			}
			arr[j] = tmp;
			PtrArr[j] = &arr[j];
		}
	}
	return;
}
