/**
* @file WindSpeed.cpp
* @brief WindSpeed class implementation file.
*
* This file contains the WindSpeed class implementation.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "WindSpeed.h"

WindSpeed::WindSpeed(): Measurement(){}

WindSpeed::WindSpeed( const float &measurement ): Measurement( measurement ){}

float WindSpeed::ConvertUnit( float &measurement ) const
{
    return ( measurement * 3.6 );
}

