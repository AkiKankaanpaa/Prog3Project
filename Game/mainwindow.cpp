#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setFixedSize(QSize(500, 500));
    QPixmap pix(":/images/kartta.png");
//    ui->backgroundLabel->setPixmap(pix);
    scene_ = new QGraphicsScene(this);
//    ui->MapView->setFixedSize(500, 500);
    ui->MapView->setScene(scene_);
    scene_->setSceneRect(0,0,800,800);
//    scene_->setBackgroundBrush(QImage(":/images/kartta.png"));
    scene_->addPixmap(pix);
    ui->MapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    startup_ = new StartupWindow(this);
    startup_->show();
    connect(startup_, &StartupWindow::rejected, this, &MainWindow::close);
    connect(startup_, &StartupWindow::difficulty_signal, this, &MainWindow::create_game);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_game()
{
    erection_ = scene_->addRect(0,0,10,10);
    bus_ = new PlayerBus(erection_);
    erection_->setBrush(Qt::blue);
}



void MainWindow::on_downButton_clicked()
{
    bus_->move(DOWN);
    ui->ylabel->setText("Y = " + QString::number(erection_->y()));
}

void MainWindow::on_leftButton_clicked()
{
    bus_->move(LEFT);
    ui->xlabel->setText("X = " + QString::number(erection_->x()));
}

void MainWindow::on_rightButton_clicked()
{
    bus_->move(RIGHT);
    ui->xlabel->setText("X = " + QString::number(erection_->x()));
}

void MainWindow::on_upButton_clicked()
{
    bus_->move(UP);
    ui->ylabel->setText("Y = " + QString::number(erection_->y()));
}

void MainWindow::on_coordinateButton_clicked()
{
    QString joo = QString::number(erection_->x()) + " " + QString::number(erection_->y());
    ErrorBox *coordinates = new ErrorBox(this, joo);
    coordinates->show();
}
