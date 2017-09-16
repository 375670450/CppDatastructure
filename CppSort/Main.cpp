#include "CppSort.h"


template <typename T>
void TestFunc(void(*func)(std::vector<T> & arr, int left, int right)) {
	std::vector<T> arr;
	GenerateRandomArray(arr, 15);
	(*func)(arr, 0, arr.size( ));		//   func(arr, 0, arr.size( )) is also available
	Print(arr, 4);
}



int main( ) {
	std::vector<int> arr = { 
		2, 2, 2, 2, 2, 2, 2, 2,
	};
	std::vector<void (*)(std::vector<int> &, int, int)> FuncArr;
	//FuncArr.push_back(QuickSort<int>);
	//FuncArr.push_back(ShellSort<int>);
	//FuncArr.push_back(BubbleSort<int>);
	//FuncArr.push_back(SelectSort<int>);
	//FuncArr.push_back(HeapSort<int>);
	//FuncArr.push_back(InsertSort<int>);
	//FuncArr.push_back(MergeSort<int>);
	//FuncArr.push_back(RadixSort<int>);
	//FuncArr.push_back(CountSort<int>);
	//FuncArr.push_back(LargeObjectSort<int>);
	
	QuickSort<int, std::greater<int> >(arr, 0, arr.size( ));
	Print(arr);
	/*for ( int i = 0; i < FuncArr.size( ); i++ ) {
		TestFunc(FuncArr[i]);
	}*/

	//TestFunc<int>(QuickSort);

	//TestFunc<int>(ShellSort);

	//TestFunc<int>(BubbleSort);

	//TestFunc<int>(SelectSort);

	//TestFunc<int>(HeapSort);

	//TestFunc<int>(InsertSort);

	//TestFunc<int>(MergeSort);

	//TestFunc<int>(RadixSort);

	//TestFunc<int>(CountSort);

	//TestFunc<int>(LargeObjectSort);

	system("pause");
	return 0;
}