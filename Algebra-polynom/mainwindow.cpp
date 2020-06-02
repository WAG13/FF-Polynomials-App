#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_primeBox_valueChanged();
    showX(false);showN(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Converter */
QString toQStr(std::string str) {return QString::fromStdString(str);}
QString polToQStr(Polynom pol) {return QString::fromStdString(pol.show());}
std::string qStrtoStd (QString str) {return str.toLocal8Bit().constData();}
/* Cleaner */
void MainWindow::cleanerTab1(){
    fieldCreated = false;
    ui->listIP->clear();
    ui->showIR->clear();
    ui->allirrPol->setEnabled(false);
    ui->Calculate->setEnabled(false);
    ui->tabWidget->findChild<QTabBar *>()->hide();
}

/* IrrPolynoms List */
void MainWindow::addIrrPolList(){
    IP = Field.getNIrreducible(ui->countIP->value());
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

void MainWindow::on_listIP_currentRowChanged(int currentRow)
{
    if (currentRow > 0){
        Field.setIrreducible(IP[currentRow]);
        ui->showIR->setPlainText(polToQStr(Field.getIrreducible()));
    }
}

void MainWindow::on_allirrPol_clicked()
{
    if (canCerateField) addIrrPolList();
}

/* Making Field */
void MainWindow::on_makeFieldButton_clicked()
{
    if (canCerateField){
        fieldCreated = true;
        Field = GaloisField(ui->primeBox->value(),ui->powerBox->value());
        ui->showIR->setPlainText(polToQStr(Field.getIrreducible()));
        ui->allirrPol->setEnabled(true);
        ui->Calculate->setEnabled(true);
    } else {
        fieldCreated = false;
        ui->wrongP->setVisible(true);
        ui->allirrPol->setEnabled(false);
    }

    (fieldCreated)
              ? ui->tabWidget->findChild<QTabBar *>()->show()
              : ui->tabWidget->findChild<QTabBar *>()->hide();
}



void MainWindow::on_primeBox_valueChanged()
{
    cleanerTab1();
    if (utils::isPrime(ui->primeBox->value())){
        canCerateField = true;
        ui->wrongP->setVisible(false);
    } else {
        canCerateField = false;
        ui->wrongP->setVisible(true);
    }
}

void MainWindow::on_powerBox_valueChanged()
{
    cleanerTab1();
}


/* Operations */
void MainWindow::showB(bool show){
    if (show){
        ui->labelB->setVisible(true);
        ui->pB->setVisible(true);
    }else{
        ui->labelB->setVisible(false);
        ui->pB->setVisible(false);
    }
}

void MainWindow::showN(bool show){
    if (show){
        ui->nBox->setValue(1);
        ui->labelN->setText(toQStr("n ="));
        ui->labelN->setVisible(true);
        ui->nBox->setVisible(true);
    }else{
        ui->labelN->setVisible(false);
        ui->nBox->setVisible(false);
    }
}

void MainWindow::showX(bool show){
    if (show){
        ui->xBox->setValue(1);
        ui->labelX->setText(toQStr("x ="));
        ui->labelX->setVisible(true);
        ui->xBox->setVisible(true);
    }else{
        ui->labelX->setVisible(false);
        ui->xBox->setVisible(false);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    showB(false);
    showN(false);
    ((index > -1) && (index < 6))
            ? showB(true)
            : showB(false);
    (index == 8)
            ? showX(true)
            : showX(false);
    ((index == 12) || (index == 15))
            ? showN(true)
            : showN(false);
}
void MainWindow::addNewLine(QString text){
    ui->history->appendPlainText(text);
}
void MainWindow::on_Calculate_clicked()
{
    Polynom A(Field.getPrime(), qStrtoStd(ui->pA->text()),'x');
    Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
    long long x = ui->xBox->value();
    long long n = ui->nBox->value();
    switch (ui->operations->currentIndex()) {
    case 0:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        addNewLine("("+polToQStr(A)+")");
        addNewLine("+");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.add(A,B)));
        break;}
    default:
        break;
    }
}
