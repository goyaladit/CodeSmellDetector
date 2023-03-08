/* Adit Goyal
 * CPSC 5910 - Refactoring
 *
 * Stores data for a test file
 */

#include <list>
#include "FunctionData.cpp"
#include <vector>


#ifndef CODESMELLDETECTOR_FILEDATA_H
#define CODESMELLDETECTOR_FILEDATA_H


class FileData {
    public:
        FileData() {};
        //FunctionData list
        vector<FunctionData> listOfFuncs;
        vector<string> listOfFuncNames;



        void printLOCField()
        {
            cout << "Printing LOC:" << endl;
            for(FunctionData func: this->listOfFuncs)
            {
                func.printLOC();
            }
        }

        void printReturnTypeField()
        {

            cout << "Printing return type:" << endl;
            for(FunctionData func: this->listOfFuncs)
            {
                func.printReturnType();
            }
        }

        void printNumParamsField()
        {

            cout << "Printing num params:" << endl;
            for(FunctionData func: this->listOfFuncs)
            {
                func.printNumParams();
            }
        }

        bool doesNameExistInListOfFuncNames(string name)
        {
            for(string x: listOfFuncNames)
            {
                if(x == name)
                    return true;
            }
            return false;
        }



};


#endif //CODESMELLDETECTOR_FILEDATA_H
