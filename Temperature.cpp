/**
* @file Temperature.cpp
* @brief Temperature class implementation file
*
* This file contains the Temperature class implementation.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "Temperature.h"

Temperature::Temperature(): Measurement() {}

Temperature::Temperature( const float &measurement ): Measurement( measurement ) {}

float Temperature::ConvertUnit( float &measurement ) const
{
    return ( (measurement -32) * 5/9 );
}
