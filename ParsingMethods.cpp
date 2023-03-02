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
#include "FileData.h"
#include "FunctionData.h"

class ParsingMethods
{


    public:

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
                        int indexOfFirstSpace = temp.find(' ');
                        int indexOfParenthesis = temp.find('(');
                        string funcName = temp.substr(indexOfFirstSpace + 1, indexOfParenthesis-indexOfFirstSpace-1);
                        funcNames.push_back(funcName);

                        //*add func name to funcNames list
                    }

                }
            }

            return funcNames;
        }

        static void printLineByLine()
        {
            fstream testFile;
            //ios:in for read operation
            testFile.open("TestFile.cpp", ios::in);
            if(testFile.is_open())
            {
                string temp;
                while(getline(testFile, temp))
                {

                    cout << "WORKS!!" << endl;


                    regex b("^[^\\s]\\w+\\s+\\w+\\([\\s\\S]*\\)[\\s\\S]*\\{");
                    if(regex_search(temp, b))
                    {
                        cout << "Regex matched with the following: " << endl;
                        cout << temp << endl << endl << endl;
                    }

                }
            }


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
 *
 *
 *
*/