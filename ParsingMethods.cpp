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
#include <tuple>
#include<map>
#include <set>
#include "FileData.cpp"
#include "FunctionData.cpp"


const double JACCARD_SIMILARITY_THRESHOLD = 0.75;


class ParsingMethods
{


    const double SIMILARITY_THRESHOLD = 0.75;
    public:
        string fileName;
        ParsingMethods(string fileN="")
        {
            fileName = fileN;
        }

        string getCodeBlockOfFuncFromVectorOfFuncs(string funcToFind, vector<FunctionData> listOfFuncs)
        {
            for(int i = 0; i < listOfFuncs.size(); i++)
            {
                if(listOfFuncs[i].nameOfFunc == funcToFind)
                {
                    return listOfFuncs[i].codeBlock;
                }
            }

        }



        //compares each function with each other and checks for jaccard similarity being greater than 0.75
        void runDuplicateCodeDetection(vector<string> listOfFuncNames, vector<FunctionData> listOfFuncs)
        {
            //all combinations of funcs
            if(listOfFuncNames.size() == 1)
            {
                cout << "There's only one function and so code duplication can't be calculated" << endl;
            }
            else
            {
                vector<vector<string>> funcCombos = returnVectorOfCombinations(listOfFuncNames);
                for(int i = 0; i < funcCombos.size(); i++)
                {
                    string funcOne = funcCombos[i][0];
                    string funcTwo = funcCombos[i][1];
                    string codeBlockOne = getCodeBlockOfFuncFromVectorOfFuncs(funcOne, listOfFuncs);
                    string codeBlockTwo = getCodeBlockOfFuncFromVectorOfFuncs(funcTwo, listOfFuncs);
                    double jaccardNum = jaccardSimilarityNum(codeBlockOne, codeBlockTwo);
                    if(jaccardNum > JACCARD_SIMILARITY_THRESHOLD)
                    {
                        cout << funcOne << " and " << funcTwo << " are duplicated." << endl;
                    }
                }
            }

        }

        //only call if number of funcs is greater than 1
        static vector<vector<string>> returnVectorOfCombinations(vector<string> funcNames)
        {
            vector<vector<string>> returnVect;
            for(int i = 0; i < funcNames.size(); i++)
            {
                for(int j = i+1; j < funcNames.size(); j++)
                {
                    vector<string> temp {funcNames[i], funcNames[j]};
                    returnVect.push_back(temp);
    //            cout << funcNames[i] << ", " << funcNames[j] << endl;
                }
            }
            return returnVect;
        }


        //QUESTION: should codeblock of a function that's used for jaccard calculation include the function
        //signature or not?

        //returns dict<string, string> of funcName (key) and codeblock (value)
        map<string, string> getCodeBlockOfEachFunc()
        {
            map<string, string> codeBlockDict;
            fstream testFile;
            //ios:in for read operation
            testFile.open(this->fileName, ios::in);
            if(testFile.is_open())
            {
                regex firstLineOfFuncRegex("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{*");
                regex closingBracketOfFuncRegex("^\\}");
                regex emptyLineRegex("^$");

                string temp;
                bool areCurrentlyInsideAFunc = false;
                string codeBlockOfCurrFunc = "";
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
                            codeBlockOfCurrFunc = "";
                            currFuncName = getFuncNameFromFuncSignature(temp);
                        }
                    }
                    //if inside a func and not an empty line
                    if(areCurrentlyInsideAFunc)
                        codeBlockOfCurrFunc += temp;

                    //check: closing bracket of func
                    if(regex_search(temp, closingBracketOfFuncRegex)) //if ending bracket found
                    {
                        codeBlockDict[currFuncName] = codeBlockOfCurrFunc;
                        areCurrentlyInsideAFunc = false;
                    }
                }
                testFile.close();
            }
            return codeBlockDict;
        }




        /*  Created this function myself and referred to Python implementation in following link:
        * https://datascienceparichay.com/article/jaccard-similarity-python/
        * Input: string of functions
        */
        double jaccardSimilarityNum(string s1, string s2)
        {
            set<char> set1( s1.begin() , s1.end() );
            set<char> set2( s2.begin() , s2.end() );

            //intersection
            std::vector<char> intersectionVector;
            set_intersection(set1.begin(),set1.end(),set2.begin(),set2.end(), std::back_inserter(intersectionVector));

            //union
            std::vector<char> unionVector;
            set_union(set1.begin(), set1.end(),set2.begin(),set2.end(), std::back_inserter(unionVector));

            double intersectionLen = (double)intersectionVector.size();
//            cout << endl << "intersectionLen: " << intersectionLen << endl;
            double unionLen = (double)unionVector.size();
//            cout << endl << "unionLen: " << unionLen << endl << endl;

            return intersectionLen/unionLen;
        }

    

        int getNumCommasInString(string paramList) {
            int numCommas = 0;
            for(int i = 0; i < paramList.size(); i++)
                if (paramList[i] == ',')
                    numCommas++;
            return numCommas;
        }


        int getNumParamsFromFuncSignature(string firstLineOfFunc)
        {
            //Ex of firstLineOfFunc: 'int fun2(int a, int b, int c, int d){'
            //count number of commas between '(' and ')' and add one
            int indexOfOpeningParen = firstLineOfFunc.find('(');
            int indexOfClosingParen = firstLineOfFunc.find(')');

            //check with if there's any characters between '(' and ')'
            bool anyCharsBetweenOpeningClosingParens = false;
            for(int i = indexOfOpeningParen+1; i < indexOfClosingParen; i++)
            {
                if(firstLineOfFunc[i] != ' ')
                {
                    anyCharsBetweenOpeningClosingParens = true;
                }
            }

            if(!anyCharsBetweenOpeningClosingParens)
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


        string getReturnTypeFromFuncSignature(string firstLineOfFunc)
        {
            //Ex of firstLineOfFunc: 'int fun2(int a, int b, int c, int d){'
            int indexOfFirstSpace = firstLineOfFunc.find(' ');
            string returnType = firstLineOfFunc.substr(0, indexOfFirstSpace);
            return returnType;

        }

        string getFuncNameFromFuncSignature(string firstLineOfFunc)
        {
            int indexOfFirstSpace = firstLineOfFunc.find(' ');
            int indexOfParenthesis = firstLineOfFunc.find('(');
            string funcName = firstLineOfFunc.substr(indexOfFirstSpace + 1, indexOfParenthesis-indexOfFirstSpace-1);
            return funcName;
        }

        vector<string> getListOfFuncNames() {
            vector<string> funcNames;
            fstream testFile;
            //ios:in for read operation
            testFile.open(this->fileName, ios::in);
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
        map<string, int> getLinesOfCodeForEachFunc()
        {
            map<string, int> linesOfCodeDict;
            fstream testFile;
            //ios:in for read operation
            testFile.open(this->fileName, ios::in);
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
    map<string, string> getReturnTypeForEachFunc()
    {
        map<string, string> returnTypeDict;
        fstream testFile;
        //ios:in for read operation
        testFile.open(this->fileName, ios::in);
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
    map<string, int> getNumParamsForEachFunc()
    {
        map<string, int> numParamsDict;
        fstream testFile;
        //ios:in for read operation
        testFile.open(this->fileName, ios::in);
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