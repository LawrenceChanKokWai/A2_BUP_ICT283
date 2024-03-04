
/**
* @file SolarRadiation.h
* @brief SolarRadiation class definition.
*
* This file contains the child definition of Measurement class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#ifndef SOLARRADIATION_H_INCLUDED
#define SOLARRADIATION_H_INCLUDED

#include<iostream>

#include "Measurement.h"

using namespace std;

/**
* @brief Represents a temperature measurement.
*/
class SolarRadiation: public Measurement
{
public:

    /**
    * @brief Default constructor.
    *
    * @post Creates a SolarRadiation object with initial values.
    */
    SolarRadiation();

    /**
    * @brief Parameterized constructor.
    *
    * @param[in] measurement The measurement variable of the Solar Radiation.
    * @post Creates a SolarRadiation object with specified solar radiation measurement.
    */
    SolarRadiation( const float &measurement );

    /**
    * @brief Used for converting unit of solar radiation reading.
    *
    * @param[in] measurement The measurement variable of the SolarRadiation.
    *
    * @return the converted solar radiation reading in kWh/m2.
    */
    float ConvertUnit( float &measurement ) const;

};


#endif // SOLARRADIATION_H_INCLUDED
