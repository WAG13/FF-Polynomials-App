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
void MainWindow::cleanerTab(){
    fieldCreated = false;
    ui->listIP->clear();
    ui->showIR->clear();
    ui->allirrPol->setEnabled(false);
    ui->Calculate->setEnabled(false);
    ui->tabWidget->findChild<QTabBar *>()->hide();
    ui->history->clear();
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
    if (currentRow >= 0){
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
    cleanerTab();
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
    cleanerTab();
}


/* Operations */
void MainWindow::showB(bool show){
    ui->labelB->setVisible(show);
    ui->pB->setVisible(show);
    if (!show)ui->pB->clear();
}

void MainWindow::showN(bool show){
    ui->nBox->setVisible(show);
    ui->labelN->setVisible(show);
    if (show)ui->nBox->setValue(1);
}

void MainWindow::showX(bool show){
    ui->xBox->setVisible(show);
    ui->labelX->setVisible(show);
    if (show)ui->xBox->setValue(1);
}

void MainWindow::on_operations_currentIndexChanged(int index){
    ((index > -1) && (index < 7))
            ? showB(true)
            : showB(false);
    (index == 9)
            ? showX(true)
            : showX(false);
    ((index == 13) || (index == 14) || (index == 16))
            ? showN(true)
            : showN(false);
}

void MainWindow::addNewLine(QString text){
    ui->history->appendPlainText(text);
}

void MainWindow::on_Calculate_clicked()
{
    Polynom A(Field.getPrime(), qStrtoStd(ui->pA->text()),'x');
    if (ui->modIrr->isChecked()) A = A%Field.getIrreducible();
    ui->pA->setText(polToQStr(A));

    switch (ui->operations->currentIndex()) {
    case 0:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("+");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.add(A,B)));
        addNewLine(" ");
        break;}
    case 1:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("-");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.subtract(A,B)));
        addNewLine(" ");
        break;}
    case 2:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("*");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.multiply(A,B)));
        addNewLine(" ");
        break;}
    case 3:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("/");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.divide(A,B)));
        addNewLine(" ");
        break;}
    case 4:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("/");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(A/B));
        addNewLine(" ");
        break;}
    case 5:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("("+polToQStr(A)+")");
        addNewLine("%");
        addNewLine("("+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(A%B));
        addNewLine(" ");
        break;}
    case 6:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        addNewLine("НСД("+polToQStr(A)+",");
        addNewLine("         "+polToQStr(B)+")");
        addNewLine("===============================");
        addNewLine(polToQStr(A.gcd(B)));
        addNewLine(" ");
        break;}
    case 7:{
        addNewLine("("+polToQStr(A)+")^(-1)");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.getInverse(A)));
        addNewLine(" ");
        break;}
    case 8:{
        addNewLine("("+polToQStr(A)+")'");
        addNewLine("===============================");
        addNewLine(polToQStr(Field.derivative(A)));
        addNewLine(" ");
        break;}
    case 9:{
        long long x = ui->xBox->value();
        addNewLine("A("+QString::number(x)+") = "+QString::number(A.valueAtPoint(x)));
        addNewLine(" ");
        break;}
    case 10:{
        addNewLine("Нормування A");
        A.normalization();
        ui->pA->setText(polToQStr(A));
        addNewLine(polToQStr(A));
        addNewLine(" ");
        break;}
    case 11:{
        addNewLine("Корені A");
        std::vector<Polynom> roots = A.findRoots();
        for(auto& root:roots){
            addNewLine(polToQStr(root));
        }
        addNewLine(" ");
        break;}
    case 12:{
        addNewLine("Кількість коренів A = "+QString::number(A.rootsNumber()));
        addNewLine(" ");
        break;}
    case 13:{
        long long n = ui->nBox->value();
        addNewLine("Круговий многочлен порядку "+QString::number(n));
        addNewLine(polToQStr(A.CyclotomicPolynomial(Field.getPrime(),n)));
        addNewLine(" ");
        break;}
    case 14:{
        long long n = ui->nBox->value();
        addNewLine("Розклад кругового многочлена на незвідні множники (Ri)");
        std::vector<Polynom> pols = A.factorizeCyclotomicRi(n);
        for(auto& pol:pols){
            addNewLine(polToQStr(pol));
        }
        addNewLine(" ");
        break;}
    case 15:{
        addNewLine("Розклад A на незвідні множники (Берлекемпа)");
        addNewLine(toQStr(A.berlekampAlgorithm()));
        addNewLine(" ");
        break;}
    case 16:{
        long long n = ui->nBox->value();
        addNewLine("Всі незвідні многочлени порядку "+QString::number(n));
        std::vector<Polynom> pols = A.allIrreduciblePolynomials(Field.getPrime(),n);
        for(auto& pol:pols){
            addNewLine(polToQStr(pol));
        }
        addNewLine(" ");
        break;}
    case 17:{
        (A.isIrreducible()) ? addNewLine("A незвідний") : addNewLine("A не незвідний");
        addNewLine(" ");
        break;}
    case 18:{ /**************************************************************************************************TODO**********/
        addNewLine("Порядок A = "+QString::number(0));
        addNewLine(" ");
        break;}
    default:
        break;
    }
}

