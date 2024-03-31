/**
* @file Main.cpp
* @brief Entry point for the assignment. The main execution file.
*
* This file contains the entry point of execution for assignment one.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include <iostream>
#include<iomanip>
#include<conio.h>
#include<cstdlib>

#include "InputValidator.h"
#include "Processor.h"
#include "Menu.h"

using namespace std;

int main()
{
    string directoryPath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";

    const string filename = directoryPath + "data_source.txt";
    const string outFilePath = directoryPath + "WindTempSolar.csv";
    Vector<string> csvFilePath;
    AoAvlMap<SensorRecType> mapRecords;
    ifstream inFile( filename );
    ofstream outputFile( outFilePath );

    Processor::GetInstance();
    Processor::GetInstance().LoadCSVFilePathToVector( csvFilePath, inFile, filename );
    Processor::GetInstance().LoadCSVData( csvFilePath, mapRecords );

    InputValidator validator;
    SensorRecType sensorRecType;
    AVL<SensorRecType> avlRecords;

    Menu<SensorRecType> menu;

    string year;
    string month;
    string day;
    char user_choice;
    do
    {
        unsigned validatedMonth = 0;
        unsigned validatedYear = 0;

        cout    << Constant::MENU_OPTIONS_MSG
                << Constant::MENU_OPTION_ONE_MSG
                << Constant::MENU_OPTION_TWO_MSG
                << Constant::MENU_OPTION_THREE_MSG
                << Constant::MENU_OPTION_FOUR_MSG
                << Constant::MENU_OPTION_FIVE_MSG
                << Constant::MENU_OPTION_SIX_MSG << endl;

        cout << Constant::SELECTION_INPUT;
        user_choice = getch();
        switch( user_choice )
        {
        case '1':
            cout << Constant::SELECTED_OPTION_ONE_MSG << endl;

            validatedMonth = validator.MonthValidation(month);
            validatedYear = validator.YearValidation(year);

            menu.OptionOne( avlRecords, mapRecords, validatedYear, validatedMonth );

            break;
        case '2':
            cout << Constant::SELECTED_OPTION_TWO_MSG << endl;
            validatedYear = validator.YearValidation(year);
            cout << '\n'  << Constant::OUTPUT << '\n' << validatedYear << ":" << endl;

            menu.OptionTwo( avlRecords, mapRecords, validatedYear, user_choice );

            break;
        case '3':
        {
            cout << Constant::SELECTED_OPTION_FIVE_MSG << endl;
            unsigned validatedMonth = validator.MonthValidation(month);

            cout << '\n' << Constant::OUTPUT << endl;
            cout << "Sample Pearson Correlation Coefficient for " << sensorRecType.GetSensorDate().GetMonthInStr(validatedMonth) << endl;

            menu.OptionThree( mapRecords, validatedMonth );

            break;
        }
        case '4':
            cout << Constant::SELECTED_OPTION_FOUR_MSG << endl;
            validatedYear = validator.YearValidation(year);
            cout << '\n' << Constant::OUTPUT << endl;
            cout << '\n' <<  validatedYear << ":" << endl;

            menu.OptionFour( avlRecords, mapRecords, outputFile, outFilePath, validatedYear );

            break;
        case '5':
        {
            cout << Constant::SELECTED_OPTION_FIVE_MSG << endl;

            cout << '\n' << Constant::OUTPUT << endl;
            cout << "Reloading data: " << filename << endl;

            Processor::GetInstance().ReloadData(mapRecords, filename);

            cout << '\n' << endl;

            break;
        }
        case '6':
            cout << Constant::SELECTED_OPTION_SIX_MSG << endl;
            exit(0);
            break;
        default:
            break;
        }
        cout << Constant::INFO( Constant::PRESS_ENTER_TO_CONTINUE_MSG ) << endl;
        while( getch() != 13 );
        system("cls");
    }
    while( user_choice !=27 );

    return 0;
}



