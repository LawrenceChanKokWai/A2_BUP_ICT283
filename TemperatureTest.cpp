
/**
* @file TemperatureTest.cpp
* @brief Temperature Test execution file
*
* This file contains the execution unit test for Temperature Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "Temperature.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput );
void TestDefaultConstructor( const Temperature &temperature );
void TestParameterizedConstructor( const Temperature &temperature, const float &validMeasurement  );
void TestSetters( Temperature &temperature, const float &validMeasurement );
void TestGetters( const Temperature &temperature, const float &validMeasurement );
void TestConvertingFahrenheitToDegreeC( const Temperature &temperature, float &reading );

int main()
{
    ostringstream outputStream;
    istringstream inputStream;
    float validMeasurement = 12.12;
    float newValidMeasurement = 11.11;
    float reading = 118.4;
    Temperature testTemperature;
    Temperature temperatureValid( validMeasurement );

    TestDefaultConstructor( testTemperature );
    TestParameterizedConstructor( temperatureValid, validMeasurement );
    TestSetters( testTemperature, newValidMeasurement );
    TestGetters( testTemperature, newValidMeasurement );
    TestConvertingFahrenheitToDegreeC( testTemperature, reading );

    return 0;
}

void Assert( bool condition, const string &title, const string &description, const string &expectedOutput )
{
    cout << title;
    cout << setw(2) << " " << description;
    cout << setw(2) << " " << expectedOutput;
    cout << setw(2) << " " << ( condition ? "[ PASS ]" : "[ FAIL ]") << "\n\n";
}

void TestDefaultConstructor( const Temperature &temperature )
{
    Assert( temperature.GetMeasurement() == 0,
            "Test 1: Default Constructor\n",
            "Test Data/Values: None\n",
            "Expected Output: temperature initialized to INITIAL_VALUE\n" );
}

void TestParameterizedConstructor( const Temperature &temperature, const float &validMeasurement )
{
    Assert( temperature.GetMeasurement() == validMeasurement,
            "Test 2: Constructor with Valid Input Parameters\n",
            "Test Data/Values: temperature = 12.12\n",
            "Expected Output: temperature = 12.12\n" );
}

void TestSetters( Temperature &temperature, const float &validMeasurement )
{
    temperature.SetMeasurement( validMeasurement );
    Assert( temperature.GetMeasurement() == validMeasurement,
            "Test 3: Setters\n",
            "Test Data/Values: temperature = 11.11\n",
            "Expected Output: temperature = 11.11\n");
}

void TestGetters( const Temperature &temperature, const float &validMeasurement )
{
    Assert( temperature.GetMeasurement() == validMeasurement,
            "Test 4: Getters\n",
            "Test Data/Values: temperature = 11.11\n",
            "Expected Output: temperature = 11.11\n");
}

void TestConvertingFahrenheitToDegreeC( const Temperature &temperature, float &reading )
{
    float expected = temperature.ConvertUnit( reading );
    cout     << "Test 5: Converting Fahrenheit To DegreeC\n"
                << "Test Data/Values: Fahrenheit = 118.4\n"
                << "Expected Output: DegreeC = 48.0\n"
                << "Actual Output: " << expected << endl;
}

