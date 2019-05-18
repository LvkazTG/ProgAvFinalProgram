#include "searchdeep.h"

#include "pointobj.h"

#include <QDebug>

using namespace Search;
//--------------------------------------------------------------------------------------------------
SearchDeep::SearchDeep(const MapaObj& map) : BaseSearch{map}
{
    setSearchType("Deep");
}
//--------------------------------------------------------------------------------------------------
void SearchDeep::initLoopConditions()
{
    _previousError = false;
    _popLastElem = false;
}
//--------------------------------------------------------------------------------------------------
bool SearchDeep::extraConditionLoopSearch() const
{
    // No extra conditional break of loop stipulated
    return true;
}
//--------------------------------------------------------------------------------------------------
void SearchDeep::principalLoopSearch()
{
    // Advance
    auto iterToEnd{_actualPath.rbegin()};

//    auto printer{qDebug()};
//    for(const auto& elemIt : _actualPath)
//    {
//        printer << "Point " << QString::fromStdString(bla->getPoint(elemIt.getPointHash())->getName()) << " ";
//    }
//    printer << "finished this path print";


    if(_previousError)
    {
        if(_popLastElem)
        {
            _actualPath.pop_back();
            iterToEnd = _actualPath.rbegin();
            _popLastElem = false;
        }

        _previousError = false;
//            iterSamePos = true;

        // Enough?
        if((_actualPath.empty()))
        {
            _keepSearchGoing = false;

            // Force end loop
            // Done altering _keepSearchGoing flag
            // No more action needed for now
            //break;
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
            _previousError = true;
            _popLastElem = true;

            //Force next iteraction here
            // No more action needed for now
            //continue;
        }
    }
    else
    {
        bool directToEnd{false};

        const auto newConnHash{iterToEnd->getActualConnHash()};
        _searchStats.addNewPointVisited(newConnHash);

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
            _popLastElem = false;
            _previousError = true;

            directToEnd = true;

            //Force next iteraction here
            // Doing it with directToEnd flag
            //continue;
        }

        if(!directToEnd)
        {
            _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
            iterToEnd = _actualPath.rbegin();
        }


        if(!directToEnd)
        {

            // Check if is solution
            const auto [isEnd, isLessExpensive] = validateEnd(iterToEnd->getPointHash());
            if(!isEnd)
            {
                if(!isLessExpensive)
                {
                    _previousError = true;
                    _popLastElem = true;
                }

            }
            else
            {
                _previousError = true;
                _popLastElem = true;
            }

            // Check if is better than best
            // Update cost (check error)
        }
    }
}
//--------------------------------------------------------------------------------------------------
