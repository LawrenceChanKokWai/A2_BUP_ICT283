/**
* @file MeasurementTest.cpp
* @brief Measurement Test execution file
*
* This file contains the execution unit test for Measurement Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "Measurement.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput );
void TestDefaultConstructor( const Measurement &measurement );
void TestParameterizedConstructor( const Measurement &measurement, const float &validMeasurement  );
void TestSetters( Measurement &measurement, const float &validMeasurement );
void TestGetters( const Measurement &measurement, const float &validMeasurement );


int main()
{
    ostringstream outputStream;
    istringstream inputStream;
    float validMeasurement = 12.12;
    float newValidMeasurement = 11.11;
    Measurement testMeasurement;
    Measurement measurementValid( validMeasurement );

    TestDefaultConstructor( testMeasurement );
    TestParameterizedConstructor( measurementValid, validMeasurement );
    TestSetters( testMeasurement, newValidMeasurement );
    TestGetters( testMeasurement, newValidMeasurement );

    return 0;
}

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput )
{
    cout << title;
    cout << setw(2) << " " << description;
    cout << setw(2) << " " << expectedOutput;
    cout << setw(2) << " " << ( condition ? "[ PASS ]" : "[ FAIL ]") << "\n\n";
}

void TestDefaultConstructor( const Measurement &measurement )
{
    Assert( measurement.GetMeasurement() == 0,
            "Test 1: Default Constructor\n",
            "Test Data/Values: None\n",
            "Expected Output: Measurement initialized to INITIAL_VALUE\n" );
}

void TestParameterizedConstructor( const Measurement &measurement, const float &validMeasurement )
{
    Assert( measurement.GetMeasurement() == validMeasurement,
            "Test 2: Constructor with Valid Input Parameters\n",
            "Test Data/Values: measurement = 12.12\n",
            "Expected Output: measurement = 12.12\n" );
}

void TestSetters( Measurement &measurement, const float &validMeasurement )
{
    measurement.SetMeasurement( validMeasurement );
    Assert( measurement.GetMeasurement() == validMeasurement,
            "Test 3: Setters\n",
            "Test Data/Values: measurement = 11.11\n",
            "Expected Output: measurement = 11.11\n");
}

void TestGetters( const Measurement &measurement, const float &validMeasurement )
{
    Assert( measurement.GetMeasurement() == validMeasurement,
            "Test 4: Getters\n",
            "Test Data/Values: measurement = 11.11\n",
            "Expected Output: measurement = 11.11\n");
}


