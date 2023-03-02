/* Adit Goyal
 * CPSC 5910
 *
 * Contains functions for parsing a .cpp file
 */


using namespace std;
#include <iostream>
#include <fstream>
#include "FileData.h"
#include "FunctionData.h"

class ParsingMethods
{


    public:
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
                    cout << temp << endl;
                }
            }


        }

};