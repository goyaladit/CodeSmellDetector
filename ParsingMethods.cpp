/* Adit Goyal
 * CPSC 5910
 *
 * Contains functions for parsing a .cpp file
 */


using namespace std;
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include<map>
#include "FileData.h"
#include "FunctionData.h"

class ParsingMethods
{
    public:


        static string getFuncNameFromFuncSignature(string firstLineOfFunc)
        {
            int indexOfFirstSpace = firstLineOfFunc.find(' ');
            int indexOfParenthesis = firstLineOfFunc.find('(');
            string funcName = firstLineOfFunc.substr(indexOfFirstSpace + 1, indexOfParenthesis-indexOfFirstSpace-1);
            return funcName;
        }

        static list<string> getListOfFuncNames() {
            list<string> funcNames;
            fstream testFile;
            //ios:in for read operation
            testFile.open("TestFile.cpp", ios::in);
            if (testFile.is_open()) {
                string temp;
                while (getline(testFile, temp)) {
                    regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{");
                    if (regex_search(temp, firstLineOfFuncRegex)) { //regex matched
                        //string temp contains first line of func
                        //code for pulling out func name
                        //ASSUMPTION - function first line is exactly of this form: "int fun1(int a, int b, int c, int d){"
                        string funcName = getFuncNameFromFuncSignature(temp);
                        funcNames.push_back(funcName);
                    }
                }
                testFile.close();
            }
            return funcNames;
        }


        //returns dict of funcName (key) and LOC (value)
        static map<string, int> getLinesOfCodeForEachFunc()
        {
            map<string, int> linesOfCodeDict;
            fstream testFile;
            //ios:in for read operation
            testFile.open("TestFile.cpp", ios::in);
            if(testFile.is_open())
            {
                regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{");
                regex closingBracketOfFuncRegex("^\\}");
                regex emptyLineRegex("^$");

                string temp;
                bool areCurrentlyInsideAFunc = false;
                int linesInCurrFunc = 0;
                string currFuncName = "";
                //traverses file line by line
                while(getline(testFile, temp))
                {
                    //check: first line of func
                    if(regex_search(temp, firstLineOfFuncRegex)) //if first line of a func found
                    {
                        if(!areCurrentlyInsideAFunc)
                        {
                            areCurrentlyInsideAFunc = true;
                            linesInCurrFunc = 0;
                            currFuncName = getFuncNameFromFuncSignature(temp);
                        }
                    }
                    //if inside a func and not an empty line
                    if(areCurrentlyInsideAFunc && !regex_search(temp, emptyLineRegex))
                        linesInCurrFunc++;

                    //check: closing bracket of func
                    if(regex_search(temp, closingBracketOfFuncRegex)) //if ending bracket found
                    {
                        linesOfCodeDict[currFuncName] = linesInCurrFunc;
                        areCurrentlyInsideAFunc = false;
                    }
                }
                testFile.close();
            }
            return linesOfCodeDict;
        }

};


/*
* Regex Notes:
* [^\s] = no whitespace
* ^ = beginning
* //w = word (letters and numbers)
* + = one or more
* "^[^\\s]\\w+\\s+\\w+\\(" = matches "int main("
 * [\s\S] = matches any character
 * ^[^\s]\w+\s+\w+\([\s\S]*\)[\s\S]*{ = matches "int main() {"
 * ^$ = matches empty string ""
 *
 *
*/