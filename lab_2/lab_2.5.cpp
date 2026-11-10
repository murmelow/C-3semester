#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    operationGroup(new QButtonGroup(this)),
    currentOperation(Add)
{
    ui->setupUi(this);

    this->setStyleSheet(R"(
    QMainWindow {
        background-color: #F2F4F7;
    }

    QWidget {
        background-color: #F2F4F7;
        color: #202124;
    }
)");
    // Убираем стрелки у числовых полей
    ui->spinSize->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinScalar->setButtonSymbols(QAbstractSpinBox::NoButtons);
    // Скрываем индексацию строк и столбцов матриц
    ui->tableA->horizontalHeader()->setVisible(false);
    ui->tableA->verticalHeader()->setVisible(false);

    ui->tableB->horizontalHeader()->setVisible(false);
    ui->tableB->verticalHeader()->setVisible(false);

    ui->tableResult->horizontalHeader()->setVisible(false);
    ui->tableResult->verticalHeader()->setVisible(false);
    // Оформление кнопок операций
    QString operationStyle = R"(
    QPushButton {
        background-color: #30343a;
        color: #eeeeee;
        border: 1px solid #50565f;
        border-radius: 5px;
        padding: 8px;
        font-size: 14px;
    }

    QPushButton:hover {
        background-color: #414852;
        border: 1px solid #718096;
    }

    QPushButton:checked {
        background-color: #1769aa;
        color: white;
        border: 2px solid #45aaff;
        font-weight: bold;
    }

    QPushButton:pressed {
        background-color: #12558c;
    }
    )";

    ui->buttonAdd->setStyleSheet(operationStyle);
    ui->buttonSubtract->setStyleSheet(operationStyle);
    ui->buttonMultiply->setStyleSheet(operationStyle);
    ui->buttonScalarA->setStyleSheet(operationStyle);
    ui->buttonScalarB->setStyleSheet(operationStyle);
    operationGroup->addButton(ui->buttonAdd, Add);
    operationGroup->addButton(ui->buttonSubtract, Subtract);
    operationGroup->addButton(ui->buttonMultiply, Multiply);
    operationGroup->addButton(ui->buttonScalarA, ScalarA);
    operationGroup->addButton(ui->buttonScalarB, ScalarB);

    operationGroup->setExclusive(true);

    ui->buttonAdd->setCheckable(true);
    ui->buttonSubtract->setCheckable(true);
    ui->buttonMultiply->setCheckable(true);
    ui->buttonScalarA->setCheckable(true);
    ui->buttonScalarB->setCheckable(true);

    ui->buttonAdd->setChecked(true);

    connect(operationGroup, &QButtonGroup::idClicked,
            this, [this](int id) {
                currentOperation = static_cast<Operation>(id);
            });

    connect(ui->spinSize,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updateMatrixSize);

    connect(ui->buttonEquals, &QPushButton::clicked,
            this, &MainWindow::calculate);

    initializeTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTables()
{
    int size = ui->spinSize->value();

    initializeMatrix(ui->tableA, size);
    initializeMatrix(ui->tableB, size);
    initializeMatrix(ui->tableResult, size);

    ui->tableResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::initializeMatrix(QTableWidget *table, int size)
{
    table->clear();
    table->setRowCount(size);
    table->setColumnCount(size);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("0");

            if (j < i) {
                setCellStyle(item, true);
            }

            table->setItem(i, j, item);
        }
    }
}

void MainWindow::setCellStyle(QTableWidgetItem *item, bool upperTriangle)
{
    if (upperTriangle) {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setBackground(QColor(45, 48, 53));
        item->setForeground(QColor(110, 110, 110));
    }
}

void MainWindow::updateMatrixSize(int size)
{
    initializeMatrix(ui->tableA, size);
    initializeMatrix(ui->tableB, size);
    initializeMatrix(ui->tableResult, size);
}

TMatrix MainWindow::readMatrix(QTableWidget *table)
{
    int size = table->rowCount();
    TMatrix matrix(size);

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            QTableWidgetItem *item = table->item(i, j);

            if (item) {
                bool ok;
                int value = item->text().toInt(&ok);

                if (!ok) {
                    throw std::invalid_argument(
                        "В таблице должны быть только целые числа"
                        );
                }

                matrix[i][j] = value;
            }
        }
    }

    return matrix;
}

void MainWindow::displayMatrix(QTableWidget *table, TMatrix matrix)
{
    int size = ui->spinSize->value();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QTableWidgetItem *item = table->item(i, j);

            if (!item) {
                item = new QTableWidgetItem();
                table->setItem(i, j, item);
            }

            if (j < i) {
                item->setText("");
                setCellStyle(item, true);
            } else {
                item->setText(QString::number(matrix[i][j]));
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                item->setBackground(QColor(32, 35, 40));
                item->setForeground(QColor(238, 238, 238));
            }
        }
    }
}

void MainWindow::calculate()
{
    try {
        matrixA = readMatrix(ui->tableA);
        matrixB = readMatrix(ui->tableB);

        int scalar = ui->spinScalar->value();
        TMatrix result(ui->spinSize->value());

        switch (currentOperation) {
        case Add:
            result = matrixA + matrixB;
            break;

        case Subtract:
            result = matrixA - matrixB;
            break;

        case Multiply:
            result = matrixA * matrixB;
            break;

        case ScalarA:
            result = matrixA * scalar;
            break;

        case ScalarB:
            result = matrixB * scalar;
            break;
        }

        displayMatrix(ui->tableResult, result);
    }
    catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
    catch (const char *error) {
        QMessageBox::critical(this, "Ошибка", error);
    }
}