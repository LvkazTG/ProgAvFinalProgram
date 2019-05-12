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
    explicit searchUserStart(const MapaObj* map, std::shared_ptr<BaseSearch> searchUsing,
                             QWidget *parent = nullptr);
    ~searchUserStart();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::searchUserStart *ui{nullptr};
    const MapaObj* _map{nullptr};
    std::shared_ptr<BaseSearch> _searchMetUsing{nullptr};

    std::tuple<std::shared_ptr<PointObj>, const bool>
        searchUserInfoSinglePoint(const QLineEdit* lnName,
                                  const QLineEdit* lnX,
                                  const QLineEdit* lnY);
};

#endif // SEARCHUSERSTART_H
