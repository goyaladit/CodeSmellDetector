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
 */


/*
 * ASSUMPTIONS:
 * - test file is named TestFile.cpp
 *
 */
using namespace std;
#include <iostream>
#include "FileData.cpp"
#include "FunctionData.cpp"
#include "ParsingMethods.cpp"
#include <regex>
#include <set>
#include <vector>
#include <w32api.h>
#include <unordered_set>

const int LONG_METHOD_NUM_LINES_THRESHOLD = 15;
const int LONG_PARAM_LIST_THRESHOLD = 3;


static void runLongParameterListDetection(FileData obj)
{
    vector<string> longParamFuncs;
    vector<int> longFuncsNumParams;
    for(int i = 0; i < obj.listOfFuncs.size(); i++)
    {
        if(obj.listOfFuncs[i].numParameters > LONG_PARAM_LIST_THRESHOLD)
        {
            longParamFuncs.push_back(obj.listOfFuncs[i].nameOfFunc);
            longFuncsNumParams.push_back(obj.listOfFuncs[i].numParameters);
        }
    }

    if(longParamFuncs.size() == 0)
    {
        cout << "None of the functions have a long parameter list" << endl;
    }
    else
    {
        for(int i = 0; i < longParamFuncs.size(); i++)
        {
            cout << longParamFuncs[i] << " has a long Parameter List, and it has "
                << longFuncsNumParams[i] << " parameters." << endl;
        }
    }
}

static void runLongMethodDetection(FileData obj)
{
    vector<string> longFuncs;
    vector<int> longFuncsLOC;
    for(int i = 0; i < obj.listOfFuncs.size(); i++)
    {
        if(obj.listOfFuncs[i].linesOfCode > LONG_METHOD_NUM_LINES_THRESHOLD)
        {
            longFuncs.push_back(obj.listOfFuncs[i].nameOfFunc);
            longFuncsLOC.push_back(obj.listOfFuncs[i].linesOfCode);
        }
    }

    if(longFuncs.size() == 0)
    {
        cout << "None of the functions is a Long Function" << endl;
    }
    else
    {
        for(int i = 0; i < longFuncs.size(); i++)
        {
            cout << longFuncs[i] << " is a Long Function, and it has "
                << longFuncsLOC[i] << " lines of code." << endl;
        }
    }
}


static void mainMenu(FileData obj)
{
    //*access list of functions from FileData obj
    cout << "Welcome to Code Smell Detection! The file you inputted contains the following methods/functions: " << endl;
    //*print out list of functions
    for(string name: obj.listOfFuncNames)
    {
        cout << name << " ";
        cout << endl;
    }
    bool exit = false;
    ParsingMethods parsingObj = *new ParsingMethods();

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

        if(userInput == "1")
        {
            runLongMethodDetection(obj);
        }
        else if(userInput == "2")
        {
            runLongParameterListDetection(obj);
        }
        else if(userInput == "3")
        {
            parsingObj.runDuplicateCodeDetection(obj.listOfFuncNames, obj.listOfFuncs);
        }
        else if(userInput == "4")
        {
            cout << "You chose Quit. Have a good day!" << endl;
            exit = true;
        }
        else
        {
            cout << "Please enter valid input (a number from 1-4).";
        }

    }
}



int main (int argc, char ** argv)
{
//    string fileName = argv[1];


    //d
    string fileName = "TestFile.cpp";


    ParsingMethods parseObj = *new ParsingMethods(fileName);
    //parse file and create FileData obj for it
    FileData file = *new FileData();
    //setting file.listOfFuncNames field
    file.listOfFuncNames = parseObj.getListOfFuncNames();
    //dictOfLOC is of form (key, value) -> (string, int) -> (funcName, LOC)
    map<string,int> dictOfLOC = parseObj.getLinesOfCodeForEachFunc();
    map<string,int> :: iterator iter;
    //creating FunctionData() objects in file.listOfFuncs field and setting FunctionData.linesOfCode field
    for(iter = dictOfLOC.begin(); iter != dictOfLOC.end(); ++iter)
    {
        FunctionData func = *new FunctionData();
        func.nameOfFunc = iter->first;
        func.linesOfCode = iter->second;
        file.listOfFuncs.push_back(func);
    }
//    file.printLOCField();
    //setting FunctionData.returnType field
    map<string, string> dictOfReturnType = parseObj.getReturnTypeForEachFunc();
    vector<FunctionData>::iterator iterOne;
    for (iterOne = file.listOfFuncs.begin(); iterOne != file.listOfFuncs.end(); ++iterOne) //traversing file.listOfFuncs
    {
        if(dictOfReturnType.count(iterOne->nameOfFunc)) //does nameOfFunc exist as key in dictOfReturnType
        {
            iterOne->returnType = dictOfReturnType[iterOne->nameOfFunc];
        }
    }
//    file.printReturnTypeField();

    //setting FunctionData.numParameters field
    map<string, int> dictOfNumParams = parseObj.getNumParamsForEachFunc();
    vector<FunctionData>::iterator iterTwo;
    for (iterTwo = file.listOfFuncs.begin(); iterTwo != file.listOfFuncs.end(); ++iterTwo) //traversing file.listOfFuncs
    {
        if(dictOfNumParams.count(iterTwo->nameOfFunc)) //does nameOfFunc exist as key in dictOfNumParams
        {
            iterTwo->numParameters = dictOfNumParams[iterTwo->nameOfFunc];
        }
    }
//    file.printNumParamsField();
    cout << endl << endl;

    //setting FunctionData.codeBlock field
    map<string, string> dictOfCodeBlocks = parseObj.getCodeBlockOfEachFunc();
    vector<FunctionData>::iterator iterThree;
    for (iterThree = file.listOfFuncs.begin(); iterThree != file.listOfFuncs.end(); ++iterThree) //traversing file.listOfFuncs
    {
        if(dictOfCodeBlocks.count(iterThree->nameOfFunc)) //does nameOfFunc exist as key in dictOfCodeBlocks
        {
            iterThree->codeBlock = dictOfCodeBlocks[iterThree->nameOfFunc];
        }
    }
    cout << endl << endl;
//    parseObj.printDuplicatedFunctions(file.listOfFuncNames, file.listOfFuncs);

    mainMenu(file);





    return 0;
}






