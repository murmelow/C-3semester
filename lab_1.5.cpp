#include "widget.h"
#include "ui_widget.h"
#include <QRegularExpression>
#include <QStringList>

Form::Form(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form) {
    ui->setupUi(this);

    ui->lineEdit_4->setReadOnly(true);   // результат только для чтения

    // editingFinished срабатывает, когда курсор уходит из поля или нажат Enter
    connect(ui->lineEdit_3, &QLineEdit::editingFinished, this, &Form::onNFinished);
    connect(ui->lineEdit,   &QLineEdit::editingFinished, this, &Form::onAFinished);
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, &Form::onBFinished);

    connect(ui->pushButton,   &QPushButton::clicked, this, &Form::onUnion);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Form::onIntersect);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Form::onComplement);
}

Form::~Form() {
    delete ui;
}

// Читаем N из поля. Если там не число или число <= 0, возвращаем 0.
int Form::getU() const {
    bool ok = false;
    int n = ui->lineEdit_3->text().trimmed().toInt(&ok);
    return (ok && n > 0) ? n : 0;
}

// "7, 3 abc 500 3" -> множество (3, 7)
TSet Form::makeSet(const QString &text) const {
    int U = getU();
    TSet s(U);
    // режем текст по всему, что не цифра
    QStringList parts = text.split(QRegularExpression("[^0-9]+"), Qt::SkipEmptyParts);
    for (const QString &p : parts) {
        bool ok = false;
        qlonglong n = p.toLongLong(&ok);
        if (ok && n > 0 && n <= U) {
            s.Add((int)n);               // TSet::Add сам ещё раз проверяет границы
        }
    }
    return s;
}

// Множество -> строка по возрастанию, без лишнего: "3 7"
QString Form::cleanText(const QString &text) const {
    TSet s = makeSet(text);
    return QString::fromStdString(s.TsetToString()).trimmed();
}

void Form::onNFinished() {
    // N поменялся: переписываем A и B под новый универсум
    if (getU() > 0) {
        ui->lineEdit->setText(cleanText(ui->lineEdit->text()));
        ui->lineEdit_2->setText(cleanText(ui->lineEdit_2->text()));
    }
}

void Form::onAFinished() {
    if (getU() > 0) ui->lineEdit->setText(cleanText(ui->lineEdit->text()));
}

void Form::onBFinished() {
    if (getU() > 0) ui->lineEdit_2->setText(cleanText(ui->lineEdit_2->text()));
}

void Form::onUnion() {
    if (getU() == 0) { ui->lineEdit_4->setText("Сначала введите N (целое > 0)"); return; }
    TSet a = makeSet(ui->lineEdit->text());
    TSet b = makeSet(ui->lineEdit_2->text());
    TSet r = a | b;
    ui->lineEdit_4->setText(QString::fromStdString(r.TsetToString()).trimmed());
}

void Form::onIntersect() {
    if (getU() == 0) { ui->lineEdit_4->setText("Сначала введите N (целое > 0)"); return; }
    TSet a = makeSet(ui->lineEdit->text());
    TSet b = makeSet(ui->lineEdit_2->text());
    TSet r = a & b;
    ui->lineEdit_4->setText(QString::fromStdString(r.TsetToString()).trimmed());
}

void Form::onComplement() {
    if (getU() == 0) { ui->lineEdit_4->setText("Сначала введите N (целое > 0)"); return; }
    TSet a = makeSet(ui->lineEdit->text());
    TSet r = ~a;
    ui->lineEdit_4->setText(QString::fromStdString(r.TsetToString()).trimmed());
}