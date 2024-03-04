
/**
* @file WindSpeed.h
* @brief WindSpeed class definition.
*
* This file contains the child definition of Measurement class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#ifndef WINDSPEED_H_INCLUDED
#define WINDSPEED_H_INCLUDED

#include<iostream>

#include "Measurement.h"

using namespace std;

/**
* @brief Represents a wind speed measurement.
*/
class WindSpeed: public Measurement
{

public:

    /**
    * @brief Default constructor.
    *
    * @post Creates a WindSpeed object with initial values.
    */
    WindSpeed();

    /**
    * @brief Parameterized constructor.
    *
    * @param[in] measurement The measurement variable of the WindSpeed.
    * @post Creates a WindSpeed object with specified wind speed measurement.
    */
    WindSpeed( const float &measurement );

    /**
    * @brief Converts windspeed reading to kWh/m2.
    *
    * @param[in] measurement The measurement variable of the WindSpeed.
    *
    * @return the converted windspeed in kWh/m2.
    */
    float ConvertUnit( float &measurement ) const;

};


#endif // WINDSPEED_H_INCLUDED
