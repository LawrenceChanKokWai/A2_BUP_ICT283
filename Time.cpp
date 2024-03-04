/**
* @file Time.cpp
* @brief Time class implementation file
*
* This file contains the Time class implementation.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "Time.h"

Time::Time()
{
    m_hour = INITIAL_VALUE;
    m_minute = INITIAL_VALUE;
}

Time::Time( const unsigned &hour,  const unsigned &minute )
{
    m_hour = hour;
    m_minute = minute;
}

unsigned Time::GetHour() const
{
    return m_hour;
}

unsigned Time::GetMinute() const
{
    return m_minute;
}

void Time::SetHour( const unsigned &hour )
{
    m_hour = hour;
}

void Time::SetMinute( const unsigned &minute )
{
    m_minute = minute;
}

bool Time::operator == ( const Time &otherTime ) const
{
    return ( m_hour == otherTime.m_hour ) && ( m_minute == otherTime.m_minute );
}

bool Time::operator != ( const Time &otherTime ) const
{
    return !( *this == otherTime );
}


bool Time::operator < ( const Time &otherTime ) const
{
    if ( m_hour != otherTime.m_hour )
    {
        return m_hour < otherTime.m_hour;
    }
    else
    {
        return m_minute < otherTime.m_minute;
    }
}

bool Time::operator > ( const Time &otherTime ) const
{
    return ( otherTime < *this );
}


ostream &operator << ( ostream &outputStream, const Time &T )
{
    outputStream << T.GetHour() << ":" << setw(2) << setfill( '0' ) << T.GetMinute();

    return outputStream;
}

istream &operator >> ( istream &inputStream, Time &T )
{
    string tempField;
    const unsigned INITIAL_VALUE = 0;

    getline( inputStream, tempField, ':');
    try
    {
        T.SetHour( stoi(tempField) );
    }
    catch(...)
    {
        T.SetHour( INITIAL_VALUE );
    }

    getline( inputStream, tempField, ',');
    try
    {
        T.SetMinute( stoi(tempField) );

    }
    catch(...)
    {
        T.SetMinute( INITIAL_VALUE );
    }

    return inputStream;
}