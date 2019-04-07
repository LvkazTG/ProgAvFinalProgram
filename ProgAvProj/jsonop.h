#ifndef JSONOP_H
#define JSONOP_H

#include <QObject>

class MapaObj;

class JsonOp : public QObject
{
    Q_OBJECT
public:
    explicit JsonOp(QObject *parent = nullptr);

    bool saveMap(const MapaObj& map,const std::string mapFile);

    MapaObj loadMap(const std::string mapFile);

signals:

public slots:
};

#endif // JSONOP_H
