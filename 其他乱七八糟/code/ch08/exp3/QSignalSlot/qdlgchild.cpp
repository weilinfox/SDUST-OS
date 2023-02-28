#include "qdlgchild.h"
#include "ui_qdlgchild.h"

QDlgChild::QDlgChild(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDlgChild)
{
    ui->setupUi(this);
}

QDlgChild::~QDlgChild()
{
    delete ui;
}
