#ifndef SEARCHUSERSTART_H
#define SEARCHUSERSTART_H

#include <QDialog>

namespace Ui {
class searchUserStart;
}

class searchUserStart : public QDialog
{
    Q_OBJECT

public:
    explicit searchUserStart(QWidget *parent = nullptr);
    ~searchUserStart();

private:
    Ui::searchUserStart *ui;
};

#endif // SEARCHUSERSTART_H
