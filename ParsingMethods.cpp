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
#include "FileData.cpp"
#include "FunctionData.cpp"

class ParsingMethods
{
    public:

        static int getNumCommasInString(string paramList) {
            int numCommas = 0;
            for(int i = 0; i < paramList.size(); i++)
                if (paramList[i] == ',')
                    numCommas++;
            return numCommas;
        }


        static int getNumParamsFromFuncSignature(string firstLineOfFunc)
        {
            //Ex of firstLineOfFunc: 'int fun2(int a, int b, int c, int d){'
            //count number of commas between '(' and ')' and add one
            int indexOfOpeningParen = firstLineOfFunc.find('(');
            int indexOfClosingParen = firstLineOfFunc.find(')');
            //check if '(' and ')' are right next to each other (means no params)
            if(indexOfClosingParen - indexOfOpeningParen == 1)
            {
                return 0;
            }
            else
            {
                string parameterListStr = firstLineOfFunc.substr(indexOfOpeningParen, indexOfClosingParen-indexOfOpeningParen+1);
                //count number of commas
                int numCommas = getNumCommasInString(parameterListStr);
                return numCommas + 1;
            }
        }


        static string getReturnTypeFromFuncSignature(string firstLineOfFunc)
        {
            //Ex of firstLineOfFunc: 'int fun2(int a, int b, int c, int d){'
            int indexOfFirstSpace = firstLineOfFunc.find(' ');
            string returnType = firstLineOfFunc.substr(0, indexOfFirstSpace);
            return returnType;

        }

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
                    regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{*");
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
                regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{*");
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


    //returns dict of funcName (key) and return type (value)
    static map<string, string> getReturnTypeForEachFunc()
    {
        map<string, string> returnTypeDict;
        fstream testFile;
        //ios:in for read operation
        testFile.open("TestFile.cpp", ios::in);
        if(testFile.is_open())
        {
            regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{*");
            string temp;
            string currFuncName = "";
            //traverses file line by line
            while(getline(testFile, temp))
            {
                //check: first line of func
                if(regex_search(temp, firstLineOfFuncRegex)) //if first line of a func found
                {
                    currFuncName = getFuncNameFromFuncSignature(temp);
                    string returnType = getReturnTypeFromFuncSignature(temp);
                    returnTypeDict[currFuncName] = returnType;
                }
            }
            testFile.close();
        }
        return returnTypeDict;
    }



    //returns dict of funcName (key) and numParams (value)
    static map<string, int> getNumParamsForEachFunc()
    {
        map<string, int> numParamsDict;
        fstream testFile;
        //ios:in for read operation
        testFile.open("TestFile.cpp", ios::in);
        if(testFile.is_open())
        {
            regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{*");
            string temp;
            string currFuncName = "";
            //traverses file line by line
            while(getline(testFile, temp))
            {
                //check: first line of func
                if(regex_search(temp, firstLineOfFuncRegex)) //if first line of a func found
                {
                    currFuncName = getFuncNameFromFuncSignature(temp);
                    int numParams = getNumParamsFromFuncSignature(temp);
                    numParamsDict[currFuncName] = numParams;
                }
            }
            testFile.close();
        }
        return numParamsDict;
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