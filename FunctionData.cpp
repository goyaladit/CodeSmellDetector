/*
 * Stores data for one function
 */

#include <list>
#include <tuple>
#include <string>
using namespace std;

#ifndef CODESMELLDETECTOR_FUNCTIONDATA_H
#define CODESMELLDETECTOR_FUNCTIONDATA_H

class FunctionData {
    public:
        FunctionData() { }
        string nameOfFunc;
        //func Parameter List
        int numParameters;
        //int LOC
        int linesOfCode;
        //func return type
        string returnType;
        //string that contains code block of func
        string codeBlock;

        void printLOC()
        {
            cout << nameOfFunc << ":  " << linesOfCode << endl;
        }

        void printReturnType()
        {
            cout << nameOfFunc << ":  " << returnType << endl;
        }

        void printNumParams()
        {
            cout << nameOfFunc << ":  " << numParameters << endl;
        }

};

#endif //CODESMELLDETECTOR_FUNCTIONDATA_H
