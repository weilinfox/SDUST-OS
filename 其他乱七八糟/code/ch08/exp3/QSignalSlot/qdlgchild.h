#ifndef QDLGCHILD_H
#define QDLGCHILD_H

#include <QDialog>

namespace Ui {
class QDlgChild;
}

class QDlgChild : public QDialog
{
    Q_OBJECT

public:
    explicit QDlgChild(QWidget *parent = 0);
    ~QDlgChild();

private:
    Ui::QDlgChild *ui;
};

#endif // QDLGCHILD_H
