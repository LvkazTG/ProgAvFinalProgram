#include "formatop.h"

#include <QFile>

#include "mapaobj.h"
#include "connlist.h"
//--------------------------------------------------------------------------------------------------
FormatOp::FormatOp(QObject *parent) : QObject{parent}
{

}
//--------------------------------------------------------------------------------------------------
bool FormatOp::saveMap(const MapaObj& map, const std::string mapFile)
{
    bool ret{true};

    const auto contentToSave{generateContentToSave(map)};

    QFile saveFile{QString::fromStdString(mapFile)};
    saveFile.open(QIODevice::WriteOnly);
    const auto quantWrite{saveFile.write(contentToSave)};
    saveFile.close();

    if(quantWrite <= 0)
    {
       ret = false;
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
MapaObj FormatOp::loadMap(const std::string mapFile)
{
    std::vector<QString> expectedKeys{"mapName", "xSize", "ySize", "points"};
    ConnList newConnList{};

    QFile loadFile{QString::fromStdString(mapFile)};
    loadFile.open(QIODevice::ReadOnly);

    const auto fileContent{loadFile.readAll()};

    loadFile.close();

    return generateLoadContent(fileContent);
}
//--------------------------------------------------------------------------------------------------
QByteArray FormatOp::generateContentToSave(const MapaObj& map)
{
    initialActionsSave();
    createMapHeaderData(map);

    for(const auto& elemInfos : map.getConnList().getConnectedMap())
    {
        createPointData(map.getPoint(elemInfos.first));
        for(const auto& elemConn : elemInfos.second)
        {
            createPointConnData(elemConn);
        }
        connectPointToItsData();
    }

    connectPointsInMapData();

    return getDataToSave();
}
//--------------------------------------------------------------------------------------------------
MapaObj FormatOp::generateLoadContent(const QByteArray fileContent)
{
    _newPoints = std::make_unique<std::vector<std::shared_ptr<PointObj>>>();

    initialActions(fileContent);
    checkAllKeys();
    auto [mapName, mapXSize, mapYSize, newConnList] = loadActions();

    MapaObj ret{mapXSize, mapXSize};
    ret.setName(mapName);
    ret.initMap(*_newPoints, newConnList);

    return ret;
}
//--------------------------------------------------------------------------------------------------
