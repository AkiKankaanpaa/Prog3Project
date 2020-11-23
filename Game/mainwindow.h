#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include "startupwindow.h"
#include <QImage>
#include <QGraphicsRectItem>
#include "playerbus.h"
#include <QGraphicsItem>
#include <vector>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void create_game();

private slots:
    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_upButton_clicked();

    void on_coordinateButton_clicked();

private:
    Ui::MainWindow *ui;
    StartupWindow *startup_;
    QGraphicsScene *scene_;
    std::vector<QGraphicsRectItem*> maprects_;

    QGraphicsRectItem *erection_;
    PlayerBus* bus_;
};



#endif // MAINWINDOW_H
