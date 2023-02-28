#include "winhello.h"
#include "ui_winhello.h"

WinHello::WinHello(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinHello)
{
    ui->setupUi(this);
}

WinHello::~WinHello()
{
    delete ui;
}
