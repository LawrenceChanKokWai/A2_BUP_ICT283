#ifndef AOAVLMAP_H_INCLUDED
#define AOAVLMAP_H_INCLUDED

#include<map>

#include "AVL.h"
#include "SensorRecType.h"
#include "SensorMeasurementType.h"

using namespace std;

template<class T>
class AoAvlMap
{
public:
    static const unsigned NUM_MTH = 12;     ///< Number of months in a year.

    /**
     * @brief Get a constant reference to the sensor data map.
     *
     * @return Constant reference to the sensor data map.
     */
    const map<unsigned, array<AVL<T>, NUM_MTH>>& GetSensorData() const;

    /**
     * @brief Get a reference to the sensor data map.
     *
     * @return Reference to the sensor data map.
     */
    map<unsigned, array<AVL<T>, NUM_MTH>>& GetSensorData();

    /**
     * @brief Insert sensor data into the map consisted with array of Vectors.
     *
     * @param sensorData The sensor data to be inserted.
     */
    bool InsertSensorData(const T &sensorData);

    void InOrderTraversalSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum) const;


    /**
     * @brief Switch function to compute the sum of different types of measurements.
     *
     * @param[in] sensorRecords The AVL of sensor records.
     * @param[in] sensorMeasurementType The type of measurement to compute.
     *
     * @return The computed measurement based on the switch case.
     */
    //float SumOfMeasurementSwitch( const AVL<T> &sensorRecords, SensorMeasurementType sensorMeasurementType ) const;

    /**
     * @brief Switch function to compute the mean of different types of measurements.
     *
     * @param[in] sensorRecords The vector of sensor records.
     * @param[in] sensorMeasurementType The type of measurement to compute.
     *
     * @return The computed measurement based on the switch case.
     */
    //float MeanOfMeasurementSwitch( const Vector<SensorRecType> &sensorRecords, SensorMeasurementType sensorMeasurementType ) const;

    /**
     * @brief Switch function to compute the sample standard deviation of different types of measurements.
     *
     * @param[in] sensorRecords The vector of sensor records.
     * @param[in] sensorMeasurementType The type of measurement to compute.
     *
     * @return The computed measurement based on the switch case.
     */
    //float SampleStandardDeviationMeasurementSwitch( const Vector<SensorRecType> &sensorRecords, SensorMeasurementType sensorMeasurementType ) const;


private:
    map<unsigned, array<AVL<SensorRecType>, NUM_MTH>> m_data;    ///< Map storing arrays of sensor data vectors organized by month and year.

};

template<class T>
const map<unsigned, array<AVL<T>, AoAvlMap<T>::NUM_MTH>>& AoAvlMap<T>::GetSensorData() const
{
    return m_data;
}

template<class T>
map<unsigned, array<AVL<T>, AoAvlMap<T>::NUM_MTH>>& AoAvlMap<T>::GetSensorData()
{
    return m_data;
}

template<class T>
bool AoAvlMap<T>::InsertSensorData(const T &sensorData)
{
    unsigned year = sensorData.GetSensorDate().GetYear();
    unsigned month = sensorData.GetSensorDate().GetMonth();

    // Check if the entry for the year exists
    auto yearIter = m_data.find(year);
    if (yearIter == m_data.end())
    {
        // If the entry doesn't exist, create it and initialize the array
        array<AVL<T>, NUM_MTH> emptyArray;
        for (auto& avl : emptyArray)
        {
            avl = AVL<T>();
        }
        m_data[year] = emptyArray;
        yearIter = m_data.find(year); // Reacquire iterator after insertion
    }

    // Access the array for the month and add the sensor data
    yearIter->second[month - 1].InsertNode(sensorData);
    return true;
}

// +++++++++++++ InOrderTraversalSum ++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Calculations of different types of measurements
template<class T>
void AoAvlMap<T>::InOrderTraversalSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum) const
{
    if (root == nullptr)
    {
        return;
    }

    InOrderTraversalSum(root->m_left, sensorMeasurementType, sum);

    switch (sensorMeasurementType)
    {
    case SensorMeasurementType::WIND_SPEED:
        sum += root->m_object.GetSensorWindSpeed().GetMeasurement();
        break;
    case SensorMeasurementType::AMBIENT_TEMPERATURE:
        sum += root->m_object.GetSensorTemperature().GetMeasurement();
        break;
    case SensorMeasurementType::SOLAR_RADIATION:
        sum += root->m_object.GetSensorSolarRadiation().GetMeasurement();
        break;
    }

    InOrderTraversalSum(root->m_right, sensorMeasurementType, sum);
}



// Calculations of different types of measurements
/**
template<class T>
float AoAvlMap<T>::SumOfMeasurementSwitch( const AVL<T> &sensorRecords, SensorMeasurementType sensorMeasurementType ) const
{
    float sum = 0.0;

    switch( sensorMeasurementType )
    {
    case SensorMeasurementType::WIND_SPEED:
        for( unsigned i(0); i<sensorRecords.GetUsed(); i++ )
        {
            sum += sensorRecords[i].GetSensorWindSpeed().GetMeasurement();
        }
        break;
    case SensorMeasurementType::AMBIENT_TEMPERATURE:
        for( unsigned i(0); i<sensorRecords.GetUsed(); i++ )
        {
            sum += sensorRecords[i].GetSensorTemperature().GetMeasurement();
        }
        break;
    case SensorMeasurementType::SOLAR_RADIATION:
        for( unsigned i(0); i<sensorRecords.GetUsed(); i++ )
        {
            sum += sensorRecords[i].GetSensorSolarRadiation().GetMeasurement();
        }
        break;
    }
    return sum;
} */


#endif // AOAVLMAP_H_INCLUDED
