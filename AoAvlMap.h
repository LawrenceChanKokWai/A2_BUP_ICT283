#ifndef AOAVLMAP_H_INCLUDED
#define AOAVLMAP_H_INCLUDED

#include<map>

#include "AVL.h"
#include "SensorRecType.h"

using namespace std;

template<class T>
class AoAvlMap
{
public:
    typedef AVL<T> MonthToRecordsArrayAVL[12];
    typedef map<unsigned, MonthToRecordsArrayAVL> YearToRecordsArrayAVLMap;

    AoAvlMap();

    bool IsMapEmpty() const;
    bool IsArrayAVLEmpty() const;

    void Insert( unsigned year, unsigned month, SensorRecType &sensorRecType );

private:
    YearToRecordsArrayAVLMap m_sensorRecords;
    //map< T, AVL<SensorRecType>[12] > YearMonthToRecordsMap;

    bool Insert( const T &object );
};

template<class T>
AoAvlMap<T>::AoAvlMap(){}

#endif // AOAVLMAP_H_INCLUDED
