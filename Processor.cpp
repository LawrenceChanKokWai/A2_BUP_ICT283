
/**
* @file Processor.cpp
* @brief Processor class implementation file
*
* This file contains the Processor class implementation.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include "Processor.h"

// +++++++++++++ PRIVATE ++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++
Processor::Processor()
{
    m_dataRead = 0;
    m_dataInserted = 0;
}

void Processor::LoadDisplayCount()
{
    std::cout   << Constant::INFO( Constant::TOTAL_READ_DATA_MSG ) << m_dataRead << '\n'
                << Constant::INFO( Constant::TOTAL_SAVED_DATA_MSG ) << m_dataInserted << '\n'
                << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
                << endl;
}

// +++++++++++++ PUBLIC +++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++
Processor &Processor::GetInstance()
{
    static Processor *s_instance = new Processor();
    return *s_instance;
}

void Processor::LoadCSVFilePathToVector( vector<string> &csvFilePath, ifstream &input, const string &filename )
{
    string file_path;
    if( !input )
    {
        cerr    << "++++++++++++++++++++++++++++++++ STATUS +++++++++++++++++++++++++++++++++++++++++\n"
                << "Error Opening File: " + filename << endl;
    }
    else
    {
        cout    << "++++++++++++++++++++++++++++++++ STATUS +++++++++++++++++++++++++++++++++++++++++\n"
                << "Opening File: " + filename << endl;
        while( input.peek() != EOF )
        {
            input >> file_path;
            csvFilePath.push_back( file_path );
        }
    }
    input.close();
}

/**
void Processor::LoadCSVData( Vector<string> &csvFilePath, MapAov &mapAov )
{
    for( unsigned i(0); i<csvFilePath.GetUsed(); i++ )
    {
        string modifiedFilePath = "C:/Users/ChanKokWai/Desktop/V3_AssignmentOne/ICT283_AssignmentOne_ChanKokWai_3394804/data/" + csvFilePath[i];
        ifstream CSVFile( modifiedFilePath );
        if( !CSVFile )
        {
            cerr << "Error Opening CSV File Path: " << modifiedFilePath << endl;
        }
        else
        {
            cout << "Opening CSV File Path: " << modifiedFilePath << endl;
        }

        string line;
        SensorRecType sensorRecType;
        getline( CSVFile, line );
        while( CSVFile.peek() != EOF )
        {
            CSVFile >> sensorRecType;
            m_dataRead ++;

            mapAov.InsertSensorData( sensorRecType );
            m_dataInserted ++;
        }
        CSVFile.close();
    }
    LoadDisplayCount();
}
*/

void Processor::LoadCSVData( vector<string> &csvFilePath, AoAvlMap<SensorRecType> &mapAoBst )
{
    string headerLine;
    string line;
    vector<string> headers;
    vector<string> records;

    string sysFilePath = string(__FILE__).substr(0, string(__FILE__).find_last_of("\\/") + 1) + "data\\";

    for (unsigned i(0); i<csvFilePath.size(); i++ )
    {
        string modifiedFilePath = sysFilePath + csvFilePath[i];
        ifstream inFile( modifiedFilePath );

        if( inFile.is_open() )
        {
            cout << "Opening CSV File Path: " << modifiedFilePath << endl;
            if( getline( inFile, headerLine ) )
            {
                headers = split( headerLine, ',' );
            }
            // Read data
            while (std::getline(inFile, line))
            {
                // skip line when row is empty
                if( line.empty() || line.find("N/A") != string::npos || line.find_first_not_of(',') == string::npos )
                {
                    continue;
                }

                records = split(line, ',');

                // Find the indices of the columns we want to read
                int WAST_index = -1;
                int T_index = -1;
                int S_index = -1;
                int SR_index = -1;
                for (unsigned i = 0; i < headers.size(); ++i)
                {
                    if (headers[i] == "WAST")
                    {
                        WAST_index = i;
                    }
                    else if (headers[i] == "T")
                    {
                        T_index = i;
                    }
                    else if (headers[i] == "S")
                    {
                        S_index = i;
                    }
                    else if (headers[i] == "SR")
                    {
                        SR_index = i;
                    }
                }
                m_dataRead ++;

                Date DValue;
                Time TValue;
                WindSpeed SValue;
                Temperature TEMPValue;
                SolarRadiation SRValue;

                string WAST;
                string T;
                string S;
                string SR;

                // Read the values of the columns we want to read
                if (WAST_index != -1 && T_index != -1 && S_index != -1 && SR_index != -1)
                {
                    WAST = records[WAST_index];
                    T = records[T_index];
                    S = records[S_index];
                    SR = records[SR_index];

                    // Split WAST into Date and Time.
                    vector<string> WAST_parts = split(WAST, ' ' ); // Date [0] , Time [1]
                    vector<string> date = split(WAST_parts[0], '/' ); // day [0], month [1], year [2]

                    vector<string> time = split( WAST_parts[1], ':' );

                    DValue.SetDay( stoi( date[0]) );
                    DValue.SetMonth( stoi( date[1]) );
                    DValue.SetYear( stoi( date[2]) );

                    TValue.SetHour( stoi(time[0] ) );
                    TValue.SetMinute( stoi( time[1] ) );

                    SValue.SetMeasurement( stof(S) );
                    TEMPValue.SetMeasurement( stof(T) );
                    SRValue.SetMeasurement( stof(SR) );

                    SensorRecType sensorRecType( DValue, TValue, SValue, SRValue, TEMPValue );
                    cout << sensorRecType << endl;

                    mapAoBst.InsertSensorData( sensorRecType );
                    m_dataInserted ++;


                    /**
                    std::cout   << "Date: " << DValue.GetDay() << '/' << DValue.GetMonth() << '/' << DValue.GetYear() << " "
                                << "Time: " << TValue.GetHour() << ':' << TValue.GetMinute()
                                << ", T: " << TEMPValue.GetMeasurement() << ", S: " << SValue.GetMeasurement() << ", SR: " << stof(SR) << std::endl;
                    */
                }
            }
            inFile.close();
        }
        else
        {
            cerr << "Error Opening CSV File Path: " << modifiedFilePath << endl;
        }
    }
    LoadDisplayCount();
}

bool Processor::OutputStreamMeasurement(
    SensorRecType &sensorRecType,
    ofstream &outputFile,
    unsigned &month,
    float &speedMean,
    float &speedSsd,
    float &tempMean,
    float &tempSsd,
    float &srSum )
{
    outputFile << sensorRecType.GetSensorDate().GetMonthInStr(month) << ","
               << setprecision(3) << speedMean << "(" << setprecision(3) << speedSsd << "),"
               << setprecision(3) << tempMean << "(" << setprecision(3) << tempSsd << "),"
               << setprecision(3) << srSum << endl;
    return true;
}

vector<string> Processor::split( const string &aString, char delimiter )
{
    vector<string> someStrings;
    string someString;
    istringstream stringStream( aString );

    while( getline( stringStream, someString, delimiter) )
    {
        someStrings.push_back( someString );
    }
    return someStrings;
}


