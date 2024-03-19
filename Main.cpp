/**
* @file Main.cpp
* @brief Entry point for the assignment. The main execution file.
*
* This file contains the entry point of execution for assignment one.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include <iostream>
#include<iomanip>
#include<conio.h>
#include<cstdlib>

#include "InputValidator.h"
#include "Processor.h"

using namespace std;

int main()
{
    string directoryPath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";

    const string filename = directoryPath + "data_source.txt";
    const string outFilePath = directoryPath + "WindTempSolar.csv";
    Vector<string> csvFilePath;
    AoAvlMap<SensorRecType> mapAov;
    vector<pair<float, string>> highestSolarRadiations;
    ifstream inFile( filename );
    ofstream outputFile( outFilePath );

    Processor::GetInstance();
    Processor::GetInstance().LoadCSVFilePathToVector( csvFilePath, inFile, filename );
    Processor::GetInstance().LoadCSVData( csvFilePath, mapAov );

    InputValidator validator;
    SensorRecType sensorRecType;
    AVL<SensorRecType> sensorRecords;

    // Declared variables
    float sumWindSpeed = 0.0;
    float windSpeedMean = 0.0;
    float convertedWindSpeedMean = 0.0;
    float temperatureSampleStandardDeviation = 0.0;
    float windSpeedSampleStandardDeviation = 0.0;
    float convertedWindSpeedSampleStandardDeviation = 0.0;

    float sumTemperature = 0.0;
    float temperatureMean = 0.0;

    float sumSolarRadiation = 0.0;
    float convertedSolarRadiation = 0.0;

    unsigned count = 0;

    string year;
    string month;
    string day;
    bool isFileExported = false;
    char user_choice;
    do
    {
        unsigned validatedDay = 0;
        unsigned validatedMonth = 0;
        unsigned validatedYear = 0;

        cout       << Constant::MENU_OPTIONS_MSG
                   << Constant::MENU_OPTION_ONE_MSG
                   << Constant::MENU_OPTION_TWO_MSG
                   << Constant::MENU_OPTION_THREE_MSG
                   << Constant::MENU_OPTION_FOUR_MSG
                   << Constant::MENU_OPTION_FIVE_MSG
                   << Constant::MENU_OPTION_SIX_MSG << endl;

        cout << Constant::SELECTION_INPUT;
        user_choice = getch();
        switch( user_choice )
        {
        case '1':
            cout << Constant::SELECTED_OPTION_ONE_MSG << endl;

            validatedMonth = validator.MonthValidation(month);
            validatedYear = validator.YearValidation(year);

            sensorRecords = mapAov.GetSensorData()[validatedYear][validatedMonth - 1];
            if (!sensorRecords.IsEmpty())
            {
                // Getting the sum
                mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::WIND_SPEED, sumWindSpeed);

                // calculate the mean and convert the wind speed....
                count = sensorRecords.GetTreeNodes();
                windSpeedMean = sumWindSpeed/count;
                convertedWindSpeedMean = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedMean );

                // calculate the sample standard deviation and convert the wind speed....
                windSpeedSampleStandardDeviation = mapAov.CalculateSampleStandardDeviation(sensorRecords.GetRoot(), SensorMeasurementType::WIND_SPEED, count);
                convertedWindSpeedSampleStandardDeviation = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedSampleStandardDeviation );

                // output the results
                cout    << Constant::OUTPUT << endl;
                cout    << sensorRecType.GetSensorDate().GetMonthInStr( validatedMonth ) << " " << validatedYear << ":" << endl;
                cout    << Constant::AVERAGE_WINDSPEED << setprecision(3) << convertedWindSpeedMean << endl;
                cout    << Constant::WINDSPEED_STANDARD_DEVIATION << setprecision(3) << convertedWindSpeedSampleStandardDeviation << '\n' << endl;
            }
            else
            {
                // output if no data is found
                cout    << Constant::OUTPUT << endl;
                cout    << setw(5) << " " << sensorRecType.GetSensorDate().GetMonthInStr(validatedMonth) << " " << validatedYear << ": No Data" << '\n' << endl;
            }
            cout << endl;
            break;
        case '2':
            cout << Constant::SELECTED_OPTION_TWO_MSG << endl;
            validatedYear = validator.YearValidation(year);
            cout << '\n'  << Constant::OUTPUT << '\n' << validatedYear << ":" << endl;

            for (unsigned month = 1; month <= 12; ++month)
            {
                sensorRecords = mapAov.GetSensorData()[validatedYear][month - 1];
                if (!sensorRecords.IsEmpty())
                {
                    // Getting the sum....
                    mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, sumTemperature);

                    // calculate the mean....
                    count = sensorRecords.GetTreeNodes();
                    temperatureMean = sumTemperature/count;

                    // calculate the sample standard deviation and convert the temperature....
                    temperatureSampleStandardDeviation = mapAov.CalculateSampleStandardDeviation(sensorRecords.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, count);

                    // output results
                    cout << sensorRecType.GetSensorDate().GetMonthInStr( month ) << ": " <<
                         setprecision(3) << temperatureMean << " degrees C, stdev: " <<  setprecision(3) << temperatureSampleStandardDeviation << endl;
                }
                else
                {
                    // output of no data
                    cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": No Data" << endl;
                }
            }
            cout << endl;
            break;
        case '3':
            cout << Constant::SELECTED_OPTION_THREE_MSG << endl;
            validatedYear = validator.YearValidation(year);
            cout << '\n'  << Constant::OUTPUT << '\n' << validatedYear << ":" << endl;

            for (unsigned month = 1; month <= 12; ++month)
            {
                sensorRecords = mapAov.GetSensorData()[validatedYear][month - 1];
                if (!sensorRecords.IsEmpty())
                {
                    // calculate the sum...
                    mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::SOLAR_RADIATION, sumSolarRadiation);
                    convertedSolarRadiation = sensorRecType.GetSensorSolarRadiation().ConvertUnit( sumSolarRadiation );

                    cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": "
                         << setprecision(5) << convertedSolarRadiation << " kWh/m2" << endl;
                }
                else
                {
                    cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": No Data" << endl;
                }
            }
            cout << endl;
            break;
        case '4':
            cout << Constant::SELECTED_OPTION_FOUR_MSG << endl;
            validatedYear = validator.YearValidation(year);
            cout << '\n' << Constant::OUTPUT << endl;
            cout << '\n' <<  validatedYear << ":" << endl;

            if( !outputFile )
            {
                cerr << "[ ERROR ] Opening File: " << outFilePath << endl;
            }

            outputFile << "Month,Average Wind Speed(stdev),Average Ambient Temperature(stdev),Solar Radiation" << endl;

            for (unsigned month = 1; month <= 12; ++month)
            {
                sensorRecords = mapAov.GetSensorData()[validatedYear][month - 1];
                if (!sensorRecords.IsEmpty())
                {
                    // calculate the sum...
                    mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::SOLAR_RADIATION, sumSolarRadiation);
                    mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, sumTemperature);
                    mapAov.InOrderTraversalSum(sensorRecords.GetRoot(), SensorMeasurementType::WIND_SPEED, sumWindSpeed);

                    // calculate the mean....
                    count = sensorRecords.GetTreeNodes();
                    temperatureMean = sumTemperature/count;
                    windSpeedMean = sumWindSpeed/count;

                    // calculate the sample standard deviation and convert the wind speed....
                    temperatureSampleStandardDeviation = mapAov.CalculateSampleStandardDeviation(sensorRecords.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, count);
                    windSpeedSampleStandardDeviation = mapAov.CalculateSampleStandardDeviation(sensorRecords.GetRoot(), SensorMeasurementType::WIND_SPEED, count);

                    convertedWindSpeedMean = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedMean );
                    convertedWindSpeedSampleStandardDeviation = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedSampleStandardDeviation );
                    convertedSolarRadiation = sensorRecType.GetSensorSolarRadiation().ConvertUnit( sumSolarRadiation );

                    cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ","
                         << setprecision(3) << convertedWindSpeedMean << "(" << setprecision(3) << convertedWindSpeedSampleStandardDeviation << "),"
                         << setprecision(3) << temperatureMean << "(" << setprecision(3) << temperatureSampleStandardDeviation << "),"
                         << setprecision(5) << convertedSolarRadiation << endl;

                    if(
                        Processor::GetInstance().OutputStreamMeasurement(
                            sensorRecType,
                            outputFile,
                            month,
                            convertedWindSpeedMean,
                            convertedWindSpeedSampleStandardDeviation,
                            temperatureMean,
                            temperatureSampleStandardDeviation,
                            convertedSolarRadiation ) )
                    {
                        isFileExported = true;
                    }
                }
                else
                {
                    cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ",No Data" << endl;
                }
            }
            outputFile.close();
            if( isFileExported )
            {
                cout << '\n' << "[ INFO ]: Data has being exported to: " << outFilePath << endl;
            }
            else
            {
                cout << "[ ERROR ]: Exporting data to: " << outFilePath << endl;
            }
            cout << endl;
            break;
        case '5':
            cout << Constant::SELECTED_OPTION_FIVE_MSG << endl;
            validatedDay = validator.DayValidation(day);
            validatedMonth = validator.MonthValidation(month);
            validatedYear = validator.YearValidation(year);

            highestSolarRadiations = mapAov.FindHighestSolarRadiation( validatedDay, validatedMonth, validatedYear );

            cout << '\n' << Constant::OUTPUT << endl;
            cout << "Date: " << validatedDay << "/" << validatedMonth << "/" << validatedYear << '\n'
                 << Constant::SOLAR_RADIATION_HIGH_MSG << highestSolarRadiations[0].first << " W/m2\n" << endl;

            cout << "Times with the highest solar radiation:" << endl;
            for (const auto& radiation : highestSolarRadiations)
            {
                cout << "Time: " << radiation.second << endl;
            }
            cout << endl;
            break;
        case '6':
            cout << Constant::SELECTED_OPTION_SIX_MSG << endl;
            exit(0);
            break;
        default:
            break;
        }
        cout << Constant::INFO( Constant::PRESS_ENTER_TO_CONTINUE_MSG ) << endl;
        while( getch() != 13 );
        system("cls");
    }
    while( user_choice !=27 );

    return 0;
}



