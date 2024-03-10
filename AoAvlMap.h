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

    void InOrderTraversalSumAndSquareSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum, float& sumSquare) const;

    float SampleStandardDeviationMeasurementSwitch(Node<T>* root, SensorMeasurementType sensorMeasurementType, unsigned &count) const;


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
void AoAvlMap<T>::InOrderTraversalSum( Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum ) const
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

// +++++++++++++ InOrderTraversalSum&SquareSum ++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Calculates the sum and sum of squares of different types of measurements
template<class T>
void AoAvlMap<T>::InOrderTraversalSumAndSquareSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum, float& sumSquare) const {
    if (root == nullptr)
        return;

    InOrderTraversalSumAndSquareSum(root->m_left, sensorMeasurementType, sum, sumSquare);

    switch (sensorMeasurementType) {
        case SensorMeasurementType::WIND_SPEED:
            sum += root->m_object.GetSensorWindSpeed().GetMeasurement();
            sumSquare += pow(root->m_object.GetSensorWindSpeed().GetMeasurement(), 2);
            break;
        case SensorMeasurementType::AMBIENT_TEMPERATURE:
            sum += root->m_object.GetSensorTemperature().GetMeasurement();
            sumSquare += pow(root->m_object.GetSensorTemperature().GetMeasurement(), 2);
            break;
        case SensorMeasurementType::SOLAR_RADIATION:
            sum += root->m_object.GetSensorSolarRadiation().GetMeasurement();
            sumSquare += pow(root->m_object.GetSensorSolarRadiation().GetMeasurement(), 2);
            break;
    }

    InOrderTraversalSumAndSquareSum(root->m_right, sensorMeasurementType, sum, sumSquare);
}

// Inside the AoAvlMap class definition
template<class T>
float AoAvlMap<T>::SampleStandardDeviationMeasurementSwitch(Node<T>* root, SensorMeasurementType sensorMeasurementType, unsigned &count) const {
    float sum = 0.0;
    float sumSquare = 0.0;
    InOrderTraversalSumAndSquareSum(root, sensorMeasurementType, sum, sumSquare);

    float variance = (sumSquare - pow(sum, 2) / count) / (count - 1);
    return sqrt(variance);
}





#endif // AOAVLMAP_H_INCLUDED
