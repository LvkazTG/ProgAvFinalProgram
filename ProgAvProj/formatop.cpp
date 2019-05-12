#include "formatop.h"

#include <QFile>

#include "mapaobj.h"
#include "connlist.h"
#include "searchstatistics.h"
//--------------------------------------------------------------------------------------------------
FormatOp::FormatOp(QObject *parent) : QObject{parent}
{

}
//--------------------------------------------------------------------------------------------------
bool FormatOp::saveMap(const MapaObj& map, const std::string& mapFile)
{
    return execSaveOperations(mapFile, generateContentToSaveMap(map));
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
QByteArray FormatOp::generateContentToSaveMap(const MapaObj& map)
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
bool FormatOp::saveStatistics(const SearchStatistics& statObj, const MapaObj& actualMap,
                              const std::string& statFile)
{
    return execSaveOperations(statFile, generateContentToSaveStatistics(statObj, actualMap));
}
//--------------------------------------------------------------------------------------------------
QByteArray FormatOp::generateContentToSaveStatistics(const SearchStatistics& statObj,
                                                     const MapaObj& actualMap)
{
    initialActionsSave();
    createMapMinimumData(actualMap);
    createStatInfo(statObj);

    return getDataToSave();
}
//--------------------------------------------------------------------------------------------------
bool FormatOp::execSaveOperations(const std::string& filename, const QByteArray content) const
{
    QFile saveFile{QString::fromStdString(filename)};
    saveFile.open(QIODevice::WriteOnly);
    const auto quantWrite{saveFile.write(content)};
    saveFile.close();

    return (quantWrite > 0);
}
//--------------------------------------------------------------------------------------------------





















