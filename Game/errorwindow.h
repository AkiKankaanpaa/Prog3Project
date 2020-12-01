#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorWindow;
}

/**
 * @brief The ErrorWindow class: this class is used by the startupwindow and mainwindow to
 * deliver error messages to the user as popups
 */
class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ErrorWindow: Constructor
     * @param parent: startupwindow or mainwindow
     * @param errorstring: string to be presented to the user
     */
    explicit ErrorWindow(QWidget *parent = nullptr, QString errorstring = "");

    /**
      * @brief ~Errorwindow(): Destructor
      */
    ~ErrorWindow();

private slots:
    /**
     * @brief on_okButton_clicked: closes the window
     */
    void on_okButton_clicked();

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H
