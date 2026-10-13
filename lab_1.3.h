#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "TSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class Form : public QWidget {
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void onNFinished();      // ушли курсором из поля N
    void onAFinished();      // ушли курсором из поля A
    void onBFinished();      // ушли курсором из поля B
    void onUnion();          // кнопка ∨
    void onIntersect();      // кнопка ∧
    void onComplement();     // кнопка ¬

private:
    int  getU() const;                           // N из поля, 0 если введено неверно
    TSet makeSet(const QString &text) const;     // текст -> множество (только 1..N)
    QString cleanText(const QString &text) const;// текст -> чистый отсортированный текст

    Ui::Form *ui;
};

#endif // WIDGET_H