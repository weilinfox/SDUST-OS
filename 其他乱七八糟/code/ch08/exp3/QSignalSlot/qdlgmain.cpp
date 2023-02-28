#include "qdlgmain.h"
#include "ui_qdlgmain.h"
#include "qdlgchild.h"  //子对话框头文件

QDlgMain::QDlgMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDlgMain)
{
    ui->setupUi(this);
}

QDlgMain::~QDlgMain()
{
    delete ui;
}

void QDlgMain::on_btnNew_clicked()
{
    //新建并显示一个子对话框
    QDlgChild  *pDlg=new QDlgChild(this);
    pDlg->show();
}
