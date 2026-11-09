//Names: Hany, Aleeza, Thanh, Victor, and Jacob
//Date: 11/14/2026
//Description: Module 12 - Searching and Hashing

#include <iostream>
#include "input.h"
#include "DynamicArray.h"
//#include "Table.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
char menuOption();
void option1();
void option2();
void option3();

int main()
{
    bool running = true;
    char option;
    srand(static_cast<unsigned int>(time(nullptr)));

    while (running)
    {
        system("cls");

        option = menuOption();
        switch (option)
        {
        case '1':
        {
			option1();
            cout << "\n\n";
            system("pause");
            break;
        }
        case '2':
        {
			option2();
            cout << "\n\n";
            system("pause");
            break;
        }
        case '3':
        {
			option3();

            cout << "\n\n";
            system("pause");
            break;
        }
        case '0':
            cout << "Exiting the program.\n";
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}


char menuOption()
{
    cout << "\tCMPR131 Chapter 12: Searches and hashing by Hany, Aleeza, Thanh, Victor, and Jacob (11/14/2026)\n";
    cout << "\t" << string(100, char(205));
    cout << "\n\t\t1> Searching from an unsorted dynamic array";
    cout << "\n\t\t2> Searching from a sorted dynamic array";
    cout << "\n\t\t3> Application using hashing\n";
    cout << "\t" << string(100, char(196));
    cout << "\n\t\t0 > Exit\n";
    cout << "\t" << string(100, char(205));

    char option = toupper(inputChar("\n\t\toption: ", static_cast<string>("1,2,3,0")));
    return option;
}

//precondition: The function assumes that the DynamicArray class has been properly defined and implemented, and that the inputChar and inputInteger functions are available for user input.
// The function also assumes that the system("cls") command is supported on the platform being used to clear the console screen.
//postcondition: The function provides a menu-driven interface for the user to interact with an unsorted dynamic array, allowing them to perform various operations such as reading data, 
// adding elements, displaying elements, searching for elements, and clearing the array. The function will continue to run until the user chooses to return to the main menu.
void option1()
{
    DynamicArray arr;
    bool running = true;
    while (running)
    {
        system("cls");
        cout << "\n\t\t1> Searching unsorted dynamic arrays";
        cout << "\n\t\t" << string(80, char(205));
        cout << "\n\t\t\tA> Read data file and store into the array";
        cout << "\n\t\t\tB> Add an element to the dynamic array";
        cout << "\n\t\t\tC> Display elements from the array";
        cout << "\n\t\t\tD> Search for an element from the array";
        cout << "\n\t\t\tE> Clear the array";
        cout << "\n\t\t" << string(80, char(196));
        cout << "\n\t\t\t0> return";
        cout << "\n\t\t" << string(80, char(205));

        char option = toupper(inputChar("\n\t\t\tOption: ", static_cast<string>("A,B,C,D,E,0")));
        switch (option)
        {
        case 'A':
        {
            int count = inputInteger("\n\t\t\tEnter the size of the dynamic array: ", 1, 10000);
            arr.generateRandom(count);
            cout << "\n\t\t\tRandom elements have been populated into the array.\n";
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'B':
        {
            try
            {
                string value = inputString("\n\t\t\tEnter a string element: ", false);

                arr.addElement(value);

                cout << "\n\t\t\tElement \"" << value << "\" has been added to the array.\n";
            }
            catch (const exception& error)
            {
                cout << "\n\t\t\tERROR: " << error.what() << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'C':
        {
            arr.display();
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'D':
        {
            if (arr.getSize() == 0)
            {
                cout << "\n\t\t\tThe array is empty.\n";
            }
            else
            {
                char searchType = toupper(inputChar("\n\t\t\tChoose search type (S)Serial or (B)Binary: ", static_cast<string>("S,B")));

                cout << "\n\t\t\tRecursive ";

                if (searchType == 'S')
                {
                    cout << "serial search\n";
                }
                else
                {
                    cout << "binary search\n";
                }

                cout << "\t\t\t" << string(50, char(196)) << "\n";

                string value = inputString("\n\t\t\tEnter a string element to search: ", false);

                int index = -1;

                if (searchType == 'S')
                {
                    index = arr.serialSearch(value);
                }
                else
                {
                    index = arr.binarySearch(value);
                }

                if (index != -1)
                {
                    cout << "\n\t\t\t\"" << value << "\" is found at index " << index << " from the unsorted array.\n";
                }
                else
                {
                    cout << "\n\t\t\t\"" << value << "\" is not found in the unsorted array.\n";
                }
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'E':
        {
            try
            {
                if (arr.getSize() == 0)
                {
                    throw string("The array is empty.");
                }

                arr.clear();

                cout << "\n\t\t\tElements from the array have been cleared/deleted.\n";
            }
            catch (const string& error)
            {
                cout << "\n\t\t\t" << error << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case '0':
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

}

//precondition: The function assumes that the DynamicArray class has been properly defined and implemented, and that the inputChar and inputInteger functions are available for user input. 
// The function also assumes that the system("cls") command is supported on the platform being used to clear the console screen.
//postcondition: The function provides a menu-driven interface for the user to interact with a sorted dynamic array, allowing them to perform various operations such as reading data, 
// adding elements, displaying elements, searching for elements, and clearing the array. The function will continue to run until the user chooses to return to the main menu.
void option2()
{
	DynamicArray arr(true); // Create a sorted dynamic array
    bool running = true;
    while (running)
    {
        system("cls");
        cout << "\n\t\t2>> Searching sorted dynamic arrays";
        cout << "\n\t\t" << string(80, char(205));
        cout << "\n\t\t\tA> Read data file and store into the array";
        cout << "\n\t\t\tB> Add an element to the dynamic array";
        cout << "\n\t\t\tC> Display elements from the array";
        cout << "\n\t\t\tD> Search for an element from the array";
        cout << "\n\t\t\tE> Clear the array";
        cout << "\n\t\t" << string(80, char(196));
        cout << "\n\t\t\t0> return";
        cout << "\n\t\t" << string(80, char(205));

        char option = toupper(inputChar("\n\t\t\tOption: ", static_cast<string>("A,B,C,D,E,0")));
        switch (option)
        {
        case 'A':
        {
            try
            {
                int count = inputInteger("\n\t\t\tEnter the size of the dynamic array: ", 1, 10000);

                arr.generateRandom(count);

                cout << "\n\t\t\tRandom elements have been populated into the array.\n";
            }
            catch (const exception& error)
            {
                cout << "\n\t\t\tERROR: " << error.what() << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'B':
        {
            try
            {
                string value = inputString("\n\t\t\tEnter a string element: ", false);
                arr.addElement(value);
                cout << "\n\t\t\tElement \"" << value << "\" has been added to the array.\n";
            }
            catch (const exception& error)
            {
                cout << "\n\t\t\tERROR: " << error.what() << "\n";
			}
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'C':
        {
            try
            {
                if (arr.getSize() == 0)
                {
                    throw string("The array is empty.");
                }

                arr.display();
            }
            catch (const string& error)
            {
                cout << "\n\t\t\t" << error << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'D':
        {
            try
            {
                if (arr.getSize() == 0)
                {
                    throw string("The array is empty.");
                }

                char searchType = toupper(inputChar("\n\t\t\tChoose search type (S)Serial or (B)Binary: ", static_cast<string>("S,B")));

                if (searchType == 'S')
                {
                    cout << "\n\t\t\tSTL serial search\n";
                }
                else
                {
                    cout << "\n\t\t\tSTL binary search\n";
                }

                cout << "\t\t\t" << string(50, char(196)) << "\n";

                string value = inputString("\n\t\t\tEnter a string element to search: ", false);

                int index = -1;

                if (searchType == 'S')
                {
                    index = arr.stlSerialSearch(value);
                }
                else
                {
                    index = arr.stlBinarySearch(value);
                }

                if (index != -1)
                {
                    cout << "\n\t\t\t\"" << value << "\" is found at index " << index << " from the sorted array.\n";
                }
                else
                {
                    cout << "\n\t\t\t\"" << value << "\" is not found in the sorted array.\n";
                }
            }
            catch (const string& error)
            {
                cout << "\n\t\t\t" << error << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'E':
        {
            try
            {
                if (arr.getSize() == 0)
                {
                    throw string("The array is empty.");
                }

                arr.clear();

                cout << "\n\t\t\tElements from the array have been cleared/deleted.\n";
            }
            catch (const string& error)
            {
                cout << "\n\t\t\t" << error << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case '0':
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

}


void option3()
{
    bool running = true;
    while (running)
    {
        system("cls");
        cout << "\n\t\t3>> Application using hashing";
        cout << "\n\t\t" << string(80, char(205));
        cout << "\n\t\t\tA> Read data file, hash and insert into the dynamic array";
        cout << "\n\t\t\tB> Search an element from the dynamic array";
        cout << "\n\t\t\tC> Insert an element into the dynamic array";
        cout << "\n\t\t\tD> Remove an element from the dynamic array";
        cout << "\n\t\t\tE> Display all records from the array";
        cout << "\n\t\t" << string(80, char(196));
        cout << "\n\t\t\t0> return";
        cout << "\n\t\t" << string(80, char(205));

        char option = toupper(inputChar("\n\t\t\tOption: ", static_cast<string>("A,B,C,D,E,0")));
        switch (option)
        {
        case 'A':
        {
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'B':
        {
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'C':
        {
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'D':
        {
            cout << "\n\n";
            system("pause");
            break;
        }
        case 'E':
        {
            cout << "\n\n";
            system("pause");
            break;
        }
        case '0':
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

}

