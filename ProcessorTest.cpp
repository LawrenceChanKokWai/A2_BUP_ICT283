/**
* @file ProcessorTest.cpp
* @brief Processor Test execution file
*
* This file contains the execution unit test for Processor Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include<iostream>

#include "Processor.h"

using namespace std;

void Assert_Equal( bool condition, const string &message );

template<class T>
void TestLoadCsvFilePathToVector( Vector<T> &csvFilePath );

template<class T>
void TestLoadCsvData( Vector<string> &csvFilePath, AoAvlMap<T> &aoAvlMap );

template<class T>
void TestReloadCsvData( AoAvlMap<T> &aoAvlMap, const string &filePath );

int main()
{
    Vector<string> csvFilePath;
    AoAvlMap<SensorRecType> testMap;

    string directoryPath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";
    const string filename = directoryPath + "data_source_test.txt";
    //const string outFilePath = directoryPath + "WindTempSolar.csv";

    ifstream input( filename );

    Processor::GetInstance();
    Processor::GetInstance().LoadCSVFilePathToVector( csvFilePath, input, filename );

    TestLoadCsvFilePathToVector( csvFilePath );
    TestLoadCsvData( csvFilePath, testMap );
    TestReloadCsvData( testMap, filename );

    return 0;
}

void Assert_Equal( bool condition, const string &message )
{
    if( condition )
    {
        cout << "\t[ PASS ]: " << message << endl;
    }
    else
    {
        cout << "\t[ FAIL ]: " << message << endl;
    }
}

template<class T>
void TestLoadCsvFilePathToVector( Vector<T> &csvFilePath )
{
    cout << "Test on csv file path loading to vector: " << endl;
    Assert_Equal( csvFilePath.GetUsed() == 3, "Csv File Path Loading to Vector" );
    cout << endl;
}

template<class T>
void TestLoadCsvData( Vector<string> &csvFilePath, AoAvlMap<T> &aoAvlMap )
{
    cout << "Test on loading csv data into the map: " << endl;
    Processor::GetInstance().LoadCSVData( csvFilePath, aoAvlMap );
    cout << endl;
}

template<class T>
void TestReloadCsvData( AoAvlMap<T> &aoAvlMap, const string &filePath )
{
    cout << "Test on reloading csv data into the map" << endl;
    Processor::GetInstance().ReloadData( aoAvlMap, filePath );
    cout << endl;
}

