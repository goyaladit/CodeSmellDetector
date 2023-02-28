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
        //func Parameter List
        list<tuple<string, string>> parameterList;
        //int LOC
        int linesOfCode;
        //func return type
        string returnType;
        //string that contains code block of func
        string codeBlock;


};

#endif //CODESMELLDETECTOR_FUNCTIONDATA_H
