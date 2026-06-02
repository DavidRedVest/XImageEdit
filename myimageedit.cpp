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
    penButton = new QPushButton(this);
    penButton->setObjectName("LineButton");
    penButton->setGeometry(QRect(50, 110, 71, 51));
    penButton->setText("画笔");
    penButton->setCheckable(true);
    //penButton->setAutoExclusive(true);  //开启互斥,可以用QButtonGroup替代
    eraseButton = new QPushButton(this);
    eraseButton->setObjectName("EraseButton");
    eraseButton->setGeometry(QRect(50, 160, 71, 51));
    eraseButton->setText("橡皮擦");
    eraseButton->setCheckable(true);
    //eraseButton->setAutoExclusive(true);    //开启互斥，可以用QButtonGroup替代
    rectButton = new QPushButton(this);
    rectButton->setObjectName("rectButton");
    rectButton->setGeometry(QRect(50, 210, 71, 51));
    rectButton->setText("矩形");
    rectButton->setCheckable(true);
    undoButton = new QPushButton(this);
    undoButton->setObjectName("undoButton");
    undoButton->setGeometry(QRect(50, 260, 71, 51));
    undoButton->setText("撤销");
    undoButton->setCheckable(true);
    redoButton = new QPushButton(this);
    redoButton->setObjectName("rectButton");
    redoButton->setGeometry(QRect(50, 310, 71, 51));
    redoButton->setText("重做");
    redoButton->setCheckable(true);

    //创建一个按钮组来管理它们
    toolGroup = new QButtonGroup(this);
    toolGroup->setExclusive(true);  //设置互斥（默认就是ture)
    //把按钮加进组里，并顺遍给它们分配一个ID（方便后续判断选择哪个）
    toolGroup->addButton(penButton, 0);
    toolGroup->addButton(eraseButton, 1);
    toolGroup->addButton(rectButton, 2);
     //默认选中画笔
    penButton->setChecked(true);

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
    //设置背景颜色
    //myImage->setStyleSheet("background-color: white;");
#if 0
    myImage->setAutoFillBackground(true); // 必须开启这一句，允许自动填充背景
    QPalette pal = myImage->palette();
    pal.setColor(QPalette::Window, Qt::white); // 设置窗口背景色为白色
    myImage->setPalette(pal);
#endif

}
void MyImageEdit::initConnect(void)
{
    connect(openB,SIGNAL(clicked()), myImage, SLOT(Open()));
    connect(penButton,SIGNAL(clicked()), myImage, SLOT(SetPen()));
    connect(eraseButton,SIGNAL(clicked()), myImage, SLOT(SetErase()));
    connect(rectButton,SIGNAL(clicked()), myImage, SLOT(SetRect()));
    connect(undoButton,SIGNAL(clicked()), myImage, SLOT(Undo()));
    connect(redoButton,SIGNAL(clicked()), myImage, SLOT(Redo()));
}

