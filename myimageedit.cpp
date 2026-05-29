#include "myimageedit.h"
#include "./ui_myimageedit.h"

#include "ximage.h"

MyImageEdit::MyImageEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyImageEdit)
{
    ui->setupUi(this);

    initDate();
    initUI();
    initConnect();
}

MyImageEdit::~MyImageEdit()
{
    delete ui;
}
void MyImageEdit::initDate(void)
{

}
void MyImageEdit::initUI(void)
{
    LineButton = new QPushButton(this);
    LineButton->setObjectName("LineButton");
    LineButton->setGeometry(QRect(50, 110, 71, 51));
    LineButton->setText("画笔");
    LineButton->setCheckable(true);
    LineButton->setAutoExclusive(true);
    EraseButton = new QPushButton(this);
    EraseButton->setObjectName("EraseButton");
    EraseButton->setGeometry(QRect(50, 160, 71, 51));
    EraseButton->setText("橡皮擦");
    EraseButton->setCheckable(true);
    EraseButton->setAutoExclusive(true);

   // qDebug()<<"initUI test";
    openB = new QPushButton(this);
    openB->setObjectName("openB");
    openB->setGeometry(QRect(60, 70, 51, 41));
    openB->setText("Open");
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setGeometry(QRect(140, 0, 681, 621));
    scrollArea->setWidgetResizable(true);
#if 0
    myImage = new QWidget(this);
    myImage->setObjectName("myImage");
    myImage->setGeometry(QRect(0, 0, 679, 619));
#endif
    myImage = new XImage(); //提升属性
    myImage->setObjectName("myImage");
    myImage->setGeometry(QRect(0, 0, 679, 619));
    scrollArea->setWidget(myImage);

}
void MyImageEdit::initConnect(void)
{
    connect(openB,SIGNAL(clicked()), myImage, SLOT(Open()));

}

