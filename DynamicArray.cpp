#include "DynamicArray.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <climits>
#include <memory>
#include <string>

using namespace std;

// Constructor
//precondition: The constructor is called to create a new instance of the DynamicArray class, and the isSorted parameter is provided to indicate whether the array should be sorted or not.
//postcondition: A new instance of the DynamicArray class is created, with the internal array pointer initialized to nullptr, the size set to 0, and the sorted flag set based on the provided parameter.
DynamicArray::DynamicArray(bool isSorted)
{
    arr = nullptr;
    size = 0;
    sorted = isSorted;
}

// Destructor
//PRECONDITION: The dynamic array is no longer needed and is being destroyed.
//POSTCONDITION: The memory allocated for the dynamic array is released, and the pointer is set to null.
DynamicArray::~DynamicArray()
{
    delete[] arr;
}

// Case A - Generate random strings
//precondition: The count parameter is a positive integer representing the number of random strings to generate.
//postcondition: The dynamic array is resized to accommodate the specified number of random strings, and the strings are generated and stored in the array.
void DynamicArray::generateRandom(int count)
{
    if (count <= 0)
    {
        throw invalid_argument("Invalid array size.");
    }

    unique_ptr<string[]> temp(new string[count]);

    for (int i = 0; i < count; i++)
    {
        int randomNumber = rand() % count + 1;

        temp[i] = "str#" + to_string(randomNumber);
    }

    // Sort only for Option 2
    if (sorted)
    {
        sort(temp.get(), temp.get() + count);
    }

    delete[] arr;

    arr = temp.release();
    size = count;
}


// Case B - Add an element
//precondition: The value parameter is a string representing the element to be added to the dynamic array.
//postcondition: The dynamic array is resized to accommodate the new element, and the element is added to the array. If the array is sorted, the element is inserted in the correct position to maintain the sorted order.
void DynamicArray::addElement(const string& value)
{
    if (size < 0 || size == INT_MAX)
    {
        throw runtime_error("Invalid array size.");
    }

    const int newSize = size + 1;

    unique_ptr<string[]> temp(new string[newSize]);

    if (!sorted)
    {
        // Option 1: Append to the end
        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }

        temp[size] = value;
    }
    else
    {
        // Option 2: Find the sorted insertion position
        int position = 0;

        if (size > 0)
        {
            position = static_cast<int>(lower_bound(arr, arr + size, value) - arr);
        }

        // Copy elements before insertion
        for (int i = 0; i < position; i++)
        {
            temp[i] = arr[i];
        }

        // Insert new element
        temp[position] = value;

        // Copy remaining elements
        for (int i = position; i < size; i++)
        {
            temp[static_cast<size_t>(static_cast<int>(i)) + 1] = arr[i];
        }
    }

    delete[] arr;

    arr = temp.release();
    size = newSize;
}

// Case C - Display elements
//precondition: The dynamic array is not empty and contains elements to be displayed.
//postcondition: The elements of the dynamic array are displayed in a formatted manner, with a specified number of elements per line. If the array is empty, a message indicating that the array is empty is displayed.
void DynamicArray::display() const
{
    if (size == 0)
    {
        cout << "\n\t\t\tThe array is empty.\n";
        return;
    }

    const int ELEMENTS_PER_LINE = 10;

    cout << "\n\t\t\t";

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";

        if ((i + ONE) % ELEMENTS_PER_LINE == 0 && i + ONE < size)
        {
            cout << "\n\t\t\t";
        }
    }

    cout << "\n";
}

// Recursive serial search
//precondition: The value parameter is the string to search for, and the index parameter is the current index being checked in the array.
//postcondition: The function returns the index of the first occurrence of the value in the array, or -1 if the value is not found.
int DynamicArray::recursiveSerialSearch(const string& value, int index) const
{
    if (index >= size)
    {
        return -1;
    }

    if (arr[index] == value)
    {
        return index;
    }

    return recursiveSerialSearch(value, index + ONE);
}

// Public serial search
//precondition: The value parameter is the string to search for in the dynamic array.
//postcondition: The function returns the index of the first occurrence of the value in the array, or -1 if the value is not found.
int DynamicArray::serialSearch(const string& value) const
{
    return recursiveSerialSearch(value, 0);
}

// Recursive binary search
//precondition: The value parameter is the string to search for, and the left and right parameters define the current search range in the array.
//postcondition: The function returns the index of the value in the array if found, or -1 if the value is not present in the specified range.
int DynamicArray::recursiveBinarySearch(const string& value, int left, int right) const
{
    if (left > right)
    {
        return -1;
    }

    // Use int64_t to prevent overflow in the calculation
    int64_t l = static_cast<int64_t>(left);
    int64_t r = static_cast<int64_t>(right);
    int mid = static_cast<int>(l + (r - l) / TWO);

    if (arr[mid] == value)
    {
        return mid;
    }

    if (value < arr[mid])
    {
        return recursiveBinarySearch(value, left, mid - ONE);
    }

    return recursiveBinarySearch(value, mid + ONE, right);
}

// Public binary search
//precondition: The value parameter is the string to search for in the dynamic array. The array must be sorted for binary search to work correctly.
//postcondition: The function returns the index of the value in the array if found, or -1 if the value is not present. If the array is empty, it returns -1.
int DynamicArray::binarySearch(const string& value) const
{
    return recursiveBinarySearch(value, 0, size - ONE);
}

// Case E - Clear the array
//precondition: The dynamic array is no longer needed, and the user wants to clear its contents. The array may be empty or contain elements.
//postcondition: The memory allocated for the dynamic array is released, the pointer is set to null, and the size is reset to 0. The dynamic array is effectively cleared and ready for reuse.
void DynamicArray::clear()
{
	assert(arr != nullptr || size == 0);
    delete[] arr;

    arr = nullptr;
    size = 0;
}

// Return number of elements 
//precondition: The dynamic array has been initialized and may contain elements. The user wants to retrieve the current number of elements in the array.
//postcondition: The function returns the current number of elements in the dynamic array. If the array is empty, it returns 0.
int DynamicArray::getSize() const
{
    return size;
}

// STL-based serial search
//precondition: The value parameter is the string to search for in the dynamic array. The array may be empty or contain elements.
//postcondition: The function uses the STL find algorithm to search for the value in the array. It returns the index of the first occurrence of the value if found, or -1 if the value is not present. If the array is empty, it returns -1.
int DynamicArray::stlSerialSearch(const string& value) const
{
    if (size == 0)
    {
        return -1;
    }

    const string* result = find(arr, arr + size, value);

    if (result == arr + size)
    {
        return -1;
    }

    return static_cast<int>(result - arr);
}

// STL-based binary search
//precondition: The value parameter is the string to search for in the dynamic array. The array must be sorted for binary search to work correctly. The array may be empty or contain elements.
//postcondition: The function uses the STL lower_bound algorithm to search for the value in the sorted array. It returns the index of the value if found, or -1 if the value is not present. If the array is empty, it returns -1.
int DynamicArray::stlBinarySearch(const string& value) const
{
    if (size == 0)
    {
        return -1;
    }

    const string* result = lower_bound(arr, arr + size, value);

    if (result != arr + size && *result == value)
    {
        return static_cast<int>(result - arr);
    }

    return -1;
}