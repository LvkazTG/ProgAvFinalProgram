#include "xmlop.h"

#include <QXmlStreamWriter>

#include <QFile>

#include "mapaobj.h"
#include "connlist.h"

#include "pointobj.h"
#include "memory"

#include <QFileDialog>

#include <QDebug>

xmlOp::xmlOp(QObject *parent) : QObject(parent)
{

}

bool xmlOp::saveMap(const MapaObj& map, const std::string mapFile)
{
    bool ret{true};

    QFile saveFile{mapFile.c_str()};
    saveFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter{&saveFile};
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("MapDescrition");
    xmlWriter.writeStartElement("MapInfo");
    xmlWriter.writeAttribute("mapName", QString::fromStdString(map.getName()));
    xmlWriter.writeAttribute("xSize", QString::number(map.getXSize()));
    xmlWriter.writeAttribute("ySize", QString::number(map.getYSize()));

    xmlWriter.writeStartElement("Points");
    for(const auto& elemInfos : map.getConnList().getConnectedMap())
    {
        const auto& point{map.getPoint(elemInfos.first)};
        xmlWriter.writeStartElement("Point");
        xmlWriter.writeAttribute("pointName", QString::fromStdString(point->getName()));
        xmlWriter.writeAttribute("xCoord", QString::number(point->getX()));
        xmlWriter.writeAttribute("yCoord", QString::number(point->getY()));

        for(const auto& elemConn : elemInfos.second)
        {
            xmlWriter.writeStartElement("PointConn");
            xmlWriter.writeAttribute("hashConn", QString::number(elemConn.first));
            xmlWriter.writeAttribute("costConn", QString::number(elemConn.second));
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();

    }


    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    saveFile.close();


//    QString filename = QFileDialog::getSaveFileName(this,
//                                       tr("Save Xml"), ".",
//                                       tr("Xml files (*.xml)"));


//    QFile file(filename);
//    file.open(QIODevice::WriteOnly);

//    QXmlStreamWriter xmlWriter2(&file);
//    xmlWriter2.setAutoFormatting(true);
//    xmlWriter2.writeStartDocument();

//    xmlWriter2.writeStartElement("LAMPS");

//    xmlWriter2.writeStartElement("LIGHT1");
//    xmlWriter2.writeTextElement("State", "statevalue" );
//    xmlWriter2.writeTextElement("Room", "roomvalue");
//    xmlWriter2.writeTextElement("Potencial", "potencialvalue");

//    xmlWriter2.writeEndElement();

//    file.close();

    return ret;
}

MapaObj xmlOp::loadMap(const std::string mapFile)
{
    QFile loadFile(mapFile.c_str());
    loadFile.open(QFile::ReadOnly);

    QXmlStreamReader xmlReader(&loadFile);

    uint8_t mapXSize{0};
    uint8_t mapYSize{0};
    std::string mapName{""};

    uint16_t actualHash{0};
    std::vector<std::shared_ptr<PointObj>> newPoints{};
    ConnList newConnList{};


    while(!xmlReader.atEnd())
    {
        if(!xmlReader.isEndElement())
        {
            const auto xmlName{xmlReader.name()};
            if(xmlName == "MapInfo")
            {
                auto xmlAttrib{xmlReader.attributes()};
                mapName = xmlAttrib.value("mapName").toString().toStdString();
                mapXSize = static_cast<uint8_t>(xmlAttrib.value("xSize").toInt());
                mapYSize = static_cast<uint8_t>(xmlAttrib.value("ySize").toInt());
            }
            else if(xmlName == "Point")
            {
                auto xmlAttrib{xmlReader.attributes()};
                auto newPoint{std::make_shared<PointObj>(xmlAttrib.value("xCoord").toInt(),
                                                         xmlAttrib.value("yCoord").toInt())};
                newPoint->setName(xmlAttrib.value("pointName").toString().toStdString());

                actualHash = newPoint->getHash();
                // Ensure connList will have elem even if it is not connected to any point
                newConnList.createEmptyHashEntry(actualHash);

                newPoints.emplace_back(std::move(newPoint));
            }
            else if (xmlName == "PointConn")
            {
                auto xmlAttrib{xmlReader.attributes()};
                newConnList.connectNewPoint(actualHash,
                                            static_cast<uint16_t>(xmlAttrib.value("hashConn").toInt()),
                                            static_cast<uint8_t>(xmlAttrib.value("costConn").toInt()));
            }
            else
            {
                // Do nothing, read next
            }
        }

        xmlReader.readNext();
    }

    loadFile.close();

    MapaObj ret{mapXSize, mapYSize};
    ret.setName(mapName);
    ret.initMap(newPoints, newConnList);

    return ret;
}


















