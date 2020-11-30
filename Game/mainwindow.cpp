#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    legal_coordinates_(new std::map<int, std::vector<int>>),
    ui(new Ui::MainWindow),
    gameimages_(new std::map<gamestate, QPixmap>),
    player_(nullptr),
    tick_timer_(new QTimer(this)),
    current_tick_(0),
    queued_direction_(RIGHT),
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
    connect(startup_, &StartupWindow::difficultySignal, this, &MainWindow::createGame);
    gamestats_ = new Gamestatistics();

    connect(tick_timer_, SIGNAL(timeout()), this, SLOT(tickHandler()));
}

MainWindow::~MainWindow()
{
    delete player_;
    delete ui;
    delete legal_coordinates_;
    delete gamestats_;
    delete gameimages_;
}

void MainWindow::readCoordinates()
{
    QFile file(":/txtfiles/tamperecoordinates.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ;
    }
    else
    {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            std::string x_line = line.toStdString();
            insertCoordinates(x_line);
        }
    }
}

void MainWindow::insertCoordinates(std::string x_line)
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

void MainWindow::insertHighscores(std::string x_line)
{
    std::string x = x_line.substr(0, x_line.find(":"));
    x_line.erase(x_line.begin(), x_line.begin()+x.size()+1);
    auto pair = std::make_pair(x, stoi(x_line));
}

void MainWindow::createGame(int chosen_difficulty)
{
    gamescene_->addPixmap(gameimages_->at(RUNNING));

    difficulty diff = (difficulty)chosen_difficulty;

    game_running_ = true;

    if(gamestats_->returnTotalNysses() == 0){
        readCoordinates();
        QGraphicsRectItem* playertoken = gamescene_->addRect(0,0,10,10);
        playertoken->setPos(40, 40);
        player_ = new Bus(playertoken, legal_coordinates_);
        playertoken->setBrush(Qt::black);
        ui->totalGameValue->setText("0");
        ui->lostGameValue->setText("0");
        ui->wonGameValue->setText("0");
        ui->totalPointValue->setText("0");
    }
    if(gamestats_->returnTotalNysses() > 0){
        delete player_;
        QGraphicsRectItem* playertoken = gamescene_->addRect(0,0,10,10);
        playertoken->setPos(40, 40);
        player_ = new Bus(playertoken, legal_coordinates_);
        queued_direction_ = RIGHT;
        player_->returnSelf()->setPos(40,40);
        player_->returnSelf()->setBrush(Qt::black);
    }
    gamestats_->changePoints(-gamestats_->returnPoints());

    setDifficultySettings(diff);

    ui->pedestrianValue->setText(QString::number(gamestats_->returnRemainingPedestrians()));
    ui->passengerValue->setText("0");
    ui->lcdPoints->display(0);
}

void MainWindow::setDifficultySettings(difficulty chosen_difficulty)
{
    int total_pedestrians = spawnGamepieces(chosen_difficulty);
    gamestats_->resetRemainingPedestrians(total_pedestrians);
    gamestats_->setGameDifficulty(chosen_difficulty);
    switch (chosen_difficulty)  {
        case EXTREMELY_EASY: {
            tick_timer_->start(25);
            break;
        }
        case EASY: {
            tick_timer_->start(20);
            break;
        }
        case NOT_EASY: {
            tick_timer_->start(17);
            break;
        }
        case UNEASY:{
            tick_timer_->start(14);
            break;
        }
    }
}

void MainWindow::checkPedestrianCollision()
{
    std::vector<unsigned int> gamepieces = {};
    std::pair<int,int> next_position = player_->determineMovement();
    int ragemeter_y;

    for(unsigned int i = 0; i<list_of_gamepieces_.size(); ++i){
        if(list_of_gamepieces_.at(i)->returnCoordinates() == next_position){
            gamepieces.push_back(i);
        }
    }

    std::sort(gamepieces.begin(), gamepieces.end(), std::greater<unsigned int>());

    if (gamepieces.size() > 0) {
        for(unsigned int i : gamepieces){

            enum::piecetype current_piecetype = list_of_gamepieces_.at(i)->returnPiecetype();

            int points = ui->lcdPoints->intValue();

            switch(current_piecetype) {
                case MASKLESS: {
                    ui->lcdPoints->display(points + 100);
                    gamestats_->changePoints(100);

                    gamestats_->changeTotalPoints(100);
                    ui->totalPointValue->setText(QString::number(gamestats_->returnTotalPoints()));

                    ragemeter_y = gamestats_->changeRage(200);
                    ragemeter_->setPos(940, ragemeter_y);

                    gamestats_->removePedestrian();

                    if (gamestats_->returnPassengers() > 0) {
                        gamestats_->doesDiseaseSpread();
                    }

                    ui->pedestrianValue
                            ->setText(QString::number(gamestats_->returnRemainingPedestrians()));

                    ui->passengerValue
                            ->setText(QString::number(gamestats_->returnPassengers()));

                    break;
                }
                case MASKED: {
                    ragemeter_y = gamestats_->changeRage(-50);
                    ragemeter_->setPos(940, ragemeter_y);

                    gamestats_->removePedestrian();
                    gamestats_->morePassengers(1);

                    ui->pedestrianValue
                            ->setText(QString::number(gamestats_->returnRemainingPedestrians()));

                    ui->passengerValue
                            ->setText(QString::number(gamestats_->returnPassengers()));

                    if (gamestats_->returnRemainingPedestrians() == 0) {
                        endGame(VICTORY);
                    }
                    break;
                }
                case POLICE: {
                    ui->lcdPoints->display(points - 250);
                    gamestats_->changePoints(-250);

                    gamestats_->changeTotalPoints(-250);
                    ui->totalPointValue->setText(QString::number(gamestats_->returnTotalPoints()));

                    ragemeter_y = gamestats_->changeRage(300);
                    ragemeter_->setPos(940, ragemeter_y);

                    break;
                }
                case POWERUP: {
                    ui->lcdPoints->display(points + 500);
                    gamestats_->changePoints(500);
                    gamestats_->changeTotalPoints(500);
                    ui->totalPointValue->setText(QString::number(gamestats_->returnTotalPoints()));

                    break;
                }
            }
            if (game_running_) {
                gamescene_->removeItem(list_of_gamepieces_.at(i)->returnSelf());
                delete list_of_gamepieces_.at(i)->returnSelf();
                delete list_of_gamepieces_.at(i);
                list_of_gamepieces_.erase(list_of_gamepieces_.begin() + i);
            }
        }
    }
}

void MainWindow::tickHandler()
{
    direction dir = player_->returnDirection();
    player_->move(dir, 1);

    int ragemeter_y = gamestats_->rageDecay();
    ragemeter_->setPos(940, ragemeter_y);

    if (gamestats_->returnRage() <= 0) {
       endGame(RAGE);
    }

    ++current_tick_;

    if (current_tick_ == 10) {
        current_tick_ = 0;

        if (player_->canMove(queued_direction_)) {
            player_->setDirection(queued_direction_);
            checkPedestrianCollision();
        } else {
            endGame(CRASH);
        }
    }
}

int MainWindow::spawnGamepieces(difficulty diff)
{
    int powerup_th, police_th, maskless_th, mask_th;
    
    switch (diff)  {
        case EXTREMELY_EASY:{
            powerup_th = 2;
            police_th = 4;
            maskless_th = 10;
            mask_th = 15;
            break;
        }

        case EASY: {
            powerup_th = 1;
            police_th = 3;
            maskless_th = 8;
            mask_th = 13;
            break;
        }
        case NOT_EASY: {
            powerup_th = 1;
            police_th = 2;
            maskless_th = 7;
            mask_th = 12;
            break;
        }
        case UNEASY: {
            powerup_th = 10;
            police_th = 10;
            maskless_th =10;
            mask_th =10;
            break;
        }
    }
    
    srand(time(0));
    int current_randint;
    int game_end_amount = 0;
    
    for(auto const& x : *legal_coordinates_) {
        
        for(int y : x.second){
            
            current_randint = 1 + (rand() % 100);

            if (current_randint <= powerup_th) {
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::yellow);
                Gamepiece* pedestrian = new Gamepiece(pedestrian_object, legal_coordinates_, POWERUP);
                list_of_gamepieces_.push_back(pedestrian);
            }
            else if (current_randint <= police_th) {
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::blue);
                Gamepiece* pedestrian = new Gamepiece(pedestrian_object, legal_coordinates_, POLICE);
                list_of_gamepieces_.push_back(pedestrian);
            }
            else if (current_randint <= maskless_th){
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::red);
                Gamepiece* pedestrian = new Gamepiece(pedestrian_object, legal_coordinates_, MASKLESS);
                list_of_gamepieces_.push_back(pedestrian);
                ++game_end_amount;

            } else if (current_randint <= mask_th){
                QGraphicsRectItem* pedestrian_object = gamescene_->addRect(0,0,10,10);
                pedestrian_object->setPos(x.first, y);
                pedestrian_object->setBrush(Qt::green);
                Gamepiece* pedestrian = new Gamepiece(pedestrian_object, legal_coordinates_, MASKED);
                list_of_gamepieces_.push_back(pedestrian);
                ++game_end_amount;
            }
        }
    }
    return game_end_amount;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(game_running_){
        direction current_direction = player_->returnDirection();
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
    } else if (!game_running_){
        switch (event->key()) {
            case Qt::Key_R:
                if(gamestats_->returnTotalNysses() > 0){
                    startup_->show();
                    gamestats_->changeRage(900);
                }
        default:
            ;
        }
    }
}

void MainWindow::endGame(gamestate condition)
{
    game_running_ = false;
    tick_timer_->stop();
    gamescene_->addPixmap(gameimages_->at(condition));

    gamestats_->newNysse();
    ui->totalGameValue->setText(QString::number(gamestats_->returnTotalNysses()));

    if (condition == VICTORY) {
        gamestats_->nysseLeft();
        ui->wonGameValue->setText(QString::number(gamestats_->returnLostNysses()));
        gamestats_->changePoints(gamestats_->returnPassengers() * 150);
    } else {
        gamestats_->nysseRemoved();
        ui->lostGameValue->setText(QString::number(gamestats_->returnRemovedNysses()));
        gamestats_->changePoints(gamestats_->returnPassengers() * -50);
        ui->totalPointValue->setText(QString::number(gamestats_->returnTotalPoints()));
    }

    for(int i = (list_of_gamepieces_.size() - 1); i >= 0; i--){
        gamescene_->removeItem(list_of_gamepieces_.at(i)->returnSelf());
        delete list_of_gamepieces_.at(i)->returnSelf();
        delete list_of_gamepieces_.at(i);
        list_of_gamepieces_.erase(list_of_gamepieces_.begin() + i);
    }
}
