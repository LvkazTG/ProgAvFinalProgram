#ifndef SEARCHRESULTDLG_H
#define SEARCHRESULTDLG_H

#include <QDialog>

#include <memory>

class QTableWidget;

class MapaObj;
class PointObj;

namespace Ui
{
    class SearchResultDlg;
}

class SearchResultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SearchResultDlg(const MapaObj* map, QWidget *parent);
    ~SearchResultDlg();

private slots:
    void on_btnClose_clicked();

private:
    Ui::SearchResultDlg *ui{nullptr};

    void addRow(QTableWidget* tbl, const std::shared_ptr<PointObj>& pointInfo,
                const uint8_t pointCost);

};

#endif // SEARCHRESULTDLG_H
