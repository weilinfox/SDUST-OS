#ifndef QDLGMAIN_H
#define QDLGMAIN_H

#include <QDialog>

namespace Ui {
class QDlgMain;
}

class QDlgMain : public QDialog
{
    Q_OBJECT

public:
    explicit QDlgMain(QWidget *parent = 0);
    ~QDlgMain();

private slots:
    void on_btnNew_clicked();

private:
    Ui::QDlgMain *ui;
};

#endif // QDLGMAIN_H
