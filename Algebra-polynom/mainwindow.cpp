#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent>

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

/* Threading */
void MainWindow::onCalculationsBegin() {
    ui->makeFieldButton->setEnabled(false);
    ui->Calculate->setEnabled(false);
    ui->allirrPol->setEnabled(false);
}

void MainWindow::onCalculationsEnd() {
    ui->makeFieldButton->setEnabled(true);
    ui->Calculate->setEnabled(true);
    ui->allirrPol->setEnabled(fieldCreated);
}

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
void MainWindow::addIrrPolList()
{
    onCalculationsBegin();
    int count = ui->countIP->value();
    compHandler.run([this, count]() {
        IP = Field.getNIrreducible(count);
        std::cout << "(((((((" << count << ")))))))" << std::endl;
        return QVector<QString>{};

    }, [&](const QVector<QString>& output) { onIrrPolListFinished(output); },
       [&]() { this->onCalculationsEnd(); });
}

void MainWindow::onIrrPolListFinished(const QVector<QString>& output)
{
    ui->listIP->clear();
    int row=0;
    for (auto& ip : IP) {
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
        onCalculationsBegin();
        compHandler.run([&]() {

            fieldCreated = true;
            Field = GaloisField(ui->primeBox->value(),ui->powerBox->value());
            return QVector<QString>{};

        }, [&](const QVector<QString>& output) { onFieldCreationFinished(output); },
           [&]() { this->onCalculationsEnd(); });
    } else {
        fieldCreated = false;
        ui->wrongP->setVisible(true);
        ui->allirrPol->setEnabled(false);
        ui->tabWidget->findChild<QTabBar *>()->hide();
    }
}

void MainWindow::onFieldCreationFinished(const QVector<QString>& output)
{
    ui->showIR->setPlainText(polToQStr(Field.getIrreducible()));
    ui->allirrPol->setEnabled(true);
    ui->Calculate->setEnabled(true);
    ui->tabWidget->findChild<QTabBar *>()->show();
}

void MainWindow::printCalculationResult(const QVector<QString>& output)
{
    for (const QString& line : output)
        addNewLine(line);
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

void MainWindow::launchCalculation(const std::function<QVector<QString> ()>& func)
{
    onCalculationsBegin();
    compHandler.run(func,
            [this](const QVector<QString>& result) { this->printCalculationResult(result); },
            [this]() { this->onCalculationsEnd(); }
    );
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
        launchCalculation([this, A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("+");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.add(A,B)));
            result.push_back(" ");

            return result;
        });
        break;}
    case 1:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([this, A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("-");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.subtract(A,B)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 2:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([this, A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("*");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.multiply(A,B)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 3:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([this, A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("/");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.divide(A,B)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 4:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("/");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(A/B));
            result.push_back(" ");
            return result;
        });
        break;}
    case 5:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([A, B]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")");
            result.push_back("%");
            result.push_back("("+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(A%B));
            result.push_back(" ");
            return result;
        });
        break;}
    case 6:{
        Polynom B(Field.getPrime(), qStrtoStd(ui->pB->text()),'x');
        if (ui->modIrr->isChecked()) B = B%Field.getIrreducible();
        ui->pB->setText(polToQStr(B));
        launchCalculation([A, B]() {
            QVector<QString> result;
            result.push_back("НСД("+polToQStr(A)+",");
            result.push_back("         "+polToQStr(B)+")");
            result.push_back("===============================");
            result.push_back(polToQStr(A.gcd(B)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 7:{
        launchCalculation([this, A]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")^(-1)");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.getInverse(A)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 8:{
        launchCalculation([this, A]() {
            QVector<QString> result;
            result.push_back("("+polToQStr(A)+")'");
            result.push_back("===============================");
            result.push_back(polToQStr(Field.derivative(A)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 9:{
        long long x = ui->xBox->value();
        launchCalculation([A, x]() {
            QVector<QString> result;
            result.push_back("A("+QString::number(x)+") = "+QString::number(A.valueAtPoint(x)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 10:{
        addNewLine("Нормування A");
        A.normalization();
        ui->pA->setText(polToQStr(A));
        launchCalculation([A]() {
            QVector<QString> result;
            result.push_back(polToQStr(A));
            result.push_back(" ");
            return result;
        });
        break;}
    case 11:{
        addNewLine("Корені A");
        launchCalculation([A]() {
            QVector<QString> result;
            std::vector<Polynom> roots = A.findRoots();
            for(auto& root:roots){
                result.push_back(polToQStr(root));
            }
            result.push_back(" ");
            return result;
        });
        break;}
    case 12:{
        launchCalculation([A]() {
            QVector<QString> result;
            result.push_back("Кількість коренів A = "+QString::number(A.rootsNumber()));
            result.push_back(" ");
            return result;
        });
        break;}
    case 13:{
        long long n = ui->nBox->value();
        addNewLine("Круговий многочлен порядку "+QString::number(n));
        launchCalculation([this, A, n]() {
            QVector<QString> result;
            result.push_back(polToQStr(A.CyclotomicPolynomial(Field.getPrime(),n)));
            result.push_back(" ");
            return result;
        });
        break;}
    case 14:{
        long long n = ui->nBox->value();
        addNewLine("Розклад кругового многочлена на незвідні множники (Ri)");
        launchCalculation([A, n]() {
            QVector<QString> result;
            std::vector<Polynom> pols = A.factorizeCyclotomicRi(n);
            for(auto& pol:pols){
                result.push_back(polToQStr(pol));
            }
            result.push_back(" ");
            return result;
        });
        break;}
    case 15:{
        addNewLine("Розклад A на незвідні множники (Берлекемпа)");
        launchCalculation([A]() {
            QVector<QString> result;
            result.push_back(toQStr(A.berlekampAlgorithm()));
            result.push_back(" ");
            return result;
        });
        break;}
    case 16:{
        long long n = ui->nBox->value();
        addNewLine("Всі незвідні многочлени порядку "+QString::number(n));
        launchCalculation([this, A, n]() {
            QVector<QString> result;
            std::vector<Polynom> pols = A.allIrreduciblePolynomials(Field.getPrime(),n);
            for(auto& pol : pols){
                result.push_back(polToQStr(pol));
            }
            result.push_back(" ");
            return result;
        });
        break;}
    case 17:{
        launchCalculation([A]() {
            QVector<QString> result;
            (A.isIrreducible()) ? result.push_back("A незвідний") : result.push_back("A звідний");
            result.push_back(" ");
            return result;
        });
        break;}
    case 18:{ /**************************************************************************************************TODO**********/
        addNewLine("Порядок A = "+QString::number(0));
        addNewLine(" ");
        break;}
    default:
        break;
    }
}

