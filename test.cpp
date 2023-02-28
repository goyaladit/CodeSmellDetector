/* Adit Goyal
 * CPSC 5910 - Refactoring
 *
 * List of Tasks:
 * - Finish "List of Tasks"
 * - define data structure for holding
 *         > functions in a file
 *              > code block for each function (lines of code)
 *              > parameter list of each function
 *              > return type of function
 *              > metrics related to each function (i.e.
 *              LOC, etc.)
 *         > a file or class
 *              > should hold functions in it
 *
 * - code for storing a test file as a data structure obj
 *      > reads test file line by line
 *      > create FileData obj for file
 *      > creates FunctionData obj for each func
 *      > parsing notes
 *          - detection of file beginning
 *          - detection of function beginning (part of class or not,
 *          public/private. etc.)
 *          - don't count empty lines in LOC
 *          - detecting parameter type and name (store each
 *          param as tuple)
 *          -
 * - figure out metric for similarity between code fragments
 *      > function for calculating metric
 * - code for UI
 *         > prints out list of all functions
 *         > Choosing detection of long method, long param list,
 *         or duplicated code
 *         > back to main menu after completing an action (loop)
 *         > option to 'Quit' in main menu
 * - code to handle invalid input (ask the prof. what is considered
 * invalid input)
 * - define assumptions (ask prof. what you can assume)
 *
 *
 *

 */
using namespace std;
#include <iostream>
#include "FileData.h"
#include "FunctionData.h"

static void mainMenu(FileData obj)
{
    //*access list of functions from FileData obj
    cout << "Welcome to Code Smell Detection! The file you input contains the following methods/functions: " << endl;
    //*print out list of functions
    bool exit = false;
    while(!exit)
    {
        cout << "Please choose what you want to do now (enter a number):" << endl;
        cout << "1. Long Method/Function Detection\n" <<
                "2. Long Parameter List Detection\n" <<
                "3. Duplicated Code Detection\n" <<
                "4. Quit\n"
                << endl;
        string userInput = "";
        cin >> userInput;

        //del
        cout << "User Input is " << userInput << endl;

//        if(userInput == "1")
//            ...
//        else if(userInput == "2")
//            ...
//        else if(userInput == "3")
//            ...
//        else if(userInput == "4")
//            ...
//        else
//            ...

    }
}

int main (int argc, char ** argv)
{
    //parse file and create FileData obj for it
    //mainMenu(FileData)

    //d
    mainMenu(*new FileData);

    return 0;
}