
///
/// @file AoAvlMap.h
/// @brief AoAvlMap class definition.
///
/// This file contains the definition of the AoAvlMap class.
///
/// @author Chan Kok Wai ( Student Number: 33924804 )
/// @version 1.0.0
///
#ifndef AOAVLMAP_H_INCLUDED
#define AOAVLMAP_H_INCLUDED

#include<map>
#include<vector>

#include "AVL.h"
#include "SensorRecType.h"
#include "SensorMeasurementType.h"

using namespace std;

/**
* @brief Represents the AoAvlMap Class
*/
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
    const map<unsigned, array<AVL<T>, NUM_MTH>> &GetSensorData() const;

    /**
     * @brief Get a reference to the sensor data map.
     *
     * @return Reference to the sensor data map.
     */
    map<unsigned, array<AVL<T>, NUM_MTH>> &GetSensorData();

    /**
     * @brief Insert sensor data into the map consisted with array of Vectors.
     *
     * @param sensorData The sensor data to be inserted.
     */
    bool InsertSensorData(const T &sensorData);


    /**
    * @brief Performs in-order traversal of the AVL tree and accumulates the sum of sensor measurements.
    *
    * This method traverses the AVL tree in an in-order manner and accumulates the sum of sensor measurements
    * based on the specified sensor measurement type. The accumulated sum is stored in the reference variable 'sum'.
    *
    * @param[in] root Pointer to the root node of the AVL tree.
    * @param[in] sensorMeasurementType Type of sensor measurement for which the sum is calculated.
    * @param[in] sum Reference to the variable storing the sum of sensor measurements.
    */
    void InOrderTraversalSum(Node<T> *root, SensorMeasurementType sensorMeasurementType, float &sum) const;

    /**
    * @brief Calculates the sample standard deviation of sensor measurements.
    *
    * This method computes the sample standard deviation of sensor measurements
    * stored in the AVL tree. It traverses the tree to accumulate the sum of
    * measurements and the sum of squared measurements, then uses these values
    * to compute the sample variance and finally returns the square root of the variance.
    *
    * @param[in] root Pointer to the root node of the AVL tree.
    * @param[in] sensorMeasurementType Type of sensor measurement for which standard deviation is calculated.
    * @param[in] count Reference to the variable storing the count of measurements.
    * @return The sample standard deviation of sensor measurements.
    */
    float CalculateSampleStandardDeviation(Node<T>* root, SensorMeasurementType sensorMeasurementType, unsigned &count) const;


    /**
    * @brief Finds the highest solar radiation readings for a specific date.
    *
    * This method searches the AVL map for the highest solar radiation readings recorded
    * on the specified date (day, month, year). It returns a vector of pairs containing
    * the highest radiation value(s) and the corresponding time(s) of measurement.
    *
    * @param[in] day The day of the date.
    * @param[in] month The month of the date.
    * @param[in] year The year of the date.
    * @return A vector of pairs representing the highest solar radiation and its corresponding time(s).
    */
    vector<pair<float, string>> FindHighestSolarRadiation(unsigned day, unsigned month, unsigned year) const;



private:
    map<unsigned, array<AVL<SensorRecType>, NUM_MTH>> m_data;    ///< Map storing arrays of sensor data vectors organized by month and year.


    /**
    * @brief Performs in-order traversal of the AVL tree and accumulates the sum and sum of squares of sensor measurements.
    *
    * This method traverses the AVL tree in an in-order manner and accumulates the sum and sum of squares of sensor measurements
    * based on the specified sensor measurement type. The accumulated sums are stored in the reference variables 'sum' and 'sumSquare'.
    *
    * @param[in] root Pointer to the root node of the AVL tree.
    * @param[in] sensorMeasurementType Type of sensor measurement for which the sums are calculated.
    * @param[in] sum Reference to the variable storing the sum of sensor measurements.
    * @param[in] sumSquare Reference to the variable storing the sum of squares of sensor measurements.
    *
    */
    void InOrderTraversalSumAndSquareSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum, float& sumSquare) const;

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
void AoAvlMap<T>::InOrderTraversalSumAndSquareSum(Node<T>* root, SensorMeasurementType sensorMeasurementType, float& sum, float& sumSquare) const
{
    if (root == nullptr)
        return;

    InOrderTraversalSumAndSquareSum(root->m_left, sensorMeasurementType, sum, sumSquare);

    switch (sensorMeasurementType)
    {
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

// Calculates the SSD
template<class T>
float AoAvlMap<T>::CalculateSampleStandardDeviation(Node<T>* root, SensorMeasurementType sensorMeasurementType, unsigned &count) const
{
    float sum = 0.0;
    float sumSquare = 0.0;
    InOrderTraversalSumAndSquareSum(root, sensorMeasurementType, sum, sumSquare);

    float variance = (sumSquare - pow(sum, 2) / count) / (count - 1);
    return sqrt(variance);
}

template<class T>
vector<pair<float, string>> AoAvlMap<T>::FindHighestSolarRadiation(unsigned day, unsigned month, unsigned year) const
{
    float highestRadiation = 0.0;
    vector<std::pair<float, std::string>> highestRadiations;

    // Find the AVL tree corresponding to the given day, month, and year
    auto yearIter = m_data.find(year);
    if (yearIter != m_data.end())
    {
        const AVL<T>& avl_tree = yearIter->second[month - 1];

        // Traverse the AVL tree to find the highest solar radiation reading
        Node<T>* root = avl_tree.GetRoot();
        while (root != nullptr)
        {
            if (root->m_object.GetSensorDate().GetDay() == day &&
                    root->m_object.GetSensorDate().GetMonth() == month &&
                    root->m_object.GetSensorDate().GetYear() == year &&
                    root->m_object.GetSensorSolarRadiation().GetMeasurement() > highestRadiation)
            {

                highestRadiation = root->m_object.GetSensorSolarRadiation().GetMeasurement();
                string hour = to_string(root->m_object.GetSensorTime().GetHour());
                string minute = to_string(root->m_object.GetSensorTime().GetMinute());
                string time = hour + ":" + minute;
                highestRadiations.clear(); // Clear previous highest times
                highestRadiations.push_back(make_pair(highestRadiation, time));
            }
            else if (root->m_object.GetSensorDate().GetDay() == day &&
                     root->m_object.GetSensorDate().GetMonth() == month &&
                     root->m_object.GetSensorDate().GetYear() == year &&
                     root->m_object.GetSensorSolarRadiation().GetMeasurement() == highestRadiation)
            {
                string hour = to_string(root->m_object.GetSensorTime().GetHour());
                string minute = to_string(root->m_object.GetSensorTime().GetMinute());
                string time = hour + ":" + minute;
                highestRadiations.push_back(make_pair(highestRadiation, time));
            }

            root = root->m_right;
        }
    }

    return highestRadiations;
}

#endif // AOAVLMAP_H_INCLUDED
