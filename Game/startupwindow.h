#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QDialog>
#include "errorwindow.h"

namespace Ui {
class StartupWindow;
}

/**
 * @brief The StartupWindow class: This class is used to launch the create_game method within the
 * mainwindow as well as choose the name of the player as well as the difficulty
 */
class StartupWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief StartupWindow: Constructor
     * @param parent: mainwindow
     */
    explicit StartupWindow(QWidget *parent = nullptr);

    /**
      * @brief ~StartupWindow(): Destructor
      */
    ~StartupWindow();

signals:
    /**
     * @brief difficultySignal: connects to create_game in mainwindow
     * @param difficulty: difficulty to be given to create_game, user input
     * @param name: name to be given to create_game, user input
     */
    void difficultySignal(int difficulty, QString name);

private slots:
    /**
     * @brief on_startButton_clicked: emits difficultySignal and closes the startupwindow
     */
    void on_startButton_clicked();

    /**
     * @brief on_cancelButton_clicked: emits rejected() and closes both startupwindow as well as
     * mainwindow
     */
    void on_cancelButton_clicked();

private:
    Ui::StartupWindow *ui;
};

#endif // STARTUPWINDOW_H
