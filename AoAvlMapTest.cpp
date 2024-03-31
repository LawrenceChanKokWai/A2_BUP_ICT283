/**
* @file AoAvlMapTest.cpp
* @brief AoAvlMap Test execution file
*
* This file contains the execution unit test for AoAvlMap Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include<iostream>

#include "AoAvlMap.h"

using namespace std;


void Assert_Equals( bool condition, const string &message );

template<class T>
void Display( const T &node );

template<class T>
void TestInsertData( AoAvlMap<T> &testMap, T &records );

template<class T>
void TestDisplayData( AoAvlMap<T> &testMap );

template<class T>
void TestDisplayYearMonthData( AoAvlMap<T> &testMap, const unsigned &year, const unsigned &month );

template<class T>
void TestInOrderTraversalSum(AoAvlMap<T> &testMap, const unsigned &year, const unsigned &month );

template<class T>
void TestInOrderTraversalSSD( AoAvlMap<T> &testMap );

void TestExtractMeasurements();

template<class T>
void TestIsEmpty( AoAvlMap<T> &testMap );

template<class T>
void TestDestroyMap( AoAvlMap<T> &testMap );

int main()
{

    AoAvlMap<SensorRecType> testMap;
    TestIsEmpty( testMap );

    Date date(11,10,2020);
    Time time(11,20);
    WindSpeed windSpeed(20.2);
    Temperature temperature(11.11);
    SolarRadiation solarRadiation(21.11);

    Date otherDate(11,10,2020);
    Time otherTime(11,30);
    WindSpeed otherWindSpeed(22.2);
    Temperature otherTemperature(11.11);
    SolarRadiation otherSolarRadiation(33.33);

    SensorRecType records( date, time, windSpeed, solarRadiation, temperature );
    SensorRecType otherRecords( otherDate, otherTime, otherWindSpeed, otherSolarRadiation, otherTemperature );

    TestInsertData( testMap, records );
    TestInsertData( testMap, otherRecords );

    //TestDisplayData( testMap );
    TestDisplayYearMonthData( testMap, 2020, 10 );

    TestInOrderTraversalSum( testMap, 2020, 10 );

    TestInOrderTraversalSSD( testMap );

    TestExtractMeasurements();

    TestDestroyMap( testMap );

    return 0;
}

void Assert_Equals( bool condition, const string &message )
{
    cout << (condition ? "\t-->[ PASS ] " : "\t-->[ FAIL ] ") << message << endl;
}

template<class T>
void TestInsertData( AoAvlMap<T> &testMap, T &records )
{
    cout << "Test On Inserting Data into map, array of avl: " << endl;
    Assert_Equals( testMap.InsertSensorData( records ),  "Data Inserting" );
    cout << endl;
}

template<class T>
void TestDisplayData( AoAvlMap<T> &testMap )
{
    // Verify the state of the map after insertion
    SensorRecType sensorRec;
    auto sensorDataMap = testMap.GetSensorData();

    cout << "Display Data After Insertion: " << endl;
    for (const auto& entry : sensorDataMap)
    {
        cout << "\tYear: " << entry.first << endl;
        for (unsigned i = 0; i < AoAvlMap<SensorRecType>::NUM_MTH; ++i)
        {
            auto& avl = entry.second[i];
            cout << '\t' << '\t' << sensorRec.GetSensorDate().GetMonthInStr(i + 1) << ": ";
            if (!avl.IsEmpty())
            {
                // Iterate through AVL tree and print data
                // Modify this part according to your AVL implementation
                avl.InOrderTraversal(Display);
            }
            else
            {
                cout << "Empty";
            }
            cout << endl;
        }
    }
}

template<class T>
void TestDisplayYearMonthData( AoAvlMap<T> &testMap, const unsigned &year, const unsigned &month )
{
    // Verify the state of the map after insertion
    SensorRecType sensorRec;
    float sumWindSpeed = 0.0;
    float sumSolarRadiation = 0.0;
    float sumTemperature = 0.0;

    auto sensorDataMap = testMap.GetSensorData();

    cout << "Display Data With user year and month: " << endl;
    for (const auto& entry : sensorDataMap)
    {
        cout << "\tYear: " << entry.first << endl;
        if( year == entry.first )
        {
            for (unsigned i = 0; i < AoAvlMap<SensorRecType>::NUM_MTH; ++i)
            {
                if( month-1 == i )
                {
                    auto& avl = entry.second[i];
                    cout << '\t' << '\t' << sensorRec.GetSensorDate().GetMonthInStr(i + 1) << ": " << endl;

                    if (!avl.IsEmpty())
                    {
                        // Iterate through AVL tree and print data
                        // Modify this part according to your AVL implementation
                        avl.InOrderTraversal(Display);
                        //cout << avl.GetRoot()->m_object.GetSensorWindSpeed().GetMeasurement() << endl;
                        testMap.InOrderTraversalSum(testMap.GetSensorData()[year][month - 1].GetRoot(), SensorMeasurementType::WIND_SPEED, sumWindSpeed);
                        testMap.InOrderTraversalSum(testMap.GetSensorData()[year][month - 1].GetRoot(), SensorMeasurementType::SOLAR_RADIATION, sumSolarRadiation);
                        testMap.InOrderTraversalSum(testMap.GetSensorData()[year][month - 1].GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, sumTemperature);

                        unsigned count = avl.GetTreeNodes();

                        cout << '\t' << '\t' << '\t' << "SumOfWindSpeed: " << sumWindSpeed << "( " << sumWindSpeed / count << " )"  << '\n'
                                << '\t' << '\t' << '\t' << "SumOfSolarRadiation: " << sumSolarRadiation << '\n'
                                << '\t' << '\t' << '\t' << "SumTemperature: " << sumTemperature << endl;

                    }
                    else
                    {
                        cout << "Empty";
                    }
                    cout << endl;
                }
            }
        }
        else
        {
            cout << endl;
            cout << "Year is not Found: No Data" << endl;
        }
    }
}


template<class T>
void TestInOrderTraversalSum(AoAvlMap<T> &testMap, const unsigned &year, const unsigned &month )
{
    cout << "\nTest On InOrderTraversalSum: " << endl;
    float sum = 0.0;
    testMap.InOrderTraversalSum(testMap.GetSensorData()[year][month - 1].GetRoot(), SensorMeasurementType::WIND_SPEED, sum);
    float expectedSum = 42.4; // 20.2 + 22.2
    Assert_Equals(sum == expectedSum, "InOrderTraversalSum test passed!");
}

template<class T>
void TestInOrderTraversalSSD( AoAvlMap<T> &testMap )
{
    cout << "\nTest On InOrderTraversalSSD: " << endl;
    // Assuming you have an instance of AoAvlMap<SensorRecType> named aoAvlMap

    // Get the AVL tree for a specific year and month
    unsigned year = 2020;
    unsigned month = 10; // July
    auto& avlTree = testMap.GetSensorData()[year][month - 1]; // Adjust month to be zero-indexed

    // Define the sensor measurement type for which you want to calculate the sample standard deviation
    SensorMeasurementType sensorType = SensorMeasurementType::WIND_SPEED;

    // Calculate the sample standard deviation
    unsigned count = testMap.GetSensorData()[year][month - 1].GetTreeNodes();
    float sampleStandardDeviation = testMap.CalculateSampleStandardDeviation(avlTree.GetRoot(), sensorType, count);

    // Output the result
    cout << "Sample standard deviation of wind speed for " << month << "/" << year << ": " << sampleStandardDeviation << '\n' << endl;
}

void TestExtractMeasurements()
{
    cout << "Test on Extracting Data from AVL and insert to Vector: " << endl;
    AoAvlMap<SensorRecType> testMap;
    AVL<SensorRecType> sensorRecords;
    Vector<float> windMeasurements;

    Date date1(2022, 3, 20);
    Time time1(8, 0);
    WindSpeed windSpeed1(15.5);
    Temperature temperature1(25.0);
    SolarRadiation solarRadiation1(550.0);
    SensorRecType record1(date1, time1, windSpeed1, solarRadiation1, temperature1);
    testMap.InsertSensorData(record1);

    Date date2(2022, 3, 20);
    Time time2(9, 0);
    WindSpeed windSpeed2(18.2);
    Temperature temperature2(26.0);
    SolarRadiation solarRadiation2(600.0);
    SensorRecType record2(date2, time2, windSpeed2, solarRadiation2, temperature2);
    testMap.InsertSensorData(record2);


   // Get the sensor data map
    const auto& sensorDataMap = testMap.GetSensorData();

    // Loop through all entries in the sensor data map
    for (const auto& entry : sensorDataMap)
    {
        for (const auto& avl : entry.second)
        {
            // Extract wind speed measurements for the current AVL tree
            testMap.ExtractMeasurements(avl.GetRoot(), SensorMeasurementType::WIND_SPEED, windMeasurements);
        }
    }
    // Verify the number of wind speed measurements extracted
    Assert_Equals(windMeasurements.GetUsed() == 2, "Correct number of wind speed measurements stored in vector");
    cout << endl;
}

//++++ For displaying traversal operation +++
template<class T>
void Display( const T &node )
{
    cout << '\n' << '\t' << '\t' << '\t' << node << " ";
}

template<class T>
void TestIsEmpty( AoAvlMap<T> &testMap )
{
    cout << "Test if MAP is empty: " << endl;
    Assert_Equals( testMap.IsEmpty(), "Map is empty" );
    cout << endl;
}

template<class T>
void TestDestroyMap( AoAvlMap<T> &testMap )
{
    cout << "Test on destroying previous data on Map" << endl;
    Assert_Equals( !testMap.IsEmpty(), "[BEFORE Destroying]: Map is not empty");
    testMap.Destroy();
    Assert_Equals( testMap.IsEmpty(), "[AFTER Destroying]: Map has destroyed previous data.");
    cout << endl;
}


