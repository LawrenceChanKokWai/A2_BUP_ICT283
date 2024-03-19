/**
* @file WindSpeedTest.cpp
* @brief WindSpeed Test execution file
*
* This file contains the execution unit test for WindSpeed Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "WindSpeed.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput );
void TestDefaultConstructor( const WindSpeed &windspeed );
void TestParameterizedConstructor( const WindSpeed &windspeed, const float &validMeasurement  );
void TestSetters( WindSpeed &windspeed, const float &validMeasurement );
void TestGetters( const WindSpeed &windspeed, const float &validMeasurement );
void TestConvertingWindSpeed( const WindSpeed &windspeed, float &reading );


int main()
{
    ostringstream outputStream;
    istringstream inputStream;
    float validMeasurement = 12.12;
    float newValidMeasurement = 11.11;
    float readingForConverting = 30.0;
    WindSpeed testWindSpeed;
    WindSpeed windSpeedValid( validMeasurement );

    TestDefaultConstructor( testWindSpeed );
    TestParameterizedConstructor( windSpeedValid, validMeasurement );
    TestSetters( testWindSpeed, newValidMeasurement );
    TestGetters( testWindSpeed, newValidMeasurement );
    TestConvertingWindSpeed( testWindSpeed, readingForConverting );

    return 0;
}

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput )
{
    cout << title;
    cout << setw(2) << " " << description;
    cout << setw(2) << " " << expectedOutput;
    cout << setw(2) << " " << ( condition ? "[ PASS ]" : "[ FAIL ]") << "\n\n";
}

void TestDefaultConstructor( const WindSpeed &windSpeed )
{
    Assert( windSpeed.GetMeasurement() == 0,
            "Test 1: Default Constructor\n",
            "Test Data/Values: None\n",
            "Expected Output: windspeed initialized to INITIAL_VALUE\n" );
}

void TestParameterizedConstructor( const WindSpeed &windspeed, const float &validMeasurement )
{
    Assert( windspeed.GetMeasurement() == validMeasurement,
            "Test 2: Constructor with Valid Input Parameters\n",
            "Test Data/Values: windspeed = 12.12\n",
            "Expected Output: windspeed = 12.12\n" );
}

void TestSetters( WindSpeed &windspeed, const float &validMeasurement )
{
    windspeed.SetMeasurement( validMeasurement );
    Assert( windspeed.GetMeasurement() == validMeasurement,
            "Test 3: Setters\n",
            "Test Data/Values: windspeed = 11.11\n",
            "Expected Output: windspeed = 11.11\n");
}

void TestGetters( const WindSpeed &windspeed, const float &validMeasurement )
{
    Assert( windspeed.GetMeasurement() == validMeasurement,
            "Test 4: Getters\n",
            "Test Data/Values: windspeed = 11.11\n",
            "Expected Output: windspeed = 11.11\n");
}

void TestConvertingWindSpeed( const WindSpeed &windspeed, float &reading )
{
    float expected = 108.0;

    Assert( windspeed.ConvertUnit( reading ) == expected,
            "Test 5: Converting WindSpeed to kWh/m2\n",
            "Test Data/Values: windspeed = 30.0\n",
            "Expected Output: windspeed = 108.0\n");
}

