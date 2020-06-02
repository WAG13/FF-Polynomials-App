#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wrongP->setVisible(false);
    (fieldCreated) ? ui->tab2->setVisible(true) : ui->tab2->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chooseIP_clicked()
{
    if (utils::isPrime(ui->primeBox->value())){
        ui->wrongP->setVisible(false);
        Field = GaloisField(ui->primeBox->value(),ui->powerBox->value());
        fieldCreated = true;
        addIrrPolList();

    } else {ui->wrongP->setVisible(true);}
}

void MainWindow::addIrrPolList(){
    std::vector<Polynom> IP = Field.getAllIrreducible();
    //make list
}

void MainWindow::on_makeFieldButton_clicked()
{
    (fieldCreated) ? ui->tab2->setVisible(true) : ui->tab2->setVisible(false);
}
