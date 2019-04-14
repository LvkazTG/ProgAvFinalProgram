#include "jsonop.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "mapaobj.h"
#include "connlist.h"

#include "pointobj.h"
#include "memory"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
JsonOp::JsonOp(QObject *parent) : QObject(parent)
{

}
//--------------------------------------------------------------------------------------------------
bool JsonOp::saveMap(const MapaObj& map, const std::string mapFile)
{
    bool ret{true};

    QJsonObject obj{};
    obj["mapName"] = QString::fromStdString(map.getName());
    obj["xSize"] = map.getXSize();
    obj["ySize"] = map.getYSize();

    QJsonArray objAllPoints{};
    for(const auto& elemInfos : map.getConnList().getConnectedMap())
    {
        QJsonObject objPoint{};
        const auto& point{map.getPoint(elemInfos.first)};

        objPoint["pointName"] = QString::fromStdString(point->getName());
        objPoint["xCoord"] = point->getX();
        objPoint["yCoord"] = point->getY();
        QJsonArray objPontosConn{};
        for(const auto& elemConn : elemInfos.second)
        {
            QJsonObject objConnInfo{};
            objConnInfo["hashConn"] = elemConn.first;
            objConnInfo["costConn"] = elemConn.second;
            objPontosConn.push_back(objConnInfo);
        }
        objPoint["pointConns"] = objPontosConn;

        objAllPoints.push_back(objPoint);
    }

    obj["points"] = objAllPoints;

    QJsonDocument objDoc{obj};
    QFile saveFile{QString::fromStdString(mapFile)};
    saveFile.open(QIODevice::WriteOnly);
    const auto quantWrite{saveFile.write(objDoc.toJson())};
    saveFile.close();

    if(quantWrite <= 0)
    {
       ret = false;
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
MapaObj JsonOp::loadMap(const std::string mapFile)
{
    std::vector<QString> expectedKeys{"mapName", "xSize", "ySize", "points"};
    ConnList newConnList{};

    QFile loadFile{QString::fromStdString(mapFile)};
    loadFile.open(QIODevice::ReadOnly);
    QJsonDocument objDoc{QJsonDocument::fromJson(loadFile.readAll())};
    loadFile.close();

    auto obj{objDoc.object()};
    const auto objAllKeys{obj.keys()};

    bool hasAllKeys{!objAllKeys.empty()};
    for(const auto& item : expectedKeys)
    {
        hasAllKeys &= objAllKeys.contains(item);
    }

    if(!hasAllKeys)
    {
        qDebug() << "Error! Expected itens on json not found";
    }
    else
    {
        // Can continue
    }
    Q_ASSERT(hasAllKeys);

    std::vector<std::shared_ptr<PointObj>> newPoints{};
    newPoints.reserve(obj["points"].toArray().size());

    // To check this warning when have time
    for(const auto& point : obj["points"].toArray())
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

        newPoints.emplace_back(std::move(newPoint));
    }

    MapaObj ret{static_cast<uint8_t>(obj["xSize"].toInt()), static_cast<uint8_t>(obj["xSize"].toInt())};
    ret.setName(obj["mapName"].toString().toStdString());
    ret.initMap(newPoints, newConnList);

    return ret;
}
//--------------------------------------------------------------------------------------------------



