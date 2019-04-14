#include "xmlop.h"

#include "mapaobj.h"
#include "connlist.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
xmlOp::xmlOp(QObject *parent) : FormatOp(parent)
{

}
//--------------------------------------------------------------------------------------------------
void xmlOp::initialActionsSave()
{
    _contentBuffer = std::make_unique<QByteArray>();
    _xmlWriter = std::make_unique<QXmlStreamWriter>(_contentBuffer.get());

    _xmlWriter->setAutoFormatting(true);
    _xmlWriter->setAutoFormattingIndent(2);

    _xmlWriter->writeStartDocument();
}
//--------------------------------------------------------------------------------------------------
void xmlOp::createMapHeaderData(const MapaObj& map)
{
    _xmlWriter->writeStartElement("MapDescrition");
    _xmlWriter->writeStartElement("MapInfo");
    _xmlWriter->writeAttribute("mapName", QString::fromStdString(map.getName()));
    _xmlWriter->writeAttribute("xSize", QString::number(map.getXSize()));
    _xmlWriter->writeAttribute("ySize", QString::number(map.getYSize()));

    _xmlWriter->writeStartElement("Points");
}
//--------------------------------------------------------------------------------------------------
void xmlOp::createPointData(const std::shared_ptr<PointObj>& point)
{
    _xmlWriter->writeStartElement("Point");
    _xmlWriter->writeAttribute("pointName", QString::fromStdString(point->getName()));
    _xmlWriter->writeAttribute("xCoord", QString::number(point->getX()));
    _xmlWriter->writeAttribute("yCoord", QString::number(point->getY()));
}
//--------------------------------------------------------------------------------------------------
void xmlOp::createPointConnData(const std::pair<uint16_t, uint8_t>& pointSingleConnData)
{
    _xmlWriter->writeStartElement("PointConn");
    _xmlWriter->writeAttribute("hashConn", QString::number(pointSingleConnData.first));
    _xmlWriter->writeAttribute("costConn", QString::number(pointSingleConnData.second));
    _xmlWriter->writeEndElement();
}
//--------------------------------------------------------------------------------------------------
void xmlOp::connectPointToItsData()
{
    // The sequencial writing of xml ensure connection, but need to close element
    _xmlWriter->writeEndElement();
}
//--------------------------------------------------------------------------------------------------
void xmlOp::connectPointsInMapData()
{
    // The sequencial writing of xml ensure connection, but need to close elements created
    _xmlWriter->writeEndElement();
    _xmlWriter->writeEndElement();
    _xmlWriter->writeEndElement();

    _xmlWriter->writeEndDocument();
}
//--------------------------------------------------------------------------------------------------
QByteArray xmlOp::getDataToSave()
{
    return *_contentBuffer;
}
//--------------------------------------------------------------------------------------------------
bool xmlOp::checkAllKeys()
{
    //pass for now
}
//--------------------------------------------------------------------------------------------------
void xmlOp::initialActions(const QByteArray fileContent)
{
    _xmlReader = std::make_unique<QXmlStreamReader>(fileContent);
}
//--------------------------------------------------------------------------------------------------
std::tuple<const std::string, const uint8_t, const uint8_t, ConnList> xmlOp::loadActions()
{
    uint8_t mapXSize{0};
    uint8_t mapYSize{0};
    std::string mapName{""};

    uint16_t actualHash{0};
    ConnList newConnList{};

    while(!_xmlReader->atEnd())
    {
        if(!_xmlReader->isEndElement())
        {
            const auto xmlName{_xmlReader->name()};
            if(xmlName == "MapInfo")
            {
                const auto xmlAttrib{_xmlReader->attributes()};
                mapName = xmlAttrib.value("mapName").toString().toStdString();
                mapXSize = static_cast<uint8_t>(xmlAttrib.value("xSize").toInt());
                mapYSize = static_cast<uint8_t>(xmlAttrib.value("ySize").toInt());
            }
            else if(xmlName == "Point")
            {
                const auto xmlAttrib{_xmlReader->attributes()};
                auto newPoint{std::make_shared<PointObj>(xmlAttrib.value("xCoord").toInt(),
                                                         xmlAttrib.value("yCoord").toInt())};
                newPoint->setName(xmlAttrib.value("pointName").toString().toStdString());

                actualHash = newPoint->getHash();
                // Ensure connList will have elem even if it is not connected to any point
                newConnList.createEmptyHashEntry(actualHash);

                _newPoints->emplace_back(std::move(newPoint));
            }
            else if (xmlName == "PointConn")
            {
                const auto xmlAttrib{_xmlReader->attributes()};
                newConnList.connectNewPoint(actualHash,
                                            static_cast<uint16_t>(xmlAttrib.value("hashConn").toInt()),
                                            static_cast<uint8_t>(xmlAttrib.value("costConn").toInt()));
            }
            else
            {
                // Do nothing, read next
            }
        }

        _xmlReader->readNext();
    }

    const std::tuple<const std::string, const uint8_t, const uint8_t, ConnList>
            ret{std::move(mapName), mapXSize, mapYSize, std::move(newConnList)};


    return ret;
}
//--------------------------------------------------------------------------------------------------
