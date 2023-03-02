/* Adit Goyal
 * CPSC 5910 - Refactoring
 *
 * Stores data for a test file
 */

#include <list>
#include "FunctionData.h"


#ifndef CODESMELLDETECTOR_FILEDATA_H
#define CODESMELLDETECTOR_FILEDATA_H


class FileData {
    public:
        FileData() {};
        //FunctionData list
        list<FunctionData> listOfFuncs;
        list<string> listOfFuncNames;



};


#endif //CODESMELLDETECTOR_FILEDATA_H
