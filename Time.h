
/**
* @file Time.h
* @brief Time class definition.
*
* This file contains the definition of the Time class, which represents the time for a specific unit.
* The class allows setting and retrieving the hour, and minute associated with the time.
* It also overloads stream operators for input and output to facilitate I/O operations.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include<iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Represents a date for the measurements.
 */
class Time
{
public:

    /**
    * @brief Default constructor for Time class.
    *
    * This constructor creates a Time object with default values for hour, and minute attributes that is set as 00.
    */
    Time();

    /**
    * @brief Parameterized Constructor For The Time Class
    *
    * This constructor creates a Time Class with user defined values for the hour, and minute as parameters.
    *
    * @param[in] hour The hour associated with the time.
    * @param[in] minute The minute associated with the time.
    */
    Time( const unsigned &hour, const unsigned &minute );

    /**
    * @brief Method that allows retrieving the hour that is associated with the Time class.
    *
    * @return unsigned data type of the hour associated with the time.
    */
    unsigned GetHour() const;

    /**
    * @brief Method that allows retrieving the minute that is associated with the Time class.
    *
    * @return unsigned data type of the minute associated with the time.
    */
    unsigned GetMinute() const;

    /**
    * @brief Method that allows setting the hour associated with the Time class.
    *
    * @param[in] hour referenced hour with the Time class.
    * @return void
    */
    void SetHour( const unsigned &hour );

    /**
    * @brief Method that allows setting the minute associated with the Time class.
    *
    * @param[in] minute referenced minute with the Time class.
    * @return void
    */
    void SetMinute( const unsigned &minute );

    /**
    * @name Comparison Operator Overload
    * @{
    */

    /**
    * @brief Overloaded equality operator for Time objects.
    *
    * This operator checks whether two Time objects have the same hour and minute.
    *
    * @param[in] otherTime The Time object to compare with.
    * @return true if the hour and minute of both Time objects are equal, false otherwise.
    *
    * @see Time
    */
    bool operator == ( const Time &otherTime ) const;

    /**
    * @brief Overloaded not equal operator for Time objects.
    *
    * This operator checks whether two Time objects does not have the same hour, and minute.
    *
    * @param[in] otherTime The Time object to compare with.
    * @return true if the hour, and minute of both Time objects are not equal, false otherwise.
    *
    * @see Time
    */
    bool operator != ( const Time &otherTime ) const;

    /**
    * @brief Overloaded less than operator for Time objects.
    *
    * This operator checks whether this Time object is less than other Time object.
    *
    * @param[in] otherTime The Time object to compare with.
    * @return true if the hour, and minute of this Time is less than other Time objects, false otherwise.
    *
    * @see Time
    */
    bool operator < ( const Time &otherTime ) const;

    /**
    * @brief Overloaded greater than operator for Time objects.
    *
    * This operator checks whether this Time object is greater than other Time object.
    *
    * @param[in] otherTime The Time object to compare with.
    * @return true if the hour, and minute of this Time is greater than other Time objects, false otherwise.
    *
    * @see Date
    */
    bool operator > ( const Time &otherTime ) const;
    /** @} */

private:
    unsigned INITIAL_VALUE = 0;

    unsigned m_hour;
    unsigned m_minute;
};

/**
* @brief Function: Overloaded stream insertion operator for Time class.
*
* This allows a Time object to be printed to an output stream using the standard output format.
* The hour (unsigned data type), and minute (unsigned data type) will be printed.
*
* @param[in] outputStream The output stream where the Time object will be printed.
* @param[in] T The Time object to be printed.
* @return A reference to the output stream after printing the Time object.
*/
ostream &operator << ( ostream &outputStream, const Time &T );

/**
* @brief Function: Overloaded stream extraction operator for Time class.
*
* This allows a Time object to be read from an input stream using the standard input format.
* The input should contain the hour (unsigned data type), and minute (unsigned data type).
*
* @param[in] inputStream The input stream from which the Time object will be read.
* @param[in] T The Time object where the read information will be stored.
* @return A reference to the input stream after setting the Time object.
*/
istream &operator >> ( istream &inputStream, Time &T );

#endif // TIME_H_INCLUDED
