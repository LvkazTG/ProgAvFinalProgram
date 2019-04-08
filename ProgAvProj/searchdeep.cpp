#include "searchdeep.h"
#include <limits>

#include <QDebug>
#include "pointobj.h"
static MapaObj const* bla{nullptr};

SearchDeep::SearchDeep(const MapaObj& map, const std::string startPoint, const std::string endPoint) :
    _bestPathCost{std::numeric_limits<uint64_t>::max()}
{
    bla = &map;

    const auto startElem{map.getPointByName(startPoint)};
    if(startElem != nullptr)
    {
        _startHash = startElem->getHash();
    }

    const auto endElem{map.getPointByName(endPoint)};
    if(endElem != nullptr)
    {
        _endHash = endElem->getHash();
    }

    _connMapList = &map.getConnList();
}

bool SearchDeep::init()
{
    bool ret{false};

    _actualPath.emplace_back(_startHash, _connMapList->getConnectedMapElem(_startHash));

    qDebug() << "First Conn hash" << _actualPath.begin()->getActualConnHash();

    bool keepSearchGoing{true};
    bool previousError{false};
    bool iterSamePos{true};
    bool popLastElem{false};

    while(keepSearchGoing)
    {
        // Advance
        auto iterToEnd{_actualPath.rbegin()};

        auto printer{qDebug()};
        for(const auto& elemIt : _actualPath)
        {
            printer << "Point " << QString::fromStdString(bla->getPoint(elemIt.getPointHash())->getName()) << " ";
        }
        printer << "finished this path print";


        if(previousError)
        {
            if(popLastElem)
            {
                _actualPath.pop_back();
                iterToEnd = _actualPath.rbegin();
                popLastElem = false;
            }

            previousError = false;
//            iterSamePos = true;

            // Enough?
            if((_actualPath.empty()))
            {
                keepSearchGoing = false;
                break;
            }
            else if(!iterToEnd->isOnLastValidIter())
            {
//                if(iterToEnd->getPointHash() == 2)
//                {
//                    qDebug() << "View all";
//                    iterToEnd->viewAllConnHashes();
//                }

//                if(iterToEnd->getPointHash() == 2)
//                {
////                    qDebug() << iterToEnd->getActualConnHash();
////                    qDebug() << "Normal?";
//                }

                bool view{iterToEnd->moveNext()};

//                if(iterToEnd->getPointHash() == 2)
//                {
////                    qDebug() << iterToEnd->getActualConnHash();
////                    qDebug() << "Strange?";
//                }

//                qDebug() << "View" << (view ? "Ok" : "Nok");
//                qDebug() << "Deb point";
            }
            else
            {
                previousError = true;
                popLastElem = true;
                continue;
            }
        }
        else
        {
            if(iterSamePos)
            {
                iterSamePos = false;
                //pass
            }
            else
            {
                const auto newConnHash{iterToEnd->getActualConnHash()};

                // Check presence in list (define error)

                bool alreadyInPath{false};
                for(const auto& elemInPath : _actualPath)
                {
                    if(elemInPath.getPointHash() == newConnHash)
                    {
                        alreadyInPath = true;
                        break;
                    }
                }

                if(alreadyInPath)
                {
                    // Remove later the popLastElem as false as is not needed but keep comment
                    // Its not necessary here, but is good to mark it
                    popLastElem = false;
                    previousError = true;
                    continue;
                }

                _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
                iterToEnd = _actualPath.rbegin();

            }

            // Check if is solution
            if(iterToEnd->getPointHash() == _endHash)
            {
                // calculate cost
                calculateActualCost();

                // If solution is better
                if(_actualPathCost < _bestPathCost)
                {
                    _bestPathCost = _actualPathCost;
                    _bestPath = _actualPath;

                    //Debug
//                    keepSearchGoing = false;
//                    continue;
                }

                previousError = true;
                popLastElem = true;
            }
            else
            {
                // calculate cost
                calculateActualCost();

                if(_actualPathCost >= _bestPathCost)
                {
                    previousError = true;
                    popLastElem = true;
                }
            }

            // Check if is better than best
            // Update cost (check error)
        }
    }


    ret = !_bestPath.empty();

    qDebug() << "Final route if any\n";
    for(const auto& elemIt : _bestPath)
    {
        qDebug() << "Point " << QString::fromStdString(bla->getPoint(elemIt.getPointHash())->getName()) << " " << "Hash " << elemIt.getPointHash() << "Cost " << elemIt.getActualConnCost();
    }
    qDebug() << "\n Cost " << _bestPathCost;


    return ret;
}

void SearchDeep::calculateActualCost()
{
    _actualPathCost = 0;

//    qDebug() << "List size " << _actualPath.size();
    for(auto it{_actualPath.begin()} ; _actualPath.end() != it ; it++)
    {
        const auto itNext{std::next(it)};
        if(itNext == _actualPath.end())
        {
            break;
        }

        _actualPathCost += it->getActualConnCost();
//        qDebug() << "new cost "<< _actualPathCost;
    }
}






















