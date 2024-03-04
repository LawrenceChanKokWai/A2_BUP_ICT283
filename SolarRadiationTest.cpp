
/**
* @file SolarRadiationTest.cpp
* @brief SolarRadiation Test execution file
*
* This file contains the execution unit test for SolarRadiation Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "SolarRadiation.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput );
void TestDefaultConstructor( const SolarRadiation &solarRadiation );
void TestParameterizedConstructor( const SolarRadiation &solarRadiation, const float &validMeasurement  );
void TestSetters( SolarRadiation &solarRadiation, const float &validMeasurement );
void TestGetters( const SolarRadiation &solarRadiation, const float &validMeasurement );
void TestConvertingSolarRadiation( const SolarRadiation &solarRadiation, float &reading );

int main()
{
    ostringstream outputStream;
    istringstream inputStream;
    float validMeasurement = 12.12;
    float newValidMeasurement = 11.11;
    float reading = 30.0f;
    SolarRadiation testSolarRadiation;
    SolarRadiation solarRadiationValid( validMeasurement );

    TestDefaultConstructor( testSolarRadiation );
    TestParameterizedConstructor( solarRadiationValid, validMeasurement );
    TestSetters( testSolarRadiation, newValidMeasurement );
    TestGetters( testSolarRadiation, newValidMeasurement );

    TestConvertingSolarRadiation( testSolarRadiation, reading );

    return 0;
}

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput )
{
    cout << title;
    cout << setw(2) << " " << description;
    cout << setw(2) << " " << expectedOutput;
    cout << setw(2) << " " << ( condition ? "[ PASS ]" : "[ FAIL ]") << "\n\n";
}

void TestDefaultConstructor( const SolarRadiation &solarRadiation )
{
    Assert( solarRadiation.GetMeasurement() == 0,
            "Test 1: Default Constructor\n",
            "Test Data/Values: None\n",
            "Expected Output: solar radiation initialized to INITIAL_VALUE\n" );
}

void TestParameterizedConstructor( const SolarRadiation &solarRadiation, const float &validMeasurement )
{
    Assert( solarRadiation.GetMeasurement() == validMeasurement,
            "Test 2: Constructor with Valid Input Parameters\n",
            "Test Data/Values: solar radiation = 12.12\n",
            "Expected Output: solar radiation = 12.12\n" );
}

void TestSetters( SolarRadiation &solarRadiation, const float &validMeasurement )
{
    solarRadiation.SetMeasurement( validMeasurement );
    Assert( solarRadiation.GetMeasurement() == validMeasurement,
            "Test 3: Setters\n",
            "Test Data/Values: solar radiation = 11.11\n",
            "Expected Output: solar radiation = 11.11\n");
}

void TestGetters( const SolarRadiation &solarRadiation, const float &validMeasurement )
{
    Assert( solarRadiation.GetMeasurement() == validMeasurement,
            "Test 4: Getters\n",
            "Test Data/Values: solar radiation = 11.11\n",
            "Expected Output: solar radiation = 11.11\n");
}

void TestConvertingSolarRadiation( const SolarRadiation &solarRadiation, float &reading )
{
    float expected = solarRadiation.ConvertUnit( reading );
    cout     << "Test 5: Converting SolarRadiation\n"
                << "Test Data/Values: solarRadiation = 30.0\n"
                << "Expected Output: solarRadiation = 0.005\n"
                << "Actual Output: " << expected << endl;
}

