#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QtWidgets>
#include "tradewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);

public slots:
    void goToTradeWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
