#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "TMatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup *operationGroup;

    enum Operation {
        Add,
        Subtract,
        Multiply,
        ScalarA,
        ScalarB
    };

    Operation currentOperation;

    TMatrix matrixA;
    TMatrix matrixB;

    void initializeTables();
    void initializeMatrix(QTableWidget *table, int size);
    void updateMatrixSize(int size);

    void setCellStyle(QTableWidgetItem *item, bool upperTriangle);

    TMatrix readMatrix(QTableWidget *table);

    void displayMatrix(QTableWidget *table, TMatrix matrix);

    void calculate();
};

#endif