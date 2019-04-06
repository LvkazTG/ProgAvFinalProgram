#include "jsonop.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "mapaobj.h"
#include "connlist.h"

JsonOp::JsonOp(QObject *parent) : QObject(parent)
{

}

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

