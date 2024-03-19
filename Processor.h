/**
* @file Processor.h
* @brief Processor class definition.
*
* This file contains the definition of the Processor class.
* The class allows FileI/O operations with singleton pattern.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include<iostream>
#include<fstream>
#include<string>

#include "AoAvlMap.h"
#include "Constant.h"
#include "Vector.h"

using namespace std;

/**
 * @brief The Processor class handles processing of CSV data as a singleton.
 *
 * This class provides functionality to load CSV file paths from a txt file and processes data into vectors,
 * and perform other processing tasks. It follows the singleton design pattern.
 */
class Processor
{
public:

    /**
     * @brief Returns the singleton instance of Processor.
     *
     * @return Processor& A reference to the singleton instance.
     */
    static Processor &GetInstance();

    /**
     * @brief Loads the CSV file paths from an txt file and stream into a vector.
     *
     * @param[in] csvFilePath The vector to store the CSV file paths.
     * @param[in] input The input stream from which to read the file paths.
     * @param[in] filename The name of the txt file being loaded.
     */
    void LoadCSVFilePathToVector( Vector<string> &csvFilePath, ifstream &input, const string &filename );

    /**
     * @brief Loads data from CSV files into an AVL map.
     *
     * This method reads data from CSV files specified by the given file paths and inserts the data into
     * an AVL map of sensor records. Each CSV file is expected to have a header line containing column names,
     * followed by data records. The method parses the CSV files, extracts relevant sensor data, constructs
     * sensor records, and inserts them into the AVL map.
     *
     * @param csvFilePath Vector containing the file paths of CSV files to be loaded.
     * @param mapAoBst Reference to the AVL map where the sensor data will be inserted.
     */
    void LoadCSVData( Vector<string> &csvFilePath, AoAvlMap<SensorRecType> &mapAoBst );

    /**
     * @brief Records sensor data to an output file and computes statistical measurements.
     *
     * This function records sensor data to the specified output file and calculates statistical measurements
     * including mean and standard deviation for speed and temperature readings, as well as the sum of sensor readings.
     *
     * @param[in] sensorRecType Reference to the sensor record type.
     * @param[in] outputFile Reference to the ofstream.
     * @param[in] month Reference to the month for which data is recorded.
     * @param[in] speedMean Reference to store the mean value of speed readings.
     * @param[in] speedSsd Reference to store the standard deviation of speed readings.
     * @param[in] tempMean Reference to store the mean value of temperature readings.
     * @param[in] tempSsd Reference to store the standard deviation of temperature readings.
     * @param[in] srSum Reference to store the sum of sensor readings.
     */
    bool OutputStreamMeasurement(
        SensorRecType &sensorRecType,
        ofstream &outputFile,
        unsigned &month,
        float &speedMean,
        float &speedSsd,
        float &tempMean,
        float &tempSsd,
        float &srSum );

private:
    static Processor *s_instance;   /**< Pointer to the singleton instance. */
    unsigned m_dataRead;            /**< Counter for the number of data read. */
    unsigned m_dataInserted;        /**< Counter for the number of data inserted. */

    /**
    * @brief Private constructor to prevent instantiation.
    */
    Processor();

    /**
     * @brief Loads the display count.
     *
     * This function loads the display count for the Processor instance.
     */
    void LoadDisplayCount();

    /**
    *
    * @brief Splits a string into substrings using a specified delimiter.
    *
    * This function takes a string and a delimiter character as input and splits the string into substrings
    * using the specified delimiter. It returns a vector containing the resulting substrings.
    *
    * @param[in] aString The string to be split.
    * @param[in] delimiter The character used as the delimiter for splitting.
    * @return A vector containing the substrings resulting from the split operation.
    *
    */
    Vector<string> Split( const string &aString, char delimiter );

};

#endif // PROCESSOR_H_INCLUDED
