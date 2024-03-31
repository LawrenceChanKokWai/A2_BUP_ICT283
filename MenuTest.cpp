
/**
* @file MenuTest.cpp
* @brief Menu Test execution file
*
* This file contains the execution unit test for Menu Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include<iostream>

#include "InputValidator.h"
#include "Processor.h"
#include "Menu.h"

using namespace std;

template<class T>
void TestOptionOne( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &year, unsigned &month );

template<class T>
void TestOptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &year, char &option );

template<class T>
void TestOptionThree( AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &month );

template<class T>
void TestOptionFour(
    AVL<T> &avl,
    AoAvlMap<T> &aoAvlMap,
    Menu<T> &menu,
    ofstream &outputFile,
    const string &filePath,
    unsigned &year);

template<class T>
void TestOptionFive( AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &month );


int main()
{
    string directoryPath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";

    const string filename = directoryPath + "data_source_test.txt";
    const string outFilePath = directoryPath + "WindTempSolarTestFile.csv";
    Vector<string> csvFilePath;
    AoAvlMap<SensorRecType> mapRecords;
    ifstream inFile( filename );
    ofstream outputFile( outFilePath );

    Processor::GetInstance();
    Processor::GetInstance().LoadCSVFilePathToVector( csvFilePath, inFile, filename );
    Processor::GetInstance().LoadCSVData( csvFilePath, mapRecords );

    InputValidator validator;
    SensorRecType sensorRecType;
    AVL<SensorRecType> avlRecords;

    Menu<SensorRecType> menu;
    unsigned year = 2014;
    unsigned month = 1;
    char optionTwo = '2';
    char optionThree = '3';

    TestOptionOne( avlRecords, mapRecords, menu, year, month );
    TestOptionTwo( avlRecords, mapRecords, menu, year, optionTwo );
    TestOptionThree( mapRecords, menu, month );
    TestOptionFour( avlRecords, mapRecords, menu, outputFile, outFilePath, year );


    return 0;
}

void Assert_Equal( bool condition, const string &message )
{
    if( condition )
    {
        cout << "[ PASS ]: " << message << endl;
    }
    else
    {
        cout << "[ FAIL ]: " << message << endl;
    }
}

template<class T>
void TestOptionOne( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &year, unsigned &month )
{
    cout << "Test on Option One: ";
    menu.OptionOne( avl, aoAvlMap, year, month );
}

template<class T>
void TestOptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &year, char &option )
{
    cout << "Test on Option Two: " << '\n';
    menu.OptionTwo( avl, aoAvlMap, year, option );
}

template<class T>
void TestOptionThree( AoAvlMap<T> &aoAvlMap, Menu<T> &menu, unsigned &month )
{
    cout << "Test on Option Three: " << endl;
    menu.OptionThree( aoAvlMap, month );
}

template<class T>
void TestOptionFour(
    AVL<T> &avl,
    AoAvlMap<T> &aoAvlMap,
    Menu<T> &menu,
    ofstream &outputFile,
    const string &filePath,
    unsigned &year)
{
    cout << "Test on Option Four: " << endl;
    menu.OptionFour( avl, aoAvlMap, outputFile, filePath, year );
}

