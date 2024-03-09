#include<iostream>

#include "Processor.h"

using namespace std;

int main()
{

    string directoryPath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";

    const string filename = directoryPath + "data_source.txt";
    const string outFilePath = directoryPath + "WindTempSolar.csv";
    vector<string> csvFilePath;
    AoAvlMap<SensorRecType> mapAoAvl;
    ifstream inFile( filename );
    ofstream outputFile( outFilePath );

    Processor::GetInstance();
    Processor::GetInstance().LoadCSVFilePathToVector( csvFilePath, inFile, filename );
    Processor::GetInstance().LoadCSVData( csvFilePath, mapAoAvl );

    return 0;
}
