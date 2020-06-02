#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "Algebra-polynom/Polynom/Polynom.h"
#include "Algebra-polynom/Polynom/GaloisField.h"
#include "Algebra-polynom/utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_makeFieldButton_clicked();
    void on_primeBox_valueChanged();
    void on_powerBox_valueChanged();
    void on_allirrPol_clicked();

    void on_listIP_currentRowChanged(int currentRow);
    void on_Calculate_clicked();
    void on_operations_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    GaloisField Field;
    std::vector<Polynom> IP;
    bool fieldCreated = false;
    bool canCerateField = true;
    void addIrrPolList();
    void cleanerTab();
    void addNewLine(QString text);
    void showB(bool show);
    void showN(bool show);
    void showX(bool show);
};
#endif // MAINWINDOW_H
