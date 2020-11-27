#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    legal_coordinates_(new std::map<int, std::vector<int>>),
    ui(new Ui::MainWindow),
    bus_(nullptr)

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

void MainWindow::read_coordinates(int current_level)
{

    QFile file(":/coordinatestxt/kaupunki.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ;
    } else { 
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            std::string x_line = line.toStdString();
            qDebug() << line;
            insert_coordinates(x_line);
        }
    }
}

void MainWindow::insert_coordinates(std::string x_line)
{
    std::string x = x_line.substr(0, x_line.find(":"));
    x_line.erase(x_line.begin(), x_line.begin()+x.size()+1);
    std::istringstream stream(x_line);

    std::vector<int> y_vec;
    char delimiter = ',';

    std::string current_yvalue;

    std::pair<int,std::vector<int>> current;

    while (getline(stream, current_yvalue, delimiter)) {
        int int_y = stoi(current_yvalue);
        y_vec.push_back(int_y);
    }
    legal_coordinates_->insert({stoi(x), y_vec});
}

void MainWindow::check_pedestrian_collision()
{
    std::vector<unsigned int> pedestrians;
    std::pair<int,int> player_coords = bus_->return_coordinates();
    for(unsigned int i = 0; i<list_of_pedestrians_.size(); ++i){
        if(list_of_pedestrians_.at(i)->return_coordinates() == player_coords){
            pedestrians.push_back(i);
        }
    }
    std::sort(pedestrians.begin(), pedestrians.end(), std::greater<unsigned int>());
    for(unsigned int i : pedestrians){
        scene_->removeItem(list_of_pedestrians_.at(i)->return_self());
        delete list_of_pedestrians_.at(i);
        list_of_pedestrians_.erase(list_of_pedestrians_.begin() + i);

    }
}

void MainWindow::create_game()
{
    read_coordinates(1);
    spawn_pedestrians(5);
    player_ = scene_->addRect(0,0,10,10);
    player_->setPos(40, 40);
    bus_ = new PlayerBus(player_, legal_coordinates_);
    player_->setBrush(Qt::blue);
}



void MainWindow::on_downButton_clicked()
{
    if(bus_->can_move(DOWN)) {
        bus_->move(DOWN);
        check_pedestrian_collision();
        ui->ylabel->setText("Y = " + QString::number(player_->y()));
    }
}

void MainWindow::on_leftButton_clicked()
{
    if(bus_->can_move(LEFT)) {
        bus_->move(LEFT);
        check_pedestrian_collision();
        ui->xlabel->setText("X = " + QString::number(player_->x()));
    }
}

void MainWindow::on_rightButton_clicked()
{
    if(bus_->can_move(RIGHT)) {
        bus_->move(RIGHT);
        check_pedestrian_collision();
        ui->xlabel->setText("X = " + QString::number(player_->x()));
    }
}

void MainWindow::on_upButton_clicked()
{
    if(bus_->can_move(UP)) {
        bus_->move(UP);
        check_pedestrian_collision();
        ui->ylabel->setText("Y = " + QString::number(player_->y()));
    }
}

void MainWindow::spawn_pedestrians(int amount)
{
    srand(time(0));
    int seed;
    for(auto const& x : *legal_coordinates_) {
        for(int y : x.second){

            seed = 1 + (rand() % 100);
            if (seed <= amount){
                QGraphicsRectItem* pedestrian_object = scene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::red);
                Pedestrian* pedestrian = new Pedestrian(pedestrian_object, legal_coordinates_, YES);
                list_of_pedestrians_.push_back(pedestrian);
            } else if (seed <= ((3*amount)/2)){
                QGraphicsRectItem* pedestrian_object = scene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::green);
                Pedestrian* pedestrian = new Pedestrian(pedestrian_object, legal_coordinates_, NO);
                list_of_pedestrians_.push_back(pedestrian);
            }
        }
    }

}

