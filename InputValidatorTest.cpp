/**
* @file InputValidatorTest.cpp
* @brief InputValidator Test execution file
*
* This file contains the execution unit test for InputValidator Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include <iostream>
#include "InputValidator.h"

void testDayValidation( InputValidator &input );
void testMonthValidation( InputValidator &input );
void testYearValidation(InputValidator &input );

int main() {
    InputValidator input;

    testDayValidation( input );
    testMonthValidation( input );
    testYearValidation( input );

    return 0;
}

void testDayValidation( InputValidator &input )
{
    string day;
    if( input.DayValidation(day) )
    {
        cout << "\t[ PASS ]: Day Validation" << endl;
    }
    else
    {
        cout << "\t[ FAIL ]: Day Validation" << endl;
    }
}

void testMonthValidation( InputValidator &input )
{
    string month;
    if(input.MonthValidation(month))
    {
        cout << "\t[ PASS ]: Month Validation" << endl;
    }
    else
    {
        cout << "\t[ FAIL ]: Month Validation" << endl;
    }
}

void testYearValidation( InputValidator &input )
{
    string year;
    if(input.YearValidation(year))
    {
        cout << "\t[ PASS ]: Year Validation" << endl;
    }
    else
    {
        cout << "\t[ FAIL ]: Year Validation" << endl;
    }
}

