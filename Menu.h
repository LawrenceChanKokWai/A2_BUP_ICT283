
///
/// @file Menu.h
/// @brief Menu class definition.
///
/// This file contains the definition of the Menu class.
///
/// @author Chan Kok Wai ( Student Number: 33924804 )
/// @version 1.0.0
///
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**
 *  @class Menu
 *
 *  @brief A class representing a menu interface for sensor data analysis.
 *
 *  This class provides various options for processing and analyzing sensor data,
 *  including calculating averages, standard deviations, exporting data to files,
 *  and calculating sample Pearson correlation coefficients.
 *
 */
template<class T>
class Menu
{
public:

    /**
     *
     *  @brief Option to calculate and display average wind speed and its standard deviation for a specified year and month.
     *
     *  @param[in] avl An AVL tree containing sensor data.
     *  @param[in] aoAvlMap An AoAvlMap containing sensor data.
     *  @param[in] year The year for which data is to be analyzed.
     *  @param[in] month The month for which data is to be analyzed.
     *
     */
    void OptionOne( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year, unsigned &month ) const;

    /**
     *  @brief Option to calculate and display average ambient temperature
     *  for each month of a specified year.
     *
     *  @param[in] avl An AVL tree containing sensor data.
     *  @param[in] aoAvlMap An AoAvlMap containing sensor data.
     *  @param[in] year The year for which data is to be analyzed.
     *  @param[in] option A character indicating the option to calculate ('2' for temperature).
     *
     */
    void OptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year, char &option ) const;

    /**
     *
     *  @brief Option to process sensor data for all months of a specified year and export results to a file.
     *
     *  @param[in] avl An AVL tree containing sensor data.
     *  @param[in] aoAvlMap An AoAvlMap containing sensor data.
     *  @param[in] outputFile An ofstream object representing the output file.
     *  @param[in] filePath The path to the output file.
     *  @param[in] year The year for which data is to be exported.
     *
     */
    void OptionFour( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, ofstream &outputFile, const string &filePath, unsigned &year );

    /**
     *  @brief Option to calculate and display sample Pearson correlation coefficient values
     *  for wind speed, temperature, and solar radiation for a specified month.
     *
     *  @param[in] aoAvlMap An AoAvlMap containing sensor data.
     *  @param[in] month The month for which correlation coefficients are to be calculated.
     *
     */
    void OptionThree( AoAvlMap<T> &aoAvlMap, unsigned &month );

private:

    /**
     *
     *  @brief Helper function to print sample Pearson correlation coefficient values with appropriate labels and formatting.
     *
     *  @param[in] label The label for the correlation coefficient.
     *  @param[in] value The value of the correlation coefficient.
     *
     */
    void PrintSpccValues(const string &label, float value);

};

// ++++++++++++ PUBLIC +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<class T>
void Menu<T>::OptionOne( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year, unsigned &month ) const
{
    float sum = 0.0;
    unsigned count = 0;
    T sensorRecType;

    avl = aoAvlMap.GetSensorData()[year][month - 1];
    if (!avl.IsEmpty())
    {
        // Getting the sum
        aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::WIND_SPEED, sum);

        // calculate the mean and convert the wind speed....
        count = avl.GetTreeNodes();
        float windSpeedMean = sum/count;
        float convertedWindSpeedMean = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedMean );

        // calculate the sample standard deviation and convert the wind speed....
        float windSpeedSampleStandardDeviation = aoAvlMap.CalculateSampleStandardDeviation(avl.GetRoot(), SensorMeasurementType::WIND_SPEED, count);
        float convertedWindSpeedSampleStandardDeviation = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedSampleStandardDeviation );

        // output the results
        cout    << Constant::OUTPUT << endl;
        cout    << sensorRecType.GetSensorDate().GetMonthInStr( month ) << " " << year << ":" << endl;
        cout    << Constant::AVERAGE_WINDSPEED << setprecision(3) << convertedWindSpeedMean << endl;
        cout    << Constant::WINDSPEED_STANDARD_DEVIATION << setprecision(3) << convertedWindSpeedSampleStandardDeviation << '\n' << endl;
    }
    else
    {
        // output if no data is found
        cout    << Constant::OUTPUT << endl;
        cout    << setw(5) << " " << sensorRecType.GetSensorDate().GetMonthInStr( month ) << " " << year << ": No Data" << '\n' << endl;
    }
    cout << endl;
}

template<class T>
void Menu<T>::OptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year, char &option ) const
{
    T sensorRecType;
    float sum = 0.0;
    unsigned count = 0;
    string unit;
    SensorMeasurementType measurementType;

    if (option == '2')
    {
        measurementType = SensorMeasurementType::AMBIENT_TEMPERATURE;
        unit = "degrees C";
    }
    else if (option == '3')
    {
        measurementType = SensorMeasurementType::SOLAR_RADIATION;
        unit = "kWh/m2";
    }

    for (unsigned month = 1; month <= 12; ++month)
    {
        avl = aoAvlMap.GetSensorData()[year][month - 1];
        if (!avl.IsEmpty())
        {
            // Calculate the sum
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), measurementType, sum);

            // Calculate the mean
            count = avl.GetTreeNodes();
            float mean = sum / count;

            if (option == '2')
            {
                // Calculate the sample standard deviation
                float sampleStandardDeviation = aoAvlMap.CalculateSampleStandardDeviation(avl.GetRoot(), measurementType, count);

                // Output results for Option Two
                cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": "
                     << setprecision(3) << mean << " " << unit << ", stdev: "
                     << setprecision(3) << sampleStandardDeviation << endl;
            }
            else if (option == '3')
            {
                // Output results for Option Three
                cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": "
                     << setprecision(5) << mean << " " << unit << endl;
            }
        }
        else
        {
            // Output of no data
            cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": No Data" << endl;
        }
    }
    cout << endl;
}

template<class T>
void Menu<T>::OptionFour( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, ofstream &outputFile, const string &filePath, unsigned &year )
{
    T sensorRecType;
    unsigned count = 0;
    float sumSolarRadiation = 0.0;
    float sumTemperature = 0.0;
    float sumWindSpeed = 0.0;
    bool isFileExported = false;

    if( !outputFile )
    {
        cerr << "[ ERROR ] Opening File: " << filePath << endl;
    }

    outputFile << "Month,Average Wind Speed(stdev),Average Ambient Temperature(stdev),Solar Radiation" << endl;

    for (unsigned month = 1; month <= 12; ++month)
    {
        avl = aoAvlMap.GetSensorData()[year][month - 1];
        if (!avl.IsEmpty())
        {
            // calculate the sum...
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::SOLAR_RADIATION, sumSolarRadiation);
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, sumTemperature);
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::WIND_SPEED, sumWindSpeed);

            // calculate the mean....
            count = avl.GetTreeNodes();
            float temperatureMean = sumTemperature/count;
            float windSpeedMean = sumWindSpeed/count;

            // calculate the sample standard deviation and convert the wind speed....
            float temperatureSampleStandardDeviation = aoAvlMap.CalculateSampleStandardDeviation(avl.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, count);
            float windSpeedSampleStandardDeviation = aoAvlMap.CalculateSampleStandardDeviation(avl.GetRoot(), SensorMeasurementType::WIND_SPEED, count);

            float convertedWindSpeedMean = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedMean );
            float convertedWindSpeedSampleStandardDeviation = sensorRecType.GetSensorWindSpeed().ConvertUnit( windSpeedSampleStandardDeviation );
            float convertedSolarRadiation = sensorRecType.GetSensorSolarRadiation().ConvertUnit( sumSolarRadiation );

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
        cout << '\n' << "[ INFO ]: Data has being exported to: " << filePath << endl;
    }
    else
    {
        cout << "[ ERROR ]: Exporting data to: " << filePath << endl;
    }
    cout << endl;
}

template<class T>
void Menu<T>::OptionThree( AoAvlMap<T> &aoAvlMap, unsigned &month )
{
    Vector<float> windSpeeds;
    Vector<float> temperatures;
    Vector<float> solarRadiations;

    // Iterate through all years and extract relevant sensor measurements for the specified month
    const auto &sensorDataMap = aoAvlMap.GetSensorData();
    for (const auto &entry : sensorDataMap )
    {
        // Convert validatedMonth to unsigned for comparison
        if ( month >= 1 && month <= AoAvlMap<SensorRecType>::NUM_MTH )
        {
            const auto& sensorRecords = entry.second[month -1];

            aoAvlMap.ExtractMeasurements(sensorRecords.GetRoot(), SensorMeasurementType::WIND_SPEED, windSpeeds);
            aoAvlMap.ExtractMeasurements(sensorRecords.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, temperatures);
            aoAvlMap.ExtractMeasurements(sensorRecords.GetRoot(), SensorMeasurementType::SOLAR_RADIATION, solarRadiations);
        }
    }

    // Calculate sPCC for each combination of data fields
    float sPCC_S_T = aoAvlMap.CalculateSPCC(windSpeeds, temperatures);
    float sPCC_S_R = aoAvlMap.CalculateSPCC(windSpeeds, solarRadiations);
    float sPCC_T_R = aoAvlMap.CalculateSPCC(temperatures, solarRadiations);

    // Output the calculated sPCC values
    PrintSpccValues("S_T", sPCC_S_T);
    PrintSpccValues("S_R", sPCC_S_R);
    PrintSpccValues("T_R", sPCC_T_R);
    cout << endl;
}


// ++++++++++++ PRIVATE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template<class T>
void Menu<T>::PrintSpccValues(const string &label, float value)
{
    cout << label << ": ";
    if (value == -1)
    {
        cout << "No Data" << endl;
    }
    else
    {
        cout << fixed << setprecision(3) << value << endl;
    }
}



#endif // MENU_H_INCLUDED
