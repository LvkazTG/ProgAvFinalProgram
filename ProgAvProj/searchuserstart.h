#ifndef SEARCHUSERSTART_H
#define SEARCHUSERSTART_H

#include <QDialog>
#include <memory>
#include <tuple>
#include <basesearch.h>

class QLineEdit;

class MapaObj;
class PointObj;

namespace Ui
{
    class searchUserStart;
}

class searchUserStart : public QDialog
{
    Q_OBJECT

public:
    explicit searchUserStart(const MapaObj* map, QWidget *parent = nullptr);
    ~searchUserStart();

    void useManualSearch(const bool status);

private slots:
    void on_btnClose_clicked();

    void on_btnStart_clicked();

private:
    Ui::searchUserStart *ui{nullptr};
    const MapaObj* _map{nullptr};
    bool _useManualSearch{false};

    std::tuple<std::shared_ptr<PointObj>, const bool>
        searchUserInfoSinglePoint(const QLineEdit* lnName,
                                  const QLineEdit* lnX,
                                  const QLineEdit* lnY);

    void informRunning();
    void informRunningStop();

};

#endif // SEARCHUSERSTART_H
