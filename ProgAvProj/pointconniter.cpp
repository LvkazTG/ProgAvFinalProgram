#include "pointconniter.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
PointConnIter::PointConnIter(const uint16_t pointHash, const std::map<uint16_t, uint8_t>& pointConns) :
    _pointHash{pointHash}, _conns{&pointConns}
{
    _actualIter = _conns->begin();
}
//--------------------------------------------------------------------------------------------------
uint16_t PointConnIter::getPointHash() const
{
    return _pointHash;
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::isAtEnd() const
{
    return _conns->end() == _actualIter;
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::isOnLastValidIter() const
{
    // Provisory solution
    // It apears going std::next() on .end() locks code

    return (isAtEnd() ? true : _conns->end() == std::next(_actualIter));
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::moveIter(const uint32_t howMuch)
{
    bool ret{false};

    if(howMuch == 1)
    {
        ret = moveNext();
    }
    else if(std::distance(_actualIter, _conns->end()) > howMuch + 1)
    {
        std::advance(_actualIter, howMuch);
        ret = true;
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::moveNext()
{
    bool ret{false};
    if(!isOnLastValidIter())
    {
        _actualIter = std::next(_actualIter);
        ret = true;
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
uint16_t PointConnIter::getActualConnHash() const
{
    return _actualIter->first;
}
//--------------------------------------------------------------------------------------------------
uint16_t PointConnIter::getActualConnCost() const
{
    return _actualIter->second;
}
//--------------------------------------------------------------------------------------------------
void PointConnIter::viewAllConnHashes() const
{
    for(const auto& bla : *_conns)
    {
        qDebug() << "Conn hash " << bla.first;
    }
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::moveUntilFind(const uint16_t searchPointHash)
{
    bool ret{false};

    while(!isAtEnd())
    {
        if(searchPointHash == _actualIter->first)
        {
            ret = true;
            break;
        }
        else
        {
            moveNext();
        }
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
bool PointConnIter::moveUntilFind(const uint16_t searchPointHash, const bool reset)
{
    if(reset)
    {
        _actualIter = _conns->begin();
    }

    const bool ret{moveUntilFind(searchPointHash)};

    if(!ret)
    {
        _actualIter = _conns->begin();
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------















