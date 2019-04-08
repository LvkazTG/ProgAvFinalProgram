#ifndef SEARCHDEEP_H
#define SEARCHDEEP_H

#include <list>
#include <map>

#include "connlist.h"
#include "mapaobj.h"
#include "pointconniter.h"
//#include "connlist.h"

class ConnList;

class SearchDeep
{
public:
    SearchDeep(const MapaObj& map, const std::string startPoint,
               const std::string endPoint);
    bool init();

    uint16_t _startHash{0};
    uint16_t _endHash{0};

    std::list<PointConnIter> _actualPath{};
    std::list<PointConnIter> _bestPath{};

    uint64_t _actualPathCost{0};
    uint64_t _bestPathCost{0};

    ConnList const* _connMapList{nullptr};

    private:
        void calculateActualCost();

};

#endif // SEARCHDEEP_H
