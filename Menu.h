#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

template<class T>
class Menu
{
public:
    void OptionOne( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year, unsigned &month ) const;
    void OptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year ) const;
    void OptionThree( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year ) const;
    void OptionFour( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, ofstream &outputFile, const string &filePath, unsigned &year );
    void OptionFive( AoAvlMap<T> &aoAvlMap, unsigned &month );

private:
    void PrintSpccValues(const string &label, float value);

};

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
void Menu<T>::OptionTwo( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year ) const
{
    T sensorRecType;
    float sumTemperature = 0.0;
    unsigned count = 0;

    for (unsigned month = 1; month <= 12; ++month)
    {
        avl = aoAvlMap.GetSensorData()[year][month - 1];
        if (!avl.IsEmpty())
        {
            // Getting the sum....
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, sumTemperature);

            // calculate the mean....
            count = avl.GetTreeNodes();
            float temperatureMean = sumTemperature/count;

            // calculate the sample standard deviation and convert the temperature....
            float temperatureSampleStandardDeviation = aoAvlMap.CalculateSampleStandardDeviation(avl.GetRoot(), SensorMeasurementType::AMBIENT_TEMPERATURE, count);

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
}

template<class T>
void Menu<T>::OptionThree( AVL<T> &avl, AoAvlMap<T> &aoAvlMap, unsigned &year ) const
{
    T sensorRecType;
    float sumSolarRadiation = 0.0;

    for (unsigned month = 1; month <= 12; ++month)
    {
        avl = aoAvlMap.GetSensorData()[year][month - 1];
        if (!avl.IsEmpty())
        {
            // calculate the sum...
            aoAvlMap.InOrderTraversalSum(avl.GetRoot(), SensorMeasurementType::SOLAR_RADIATION, sumSolarRadiation);
            float convertedSolarRadiation = sensorRecType.GetSensorSolarRadiation().ConvertUnit( sumSolarRadiation );

            cout << sensorRecType.GetSensorDate().GetMonthInStr(month) << ": "
                 << setprecision(5) << convertedSolarRadiation << " kWh/m2" << endl;
        }
        else
        {
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
void Menu<T>::OptionFive( AoAvlMap<T> &aoAvlMap, unsigned &month )
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
