#ifndef MYIMAGEEDIT_H
#define MYIMAGEEDIT_H

#include <QWidget>

#include <QPushButton>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyImageEdit;
}
QT_END_NAMESPACE

class MyImageEdit : public QWidget
{
    Q_OBJECT

public:
    MyImageEdit(QWidget *parent = nullptr);
    ~MyImageEdit();

private:
    Ui::MyImageEdit *ui;

public:
    void initDate();
    void initUI();
    void initConnect();


    QPushButton *openB;
    QScrollArea *scrollArea;
    QWidget *myImage;

    QPushButton *penButton;
    QPushButton *eraseButton;

protected:


};
#endif // MYIMAGEEDIT_H
