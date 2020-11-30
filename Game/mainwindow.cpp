#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    legal_coordinates_(new std::map<int, std::vector<int>>),
    ui(new Ui::MainWindow),
    gameimages_(new std::map<gamestate, QPixmap>),
    bus_(nullptr),
    tick_timer_(new QTimer(this)),
    current_tick_(0),
    queued_direction_(RIGHT),
    gamestats_(new Gamestatistics(0)),
    game_running_(false)

{
    ui->setupUi(this);
    QPixmap infolabel(":/images/infolabel.png");
    ui->infoLabel->setPixmap(infolabel);

    QPixmap running(":/images/map.png");
    QPixmap crash(":/images/crash.png");
    QPixmap rage(":/images/rage.png");
    QPixmap victory(":/images/victory.png");
    gameimages_->insert({RUNNING, running});
    gameimages_->insert({CRASH, crash});
    gameimages_->insert({RAGE, rage});
    gameimages_->insert({VICTORY, victory});

    ragescene_ = new QGraphicsScene(this);
    ui->rageMeter->setScene(ragescene_);
    ragescene_->setSceneRect(940,10,40,150);
    ui->rageMeter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rageMeter->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ragemeter_ = ragescene_->addRect(0,0,40,150);
    ragemeter_->setPos(940,10);
    ragemeter_->setBrush(Qt::red);

    gamescene_ = new QGraphicsScene(this);
    ui->MapView->setScene(gamescene_);
    gamescene_->setSceneRect(0,0,800,800);
    ui->MapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gamescene_->addPixmap(gameimages_->at(RUNNING));

    startup_ = new StartupWindow(this);
    startup_->show();
    connect(startup_, &StartupWindow::rejected, this, &MainWindow::close);
    connect(startup_, &StartupWindow::difficulty_signal, this, &MainWindow::create_game);

    connect(tick_timer_, SIGNAL(timeout()), this, SLOT(tick_handler()));
}

MainWindow::~MainWindow()
{
    delete bus_;
    delete ui;
    delete legal_coordinates_;
    delete gamestats_;
}

void MainWindow::read_coordinates()
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

void MainWindow::create_game(int chosen_difficulty)
{
    game_running_ = true;
    read_coordinates();

    QGraphicsRectItem* playertoken = gamescene_->addRect(0,0,10,10);
    playertoken->setPos(40, 40);
    bus_ = new PlayerBus(playertoken, legal_coordinates_);
    playertoken->setBrush(Qt::blue);

    set_difficulty_settings(chosen_difficulty);
}

void MainWindow::set_difficulty_settings(int chosen_difficulty)
{
    switch (chosen_difficulty)  {
        case EXTREMELY_EASY:
            spawn_pedestrians(10);
            tick_timer_->start(25);
            break;

        case EASY:
            spawn_pedestrians(8);
            tick_timer_->start(20);
            break;

        case NOT_EASY:
            spawn_pedestrians(6);
            tick_timer_->start(15);
            break;

        case UNEASY:
            spawn_pedestrians(4);
            tick_timer_->start(10);
            break;

        default:
            ;
    }
}

void MainWindow::check_pedestrian_collision()
{
    std::vector<unsigned int> pedestrians = {};
    std::pair<int,int> to_be_player_coords = bus_->determine_movement();
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
                update_rage(30);

                gamestats_->maskrefuser_died();

            } else {
                ui->lcdPoints->display(points - 50);
                gamestats_->change_points(-50);
                update_rage(-10);

                gamestats_->morePassengers(1);
            }

            gamescene_->removeItem(list_of_pedestrians_.at(i)->return_self());
            delete list_of_pedestrians_.at(i)->return_self();
            delete list_of_pedestrians_.at(i);
            list_of_pedestrians_.erase(list_of_pedestrians_.begin() + i);
        }
    } else {
        update_rage(-5);
        if (gamestats_->return_rage() <= 0) {
            end_game(RAGE);
        }
    }
}

void MainWindow::update_rage(int amount)
{
    if ((gamestats_->return_rage() + amount) > 150) {
        gamestats_->change_rage(150 - gamestats_->return_rage());
        ragemeter_->setPos(940,10);
    }
    else {
        gamestats_->change_rage(amount);
        ragemeter_->setPos(940,ragemeter_->y()-amount);
    }
}

void MainWindow::tick_handler()
{
    direction dir = bus_->return_direction();
    bus_->move(dir, 1);

    ++current_tick_;

    if (current_tick_ == 10) {
        current_tick_ = 0;
        bus_->set_direction(queued_direction_);
        dir = bus_->return_direction();

        if (bus_->can_move(dir)) {
            check_pedestrian_collision();
        } else {
            end_game(CRASH);
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
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::red);
                Pedestrian* pedestrian = new Pedestrian(pedestrian_object, legal_coordinates_, NO);
                list_of_pedestrians_.push_back(pedestrian);

            } else if (seed <= ((3*amount)/2)){
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
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
    if(game_running_){
        direction current_direction = bus_->return_direction();
        switch (event->key())  {
            case Qt::Key_W:
                if (current_direction != DOWN) {
                    queued_direction_ = UP;
                }
                break;

            case Qt::Key_A:
                if (current_direction != RIGHT) {
                    queued_direction_ = LEFT;
                }
                break;

            case Qt::Key_S:
                if (current_direction != UP) {
                    queued_direction_ = DOWN;
                }
                break;

            case Qt::Key_D:
                if (current_direction != LEFT) {
                    queued_direction_ = RIGHT;
                }
                break;

            default:
                ;
        }
    }
}

void MainWindow::end_game(gamestate condition)
{
    gamescene_->addPixmap(gameimages_->at(RUNNING));
    game_running_ = false;
    tick_timer_->stop();
    gamescene_->addPixmap(gameimages_->at(condition));
    int size = list_of_pedestrians_.size() - 1;
    for(int i = size; i >= 0; i--){
        gamescene_->removeItem(list_of_pedestrians_.at(i)->return_self());
        delete list_of_pedestrians_.at(i)->return_self();
        delete list_of_pedestrians_.at(i);
        list_of_pedestrians_.erase(list_of_pedestrians_.begin() + i);
    }
}

