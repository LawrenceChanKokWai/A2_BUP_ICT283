
/**
* @file Temperature.h
* @brief Temperature class definition.
*
* This file contains the child definition of Measurement class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#ifndef TEMPERATURE_H_INCLUDED
#define TEMPERATURE_H_INCLUDED

#include<iostream>

#include "Measurement.h"

using namespace std;

/**
* @brief Represents a temperature measurement.
*/
class Temperature: public Measurement
{
public:

    /**
    * @brief Default constructor.
    *
    * @post Creates a Temperature object with initial values.
    */
    Temperature();

    /**
    * @brief Parameterized constructor.
    *
    * @param[in] measurement The measurement variable of the Temperature.
    * @post Creates a Temperature object with specified temperature measurement.
    */
    Temperature( const float &measurement );

    /**
    * @brief Used for converting unit of temperature reading.
    *
    * @param[in] measurement The measurement variable of the Temperature.
    *
    * @return the converted temperature reading.
    */
    float ConvertUnit( float &measurement ) const override;
};


#endif // TEMPERATURE_H_INCLUDED
