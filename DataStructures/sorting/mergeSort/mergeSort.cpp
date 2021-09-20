// mergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <future>
using namespace std;



vector<int> mergerHelper(vector<int> leftArray, vector<int> rightArray) {

	vector<int> sortedArray((leftArray.size() + rightArray.size()), 0);

	int k = 0;
	int i = 0;
	int j = 0;

	while (i <= leftArray.size() - 1 && j <= rightArray.size() - 1) {
		if (leftArray[i] <= rightArray[j]) {
			sortedArray[k] = leftArray[i];
			i++;
		}
		else {
			sortedArray[k] = rightArray[j];
			j++;
		}

		k++;
	}

	while (i < leftArray.size()) {
		sortedArray[k] = leftArray[i];
		i++;
		k++;
	}

	while (j < rightArray.size()) {
		sortedArray[k] = rightArray[j];
		j++;
		k++;
	}

	return sortedArray;
}

vector<int> mergeSort(vector<int> array, int depth=0) {
	// Write your code here.

	cout << "This thread " << std::this_thread::get_id << " partioning elements : " << array.size() << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	if (array.size() <= 1)
		return array;

	int mid = array.size() / 2;

	vector<int> leftHalf(array.begin(), array.begin() + mid);
	vector<int> rightHalf(array.begin() + mid, array.end());

	std::future<vector<int>> left;
	vector<int> leftArray;
	if (depth < std::thread::hardware_concurrency()) {
		cout << "current depth : " << depth << endl;
		left = std::async(std::launch::async, mergeSort, leftHalf, depth+1);
	}
	else {
		leftArray = mergeSort(leftHalf, depth);
	}

	auto right = mergeSort(rightHalf, depth);

	if (depth < std::thread::hardware_concurrency())
		leftArray = left.get();

	return mergerHelper(leftArray,right);

}


int main()
{
	auto array = mergeSort({ 8, 5, 2, 9, 5, 6, 3,23,6547,66,23,12,3,8,90,655,44,33,22,678,533,245,45,76,789,465,35,4,23,654,456,456,46,345,24,23,45,
		8, 5, 2, 9, 5, 6, 3,23,6547,66,23,12,3,8,90,655,44,33,22,678,533,245,45,76,789,465,35,4,23,654,456,456,46,345,24,23,45 });

	for (auto elem : array) {
		cout << elem << " , ";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
