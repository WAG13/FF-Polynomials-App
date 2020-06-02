#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_makeFieldButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString toQStr(std::string str) {return QString::fromStdString(str);}
QString polToQStr(Polynom pol) {return QString::fromStdString(pol.show());}

void MainWindow::addIrrPolList(){

    std::vector<Polynom> IP = Field.getNIrreducible(ui->countIP->value());
    //make list
    ui->listIP->clear();

    int row=0;
    for (auto& ip : IP) {
        ip.show();
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(polToQStr(ip));
        ui->listIP->insertItem(row, newItem);
        row++;
    }

}

void MainWindow::on_allirrPol_clicked()
{
    if (canCerateField) addIrrPolList();
}

void MainWindow::on_makeFieldButton_clicked()
{
    if (canCerateField){
        Field = GaloisField(ui->primeBox->value(),ui->powerBox->value());
        ui->showIR->setPlainText(polToQStr(Field.getIrreducible()));
        ui->allirrPol->setEnabled(true);
    } else {
        fieldCreated = false;
        ui->wrongP->setVisible(true);
        ui->allirrPol->setEnabled(false);
    }

    (fieldCreated)
              ? ui->tabWidget->findChild<QTabBar *>()->show()
              : ui->tabWidget->findChild<QTabBar *>()->hide();
}

void MainWindow::on_primeBox_valueChanged(int arg1)
{
    ui->listIP->clear();
    ui->showIR->clear();
    ui->allirrPol->setEnabled(false);
    if (utils::isPrime(ui->primeBox->value())){
        canCerateField = true;
        ui->wrongP->setVisible(false);
    } else {
        canCerateField = false;
        ui->wrongP->setVisible(true);
    }
}

void MainWindow::on_powerBox_valueChanged(int arg1)
{
    ui->listIP->clear();
    ui->showIR->clear();
    ui->allirrPol->setEnabled(false);
}


