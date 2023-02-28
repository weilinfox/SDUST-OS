#ifndef WINHELLO_H
#define WINHELLO_H

#include <QMainWindow>

namespace Ui {
class WinHello;
}

class WinHello : public QMainWindow
{
    Q_OBJECT

public:
    explicit WinHello(QWidget *parent = 0);
    ~WinHello();

private:
    Ui::WinHello *ui;
};

#endif // WINHELLO_H
