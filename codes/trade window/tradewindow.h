#ifndef tradewindow_H
#define tradewindow_H

#include <QWidget>
#include <QtWidgets>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class tradewindow; }
QT_END_NAMESPACE

class tradewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tradewindow(QWidget *parent = nullptr);
    ~tradewindow();

    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);

public slots:
    void TradeRequest();
    void waitForCheckingConditions();

private:
    Ui::tradewindow *ui;
};

#endif // tradewindow_H
