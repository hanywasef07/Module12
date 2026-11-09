#pragma once

#include <iostream>
#include <string>

using namespace std;

class DynamicArray
{
private:
	static const int ONE = 1, TWO = 2, HUND = 100;
	string* arr; // Pointer to the dynamic array
	int size; // Current number of elements in the array
	bool sorted; // Flag to indicate if the array is sorted

    // Recursive search functions
	int recursiveSerialSearch(const string& value, int index) const; // Helper function for serial search

	int recursiveBinarySearch(const string& value, int left, int right) const; // Helper function for binary search

public:
	//DynamicArray(); // Default constructor
	DynamicArray(bool isSorted = false); // Constructor with sorted flag
	~DynamicArray(); // Destructor

    // Prevent shallow copying
	DynamicArray(const DynamicArray&) = delete; // Delete copy constructor
	DynamicArray& operator=(const DynamicArray&) = delete; // Delete copy assignment operator

	void generateRandom(int count); // Generate random strings and add them to the array
	void addElement(const string& value); // Add an element to the dynamic array
	void display() const; // Display elements in the dynamic array

	int serialSearch(const string& value) const; // Public serial search function
	int binarySearch(const string& value) const; // Public binary search function

    void clear(); // Clear the dynamic array
    int getSize() const; // Get the number of elements in the dynamic array

	int stlSerialSearch(const string& value) const; // STL-based serial search function
	int stlBinarySearch(const string& value) const; // STL-based binary search function
};