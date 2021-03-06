#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "animal.h"
#include "client.h"
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void initAnimals();
    void initClients();
    void refreshAnimals();
    void refreshClients();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showAnimalProfile();

    void showClientProfile();

    void onlyViewLoggedInClient(string name);

    void on_addAnimalButton_clicked();

    void on_refreshAnimalsButton_clicked();

    void on_refreshClientsButton_clicked();

    void on_staffButton_clicked();

    void on_addClientButton_clicked();

    void on_clientDropDown_activated(int index);

    void on_runACMButton_clicked();

private:
    Ui::MainWindow *ui;
    FileManager fm;
    string currentUser;
};

#endif // MAINWINDOW_H
