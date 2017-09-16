#pragma once
#include "BinTree.h"

template <typename T, typename Comparator = less<T> >
class PriorityQueue_List : public BinTree<T> {
	
};

template <typename T, typename Comparator = less<T> >
class PriorityQueue_Array {
protected:
	const Comparator isLessThan;

	T* Data;

	int	Capacity;

	int	Size;

	void PercolateUp(int pos) {
		for ( ; (pos >> 1) > 0 && isLessThan(Data[pos], Data[pos >> 1]); pos >>= 1 ) {
			swap(Data[pos], Data[pos >> 1]);
		}
		return;
	}

	void PercolateDown(int pos) {
		int child;
		T tmp = Data[pos];
		for ( ; (pos << 1) <= Size; pos = child ) {
			child = pos << 1;
			if ( child + 1 <= Size && isLessThan(Data[child + 1], Data[child]) )	child++;
			if ( isLessThan(Data[child], tmp) ) {
				swap(Data[pos], Data[child]);
			}
			//Still need to continue adjust those elements below
			//else {					
			//	break;
			//}
		}
	}

public:
	PriorityQueue_Array(int _capacity = 0):Capacity(_capacity), Size(0) { 
		Data = new T[_capacity]; 
	}
	
	PriorityQueue_Array(const PriorityQueue_Array & PQ) {
		// Deep copy
		Capacity = PQ.Capacity;
		Size = PQ.Size;
		isLessThan = PQ.isLessThan;
		Data = new T[Capacity];
		memcpy(Data, PQ.Data, sizeof(T)*Capacity);
	}
	
	PriorityQueue_Array(vector<T> & Array) {
		// Insert the elements by order would be unconvenient,
		// Better change some element's position in Array and turn it to a heap
		// Time Complexity : O(N) ? 
		Capacity = Array.size( );
		Data = new T[Capacity];
		for ( int i = 0; i < Array.size( ); i++ ) {
			Data[++Size] = Array[i];
		}
		for ( int pos = Size / 2; pos > 0; pos-- ) {			
			PercolateDown(pos);
			Print( );
		}
	}

	
	PriorityQueue_Array(T Array[], int Size) {
		Size = Capacity = size;
		Data = new T[Capacity];
		memcpy(Data, Array, sizeof(T)*Capacity);
		for ( int pos = Size / 2; pos > 0; pos-- ) {
			PercolateDown(pos);
		}
	}
	
	~PriorityQueue_Array( ) { 
		if ( Data != nullptr ) {
			delete[] Data;
		}
	}
	
	T Delete( ) {
		if ( isEmpty( ) ) {
			std::cout << "Priority Queue is empty" << endl;
			return Data[0];
		}
		Data[1] = Data[Size--];
		T result = Data[1];
		PercolateDown(1);
		return result;
	}

	int	size( ) const {
		return  Size;
	}
	
	bool isFull( ) const {
		return Size == Capacity;
	}
	
	bool isEmpty( ) const {
		return Size == 0;
	}
	
	void Insert(T data) {
		if ( isFull( ) ) {
			std::cout << "Priority Queue is full" << endl;
			return;
		}
		Data[++Size] = data;
		PercolateUp(Size);
	}
	
	void Print( ) const {
		for ( int i = 1; i <= Size; i++ ) {
			cout << Data[i] << " ";
		}
		cout << endl;
	}
	
};
