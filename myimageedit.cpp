#include "myimageedit.h"
#include "./ui_myimageedit.h"

#include "ximage.h"
#include <QColorDialog>
#include <QIcon>

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
    if(penButton->objectName().isEmpty()) {
        penButton->setObjectName("LineButton");
    }
    penButton->setGeometry(QRect(50, 90, 70, 50));
    penButton->setText("画笔");
    penButton->setCheckable(true);
    //penButton->setAutoExclusive(true);  //开启互斥,可以用QButtonGroup替代
    eraseButton = new QPushButton(this);
    eraseButton->setObjectName("EraseButton");
    eraseButton->setGeometry(QRect(50, 170, 70, 50));
    eraseButton->setText("橡皮擦");
    eraseButton->setCheckable(true);
    //eraseButton->setAutoExclusive(true);    //开启互斥，可以用QButtonGroup替代
    rectButton = new QPushButton(this);
    rectButton->setObjectName("rectButton");
    rectButton->setGeometry(QRect(50, 260, 70, 50));
    rectButton->setText("矩形");
    rectButton->setCheckable(true);
    undoButton = new QPushButton(this);
    undoButton->setObjectName("undoButton");
    undoButton->setGeometry(QRect(20, 340, 50, 40));
    undoButton->setText("撤销");
    undoButton->setCheckable(true);
    redoButton = new QPushButton(this);
    redoButton->setObjectName("rectButton");
    redoButton->setGeometry(QRect(80, 340, 50, 40));
    redoButton->setText("重做");
    redoButton->setCheckable(true);
    penSizeSlider = new QSlider(this);
    if(penSizeSlider->objectName().isEmpty()) {
        penSizeSlider->setObjectName("penSizeSlider");
    }
    penSizeSlider->setGeometry(QRect(10, 420, 100, 30));
    penSizeSlider->setOrientation(Qt::Orientation::Horizontal);
    //设置区间值
    penSizeSlider->setMinimum(5);
    penSizeSlider->setMaximum(50);
    penSizeSlider->setValue(5); //设置初始值
    colorButton = new QPushButton(this);
    colorButton->setObjectName("colorButton");
    colorButton->setGeometry(QRect(50, 500, 70, 50));
    colorButton->setText("颜色");

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
    openB->setGeometry(QRect(50, 10, 70, 50));
    openB->setText("Open");
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setGeometry(QRect(140, 0, 681, 621));
    //对于图片编辑器，这里通常设置为false,允许内部的myImage保持自身真实大小
    scrollArea->setWidgetResizable(false);
#if 0
    myImage = new QWidget(this);
    myImage->setObjectName("myImage");
    myImage->setGeometry(QRect(0, 0, 679, 619));
#endif
    myImage = new XImage(); //提升属性
    myImage->setObjectName("myImage");
    //对于图片编辑器，不需要这行代码
    //myImage->setGeometry(QRect(0, 0, 679, 619));
    scrollArea->setWidget(myImage);
    //设置背景颜色
    //myImage->setStyleSheet("background-color: white;");
#if 0
    myImage->setAutoFillBackground(true); // 必须开启这一句，允许自动填充背景
    QPalette pal = myImage->palette();
    pal.setColor(QPalette::Window, Qt::white); // 设置窗口背景色为白色
    myImage->setPalette(pal);
#endif


#if 1
    //增加图片资源
    //设置图片图标
    QIcon openIcon(":/Resources/open.svg");
    openB->setIcon(openIcon);
    //调整图标大小填满按钮
    openB->setIconSize(QSize(70, 50));
    //去除原有的文本和默认边框
    openB->setText("");
    openB->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    openB->setStyleSheet("border: none;");  //彻底去掉边框

    //设置图片图标
    QIcon penIcon(":/Resources/pen.svg");
    penButton->setIcon(penIcon);
    //调整图标大小填满按钮
    penButton->setIconSize(QSize(70, 50));
    //去除原有的文本和默认边框
    penButton->setText("");
    penButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    penButton->setStyleSheet("border: none;");  //彻底去掉边框

    //设置图片图标
    QIcon eraserIcon(":/Resources/eraser.svg");
    eraseButton->setIcon(eraserIcon);
    //调整图标大小填满按钮
    eraseButton->setIconSize(QSize(70, 50));
    //去除原有的文本和默认边框
    eraseButton->setText("");
    eraseButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    eraseButton->setStyleSheet("border: none;");  //彻底去掉边框

    //设置图片图标
    QIcon rectIcon(":/Resources/rect.svg");
    rectButton->setIcon(rectIcon);
    //调整图标大小填满按钮
    rectButton->setIconSize(QSize(70, 50));
    //去除原有的文本和默认边框
    rectButton->setText("");
    rectButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    rectButton->setStyleSheet("border: none;");  //彻底去掉边框

    //设置图片图标
    QIcon undoIcon(":/Resources/undo.png");
    undoButton->setIcon(undoIcon);
    //调整图标大小填满按钮
    undoButton->setIconSize(QSize(50, 40));
    //去除原有的文本和默认边框
    undoButton->setText("");
    undoButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    undoButton->setStyleSheet("border: none;");  //彻底去掉边框

    //设置图片图标
    QIcon redoIcon(":/Resources/redo.png");
    redoButton->setIcon(redoIcon);
    //调整图标大小填满按钮
    redoButton->setIconSize(QSize(50, 40));
    //去除原有的文本和默认边框
    redoButton->setText("");
    redoButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    redoButton->setStyleSheet("border: none;");  //彻底去掉边框

    QIcon colorIcon(":/Resources/color.svg");
    colorButton->setIcon(colorIcon);
    //调整图标大小填满按钮
    colorButton->setIconSize(QSize(70, 50));
    //去除原有的文本和默认边框
    colorButton->setText("");
    colorButton->setFlat(true); //设置为扁平化，去掉默认按下的立体边框
    colorButton->setStyleSheet("border: none;");  //彻底去掉边框
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
    connect(penSizeSlider,SIGNAL(valueChanged(int)), myImage, SLOT(SetPenSize(int)));
    connect(colorButton,SIGNAL(clicked()), this, SLOT(SetColor()));
}

void MyImageEdit::SetColor()
{
    QColor col = QColorDialog::getColor(Qt::red, this);
    //如果取消，则直接返回，不修改颜色
    if(!col.isValid()) {
        return;
    }
    QString sty = QString("background-color:rgba(%1, %2, %3, %4);")
                      .arg(col.red()).arg(col.green()).arg(col.blue()).arg(col.alpha());
    colorButton->setStyleSheet(sty);
    myImage->SetPenColor( col.red(), col.green(), col.blue(), col.alpha() );
}
