// Reading on internet, alter nested json parts is "not supported"
// https://stackoverflow.com/questions/17034336/how-to-change-qjsonobject-value-in-a-qjson-hierarchy-without-using-copies

#include "jsonop.h"

#include <QJsonDocument>

#include "mapaobj.h"
#include "connlist.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
JsonOp::JsonOp(QObject *parent) : FormatOp{parent}
{

}
//--------------------------------------------------------------------------------------------------
void JsonOp::initialActionsSave()
{
    _obj = std::make_unique<QJsonObject>();
}
//--------------------------------------------------------------------------------------------------
void JsonOp::createMapHeaderData(const MapaObj& map)
{
    if(nullptr != _obj)
    {
        auto& objData{*_obj};
        objData["mapName"] = QString::fromStdString(map.getName());
        objData["xSize"] = map.getXSize();
        objData["ySize"] = map.getYSize();
    }

    _objPoints = std::make_unique<QJsonArray>();
}
//--------------------------------------------------------------------------------------------------
void JsonOp::createPointData(const std::shared_ptr<PointObj>& point)
{
    _objSinglePoint = std::make_unique<QJsonObject>();

    auto& objSinglePointData{*_objSinglePoint};
    objSinglePointData["pointName"] = QString::fromStdString(point->getName());
    objSinglePointData["xCoord"] = point->getX();
    objSinglePointData["yCoord"] = point->getY();

    _objPointsConn = std::make_unique<QJsonArray>();
}
//--------------------------------------------------------------------------------------------------
void JsonOp::createPointConnData(const std::pair<uint16_t, uint8_t>& pointSingleConnData)
{
    if(nullptr != _objPointsConn)
    {
        QJsonObject objConnInfo{};
        objConnInfo["hashConn"] = pointSingleConnData.first;
        objConnInfo["costConn"] = pointSingleConnData.second;

        _objPointsConn->push_back(objConnInfo);
    }
    else
    {
        // Error
    }
}
//--------------------------------------------------------------------------------------------------
void JsonOp::connectPointToItsData()
{
    if((nullptr != _objPointsConn) && (nullptr != _objSinglePoint) &&
       (nullptr != _objPoints))
    {
        (*_objSinglePoint)["pointConns"] = *_objPointsConn;
        _objPoints->push_back(*_objSinglePoint);

        _objSinglePoint = nullptr;
        _objPointsConn = nullptr;
    }
    else
    {
        // Error
    }
}
//--------------------------------------------------------------------------------------------------
void JsonOp::connectPointsInMapData()
{
    if((nullptr != _objPoints) && (nullptr != _obj))
    {
        (*_obj)["points"] = *_objPoints;

        _objPoints = nullptr;
    }
    else
    {
        // Error
    }
}
//--------------------------------------------------------------------------------------------------
QByteArray JsonOp::getDataToSave()
{
    QJsonDocument objDoc{*_obj};
    return objDoc.toJson();
}
//--------------------------------------------------------------------------------------------------
bool JsonOp::checkAllKeys()
{
    //pass for now
}
//--------------------------------------------------------------------------------------------------
void JsonOp::initialActions(const QByteArray fileContent)
{
    const QJsonDocument objDoc{QJsonDocument::fromJson(fileContent)};

    _obj = std::make_unique<QJsonObject>(objDoc.object());

// Do check for error later
//    std::vector<QString> expectedKeys{"mapName", "xSize", "ySize", "points"};

    const auto objAllKeys{_obj->keys()};
    const bool hasAllKeys{!objAllKeys.empty() && objAllKeys.contains("points")};

    if(!hasAllKeys)
    {
        qDebug() << "Error! Expected itens on json not found";
    }
    else
    {
        // Can continue
    }
    Q_ASSERT(hasAllKeys);

    _newPoints->reserve((*_obj)["points"].toArray().size());
}
//--------------------------------------------------------------------------------------------------
std::tuple<const std::string, const uint8_t, const uint8_t, ConnList> JsonOp::loadActions()
{
    auto& objData{*_obj};

    ConnList newConnList{};

    // To check this warning when have time
    for(const auto& point : objData["points"].toArray())
    {
        const auto objPoint{point.toObject()};
        auto newPoint{std::make_shared<PointObj>(objPoint["xCoord"].toInt(), objPoint["yCoord"].toInt())};
        newPoint->setName(objPoint["pointName"].toString().toStdString());

        std::map<uint16_t, uint8_t> pointLoadConns{};

        // To check this warning when have time
        for(const auto& pointConn : objPoint["pointConns"].toArray())
        {
            auto objPointConn{pointConn.toObject()};
            pointLoadConns.emplace(objPointConn["hashConn"].toInt(), objPointConn["costConn"].toInt());
        }
        newConnList.connectPoints(newPoint->getHash(), pointLoadConns);

        _newPoints->emplace_back(std::move(newPoint));
    }

    const std::tuple<const std::string, const uint8_t, const uint8_t, ConnList>
            ret{objData["mapName"].toString().toStdString(),
                static_cast<uint8_t>(objData["xSize"].toInt()),
                static_cast<uint8_t>(objData["xSize"].toInt()),
                std::move(newConnList)};

    return ret;
}
//--------------------------------------------------------------------------------------------------
