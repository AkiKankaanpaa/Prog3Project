#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    legal_coordinates_(new std::map<int, std::vector<int>>),
    ui(new Ui::MainWindow),
    bus_(nullptr),
    current_tick_(0),
    ragetime_(150),
    game_running_(false)

{
    ui->setupUi(this);
    QPixmap pix(":/images/kartta.png");

    ragescene_ = new QGraphicsScene(this);
    ui->rageMeter->setScene(ragescene_);
    ragescene_->setSceneRect(940,10,40,150);
    ui->rageMeter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rageMeter->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_ = new QGraphicsScene(this);
    ui->MapView->setScene(scene_);
    scene_->setSceneRect(0,0,800,800);
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
    std::vector<unsigned int> pedestrians = {};
    std::pair<int,int> to_be_player_coords = determine_bus_movement();
    for(unsigned int i = 0; i<list_of_pedestrians_.size(); ++i){
        if(list_of_pedestrians_.at(i)->return_coordinates() == to_be_player_coords){
            pedestrians.push_back(i);
        }
    }
    std::sort(pedestrians.begin(), pedestrians.end(), std::greater<unsigned int>());
    if (pedestrians.size() > 0) {
        for(unsigned int i : pedestrians){

            enum::mask was_worn = list_of_pedestrians_.at(i)->return_maskstatus();

            int points = ui->lcdPoints->intValue();

            if (was_worn == NO) {
                ui->lcdPoints->display(points + 100);
                gamestats_->change_points(100);
                increase_rage(30);
            } else {
                ui->lcdPoints->display(points - 50);
                gamestats_->change_points(-50);
                reduce_rage(10);
            }
            scene_->removeItem(list_of_pedestrians_.at(i)->return_self());
            delete list_of_pedestrians_.at(i);
            list_of_pedestrians_.erase(list_of_pedestrians_.begin() + i);
        }
    } else {
        reduce_rage(1);
    }
}

std::pair<int, int> MainWindow::determine_bus_movement()
{
    std::pair<int, int> current_coordinates = bus_->return_coordinates();
    direction dir = bus_->return_direction();

    if(dir == RIGHT){
        current_coordinates.first += 10;
        return current_coordinates;
    } else if(dir == LEFT) {
        current_coordinates.first -= 10;
        return current_coordinates;
    } else if(dir == UP){
        current_coordinates.second -= 10;
        return current_coordinates;
    } else {
        current_coordinates.second += 10;
        return current_coordinates;
    }
}

void MainWindow::reduce_rage(int amount)
{
    ragetime_ -= amount;
    ragemeter_->setPos(940,ragemeter_->y()+amount);
}

void MainWindow::increase_rage(int amount)
{
    if ((ragetime_ + amount) > 150) {
        ragetime_ = 150;
        ragemeter_->setPos(940,10);
    }
    else {
        ragetime_+= amount;
        ragemeter_->setPos(940,ragemeter_->y()-amount);
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

    tick_timer_ = new QTimer(this);
    connect(tick_timer_, SIGNAL(timeout()), this, SLOT(tick_handler()));

    tick_timer_->start(15);

    ragemeter_ = ragescene_->addRect(0,0,40,150);
    ragemeter_->setPos(940,10);
    ragemeter_->setBrush(Qt::red);

    game_running_ = true;

    gamestats_ = new Gamestatistics(ITYD);
}

void MainWindow::tick_handler()
{
    direction dir = bus_->return_direction();
    bus_->move(dir, 1);

    ++current_tick_;

    if (current_tick_ == 10) {
        current_tick_ = 0;
        bus_->set_direction(queued_direction);
        dir = bus_->return_direction();

        if (bus_->can_move(dir)) {
            check_pedestrian_collision();
        } else {
            end_game();
        }
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
                Pedestrian* pedestrian = new Pedestrian(pedestrian_object, legal_coordinates_, NO);
                list_of_pedestrians_.push_back(pedestrian);
            } else if (seed <= ((3*amount)/2)){
                QGraphicsRectItem* pedestrian_object = scene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::green);
                Pedestrian* pedestrian = new Pedestrian(pedestrian_object, legal_coordinates_, YES);
                list_of_pedestrians_.push_back(pedestrian);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    direction current_direction = bus_->return_direction();
    switch (event->key())  {
        case Qt::Key_W:
            if (current_direction != DOWN) {
                queued_direction = UP;
            }
            break;

        case Qt::Key_A:
            if (current_direction != RIGHT) {
                queued_direction = LEFT;
            }
            break;

        case Qt::Key_S:
            if (current_direction != UP) {
                queued_direction = DOWN;
            }
            break;

        case Qt::Key_D:
            if (current_direction != LEFT) {
                queued_direction = RIGHT;
            }
            break;

        default:
            ;
    }
}

void MainWindow::end_game()
{
    game_running_ = false;
    tick_timer_->stop();
}

