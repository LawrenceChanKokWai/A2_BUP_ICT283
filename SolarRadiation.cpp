/**
* @file SolarRadiation.cpp
* @brief SolarRadiation class implementation file
*
* This file contains the SolarRadiation class implementation.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "SolarRadiation.h"

SolarRadiation::SolarRadiation(): Measurement() {}

SolarRadiation::SolarRadiation( const float &measurement ): Measurement( measurement ) {}

float SolarRadiation::ConvertUnit( float &measurement ) const
{
    return ( measurement/1000 * 10/60 );
}

