#ifndef XMLOP_H
#define XMLOP_H

#include <QObject>

class MapaObj;

class xmlOp : public QObject
{
    Q_OBJECT
public:
    explicit xmlOp(QObject *parent = nullptr);

    bool saveMap(const MapaObj& map,const std::string mapFile);
    MapaObj loadMap(const std::string mapFile);

signals:

public slots:
};

#endif // XMLOP_H
