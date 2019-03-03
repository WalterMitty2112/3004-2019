#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewanimalwindow.h"
#include "ui_viewanimalwindow.h"
#include "addanimalwindow.h"
#include "ui_addanimalwindow.h"
#include "viewclientwindow.h"
#include "ui_viewclientwindow.h"
#include "addclientwindow.h"
#include "ui_addclientwindow.h"

#include "animal.h"
#include "client.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDirIterator>
#include <QtWidgets>
#include <string>
using namespace std;

/*
 * A struct to contain the animal class and its corresponding
 * file name where its information is stored.
 */
struct animalNode {
    Animal *storedAnimal;
    string animalFileName;
};

/*
 * A struct to contain the client class and its corresponding
 * file name where its information is stored.
 */
struct clientNode {
    Client *storedClient;
    string clientFileName;
};

animalNode *nodes = new animalNode[30];
int arrTracker = 0;

clientNode *nodes2 = new clientNode[30];
int arrTracker2 = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString storagePath = QDir::currentPath() + "/Animals/";

    //If project was executed for the first time, create a folder containing 5 animals from persistent storage in the build folder
    if (!QDir(storagePath).exists()) {
        QDir().mkdir("Animals");

        QFile::copy(":/memstorage/AnimalClient Files/Animal/A-Brian.txt", storagePath + "A-Brain.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Animal/A-Gary.txt", storagePath + "A-Gary.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Animal/A-Stitch.txt", storagePath + "A-Stitch.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Animal/A-Pikachu.txt", storagePath + "A-Pikachu.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Animal/Garfield.txt", storagePath + "Garfield.txt");
    }

    QString storagePath2 = QDir::currentPath() + "/Clients/";

    //If project was executed for the first time, create a folder containing 5 clients from persistent storage in the build folder
    if (!QDir(storagePath2).exists()) {
        QDir().mkdir("Clients");

        QFile::copy(":/memstorage/AnimalClient Files/Client/Andy.txt", storagePath2 + "Andy.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Client/Andrew.txt", storagePath2 + "Andrew.txt");
        QFile::copy(":/memstorage/AnimalClient Files/Client/Devon.txt", storagePath2 + "Devon.txt");
    }


    ui->setupUi(this);
    initAnimals();
    initClients();

    currentUser = "Staff";
    ui->label_3->setText("Current User: Staff");

    ui->staffButton->setDisabled(true);

    ui->clientButton->setDisabled(false);
    ui->scrollArea_3->setDisabled(false);
    ui->addAnimalButton->setDisabled(false);
    ui->addClientButton->setDisabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Loads all animals from storage into the program
 */
void MainWindow::initAnimals() {

    int i = 0; //Counter for how many animals were allocated for later accessing of current animals in the array

    //Deletes all the widgets (buttons containing the animal names) in the scrolling area layout
    ui->scrollArea_2->takeWidget();
   QLayoutItem* item;
    while ( ( item = ui->verticalLayout_2->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    //QDir dir(":/memstorage/AnimalClient Files/Animal/");
    QDir dir(QDir::currentPath() + "/Animals/");
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);
    foreach(QString filename, files) { //It generates a string list of the directory continaing all the text files, iterating through each of the files obtaining their filenames
        //QFile file(":/memstorage/AnimalClient Files/Animal/" + filename);
        QFile file(QDir::currentPath() + "/Animals/" + filename);

        if (file.open(QIODevice::ReadOnly)) {

            QTextStream in(&file);
            int count = 0; //Indicates what # the line is

            //Variables for constructing animal object with their traits
            QString name = "";
            int age = 0;
            string breed = "";
            string type = "";
            int weight = 0;
            bool hasFur = false;
            int climatePref = 0;
            bool claws = false;
            bool sheds = false;
            string gender = "";
            string colour = "";
            string favFood = "";
            int intell = 0;
            int aggro = 0;
            int courage = 0;
            int play = 0;
            int strength = 0;
            string specSkill = "";
            int kidFriendly = 0;
            int commSkill = 0;
            int houseTrained = 0;
            int trust = 0;
            int curiosity = 0;
            int furLength = 0;

            //Reads each line of the animal file and each line corresponds to each respective physical trait of the animal, plus sets it to it's corresponding variable
            while(!in.atEnd()) {
                if (count == 0)
                    name = in.readLine();
                else if (count == 1)
                    type = in.readLine().toStdString();
                else if (count == 2)
                    breed = in.readLine().toStdString();
                else if (count == 3)
                     gender = in.readLine().toStdString();
                else if (count == 4)
                    age = in.readLine().toInt();         
                else if (count == 5)
                      colour = in.readLine().toStdString();
                else if (count == 6)
                      weight = in.readLine().toInt();
                else if (count == 7)
                      climatePref = in.readLine().toInt();
                else if (count == 8) {
                          if (in.readLine() == 'Y')
                            claws = true;
                          else
                              claws = false;

                }
                else if (count == 9) {
                          if (in.readLine() == 'Y')
                            sheds = true;
                          else
                             sheds = false;
                }
                else if (count == 10) {
                    if (in.readLine() == 'Y')
                      hasFur = true;
                    else
                      hasFur = false;
                }
                else if (count == 11)
                    favFood = in.readLine().toStdString();
                else if (count == 12)
                    intell = in.readLine().toInt();
                else if (count == 13)
                    aggro = in.readLine().toInt();
                else if (count == 14)
                    courage = in.readLine().toInt();
                else if (count == 15)
                    play = in.readLine().toInt();
                else if (count == 16)
                    strength = in.readLine().toInt();
                else if (count == 17)
                    specSkill = in.readLine().toStdString();
                else if (count == 18)
                    kidFriendly = in.readLine().toInt();
                else if (count == 19)
                    commSkill = in.readLine().toInt();
                else if (count == 20)
                    houseTrained = in.readLine().toInt();
                else if (count == 21)
                    trust = in.readLine().toInt();
                else if (count == 22)
                    curiosity = in.readLine().toInt();
                else if (count == 23)
                    furLength = in.readLine().toInt();
                else
                    break;

                /*There is no readline calls for non-physical traits which are the other remaining lines. Therefore, this break statement is there in the else statement for the
                 * while loop to not infinitely loop */

                count++;
            }
            file.close();

            Animal *animal = new Animal(name.toStdString(), age, breed, type,
                                        weight, furLength, climatePref, claws, sheds, hasFur,
                                        gender, colour, favFood, intell, aggro, courage, play,
                                        strength, specSkill, kidFriendly, commSkill, houseTrained, curiosity, trust);

            nodes[i].storedAnimal = animal;
            nodes[i].animalFileName = filename.toStdString();

            QPushButton *button = new QPushButton(name, this);
            button->setStyleSheet("height: 25px");
            connect(button, SIGNAL(clicked()), this, SLOT(showAnimalProfile())); //Connect each button to view animal ui form
            ui->verticalLayout_2->addWidget(button); //Add button to the scrolling area layout

            i++;
            arrTracker = i;

        }
        else {
            QString str = "Could not open " + filename + "!";
            switch( QMessageBox::question(
                            this,
                            tr("ERROR"),
                            str,

                            QMessageBox::Ok,

                            QMessageBox::Ok ) )
                {
                    case QMessageBox::Ok:
                        break;
                    default:
                        break;
                }
        }

        ui->scrollArea_2->setWidget(ui->verticalLayoutWidget_2);
    }
}

/*
 * Loads all clients from storage into the program
 */
void MainWindow::initClients() {

    int i = 0; //Counter for how many clients were allocated for later accessing of current clients in the array

    //Deletes all the widgets (buttons containing the client names) in the scrolling area layout
    ui->scrollArea_3->takeWidget();
   QLayoutItem* item;
    while ( ( item = ui->verticalLayout_4->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    QDir dir(QDir::currentPath() + "/Clients/");
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);
    foreach(QString filename, files) { //It generates a string list of the directory continaing all the text files, iterating through each of the files obtaining their filenames
        QFile file(QDir::currentPath() + "/Clients/" + filename);

        if (file.open(QIODevice::ReadOnly)) {

            QTextStream in(&file);
            int count = 0; //Indicates what # the line is

            //Variables for constructing client object with their basic info
            QString name = "";
            int age = 0;
            string address = "";
            string pNum = "";
            string email = "";
            string gender = "";
            string climate = "";

            //Reads each line of the client file and each line corresponds to each respective basic info of the client, plus sets it to it's corresponding variable
            while(!in.atEnd()) {
                if (count == 0)
                    name = in.readLine();
                else if (count == 1)
                    age = in.readLine().toInt();
                else if (count == 2)
                    address = in.readLine().toStdString();
                else if (count == 3)
                    pNum = in.readLine().toStdString();
                else if (count == 4)
                    email = in.readLine().toStdString();
                else if (count == 5)
                     climate = in.readLine().toStdString();
                else if (count == 6)
                     gender = in.readLine().toStdString();

                else
                    break;

                /*There is no readline calls for preferences which are the other remaining lines. Therefore, this break statement is there in the else statement for the
                 * while loop to not infinitely loop */

                count++;
            }
            file.close();

            Client *client = new Client(name.toStdString(), age, gender, address, climate, pNum, email);

            nodes2[i].storedClient = client;
            nodes2[i].clientFileName = filename.toStdString();

            QPushButton *button = new QPushButton(name, this);
            button->setStyleSheet("height: 25px");
            connect(button, SIGNAL(clicked()), this, SLOT(showClientProfile())); //Connect each button to view client ui form
            ui->verticalLayout_4->addWidget(button); //Add button to the scrolling area layout

            i++;
            arrTracker2 = i;

        }
        else {
            QString str = "Could not open " + filename + "!";
            switch( QMessageBox::question(
                            this,
                            tr("ERROR"),
                            str,

                            QMessageBox::Ok,

                            QMessageBox::Ok ) )
                {
                    case QMessageBox::Ok:
                        break;
                    default:
                        break;
                }
        }

        ui->scrollArea_3->setWidget(ui->verticalLayoutWidget_4);
    }
}

/*
 * Refreshes the list of animals, to be used
 * in the case of additions and deletions.
 */
void MainWindow::refreshAnimals() {
    delete [] nodes;

    nodes = new animalNode[30];
    arrTracker = 0;

    initAnimals();
}

/*
 * Refreshes the list of clients, to be used
 * in the case of additions and deletions.
 */
void MainWindow::refreshClients() {
    delete [] nodes2;

    nodes2 = new clientNode[30];
    arrTracker2 = 0;

    initClients();
}

/*
 * Opens up a new window that is used to view a specific
 * animal's information.
 */
void MainWindow::showAnimalProfile() {

    for(int i = 0; i < arrTracker; i++) {

        if (((QPushButton*)sender())->text().toStdString() == nodes[i].storedAnimal->getName()) {
            ViewAnimalWindow viewAnim;

            Animal a = *(nodes[i].storedAnimal);
            viewAnim.fillProfileInfo(a);
            viewAnim.selectedFileName(QString::fromStdString(nodes[i].animalFileName));

            if (currentUser == "Client")
                viewAnim.disableDeleteButton();

            viewAnim.setModal(true);
            viewAnim.exec();

        }
    }
}

/*
 * Opens up a new window that is used to view a specific
 * client's information.
 */
void MainWindow::showClientProfile() {

    for(int i = 0; i < arrTracker2; i++) {

        if (((QPushButton*)sender())->text().toStdString() == nodes2[i].storedClient->getName()) {
            ViewClientWindow viewCln;

            Client c = *(nodes2[i].storedClient);
            viewCln.fillProfileInfo(c);
            viewCln.selectedFileName(QString::fromStdString(nodes2[i].clientFileName));

            viewCln.setModal(true);
            viewCln.exec();
        }
    }
}

/*
 * Opens up the addAnimalWIndow which will
 * be used to add animals to the list.
 */
void MainWindow::on_addAnimalButton_clicked()
{
    AddAnimalWIndow addAnim;
    addAnim.setModal(true);
    addAnim.exec();
}

/*
 * Opens up the addClientWindow which will
 * be used to add clients to the list.
 */
void MainWindow::on_addClientButton_clicked()
{
    AddClientWindow addCln;
    addCln.setModal(true);
    addCln.exec();
}

/*
 * Refreshes the list of animals.
 */
void MainWindow::on_refreshAnimalsButton_clicked()
{
    refreshAnimals();
}

/*
 * Refreshes the list of clients.
 */
void MainWindow::on_refreshClientsButton_clicked()
{
    refreshClients();
}

// Enables set user privelleges for being a client
void MainWindow::on_clientButton_clicked()
{
    currentUser = "Client";
    ui->label_3->setText("Current User: Client");

    ui->scrollArea_3->setDisabled(true); //Disabled viewing detailed info of animals
    ui->addAnimalButton->setDisabled(true);
    ui->addClientButton->setDisabled(true);
    ui->clientButton->setDisabled(true);

    ui->staffButton->setDisabled(false);

}

// Enables set user privelleges for being a staff
void MainWindow::on_staffButton_clicked()
{
    currentUser = "Staff";
    ui->label_3->setText("Current User: Staff");

    ui->staffButton->setDisabled(true);

    ui->clientButton->setDisabled(false);
    ui->scrollArea_3->setDisabled(false); //Enabled viewing detailed info of animals
    ui->addAnimalButton->setDisabled(false);
    ui->addClientButton->setDisabled(false);
}


