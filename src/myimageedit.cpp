#include "myimageedit.h"

#include <QColorDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "./ui_myimageedit.h"
#include "ximage.h"

MyImageEdit::MyImageEdit(QWidget* parent)
    : QWidget(parent), ui(new Ui::MyImageEdit) {
    ui->setupUi(this);

    initDate();
    initUI();
    initConnect();

    // 设置一个合理的最小尺寸，防止用户缩的太小导致按钮重叠
    // this->setMinimumSize(800, 600);

    // 启动时直接最大化
    // this->showMaximized();
    // 或者启动时给一个合理的大小
    // this->resize(900, 800);
}

MyImageEdit::~MyImageEdit() {
    delete ui;
}
void MyImageEdit::initDate(void) {
}
static void setupIconButton(QPushButton* btn, const QString& iconPath,
                            const QSize& size = {70, 50}) {
    btn->setIcon(QIcon(iconPath));
    btn->setIconSize(size);
    btn->setText("");
    btn->setFlat(true);
    btn->setStyleSheet("border: none;");
}

void MyImageEdit::initUI(void) {
    // 使用布局管理器
    openB = new QPushButton(this);
    penButton = new QPushButton(this);
    penButton->setText("画笔");
    eraseButton = new QPushButton(this);
    eraseButton->setText("橡皮擦");
    rectButton = new QPushButton(this);
    undoButton = new QPushButton(this);
    redoButton = new QPushButton(this);
    penSizeSlider = new QSlider(this);
    penSizeSlider->setMinimum(5);
    penSizeSlider->setMaximum(50);
    penSizeSlider->setValue(5);  // 设置初始值
    colorButton = new QPushButton(this);
    saveButton = new QPushButton(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    // 【关键优化 1】：关闭内部 Widget 的强制拉伸。
    // 这意味着里面的 XImage
    // 可以保持其真实的像素大小，超出部分会自动出现滚动条。
    scrollArea->setWidgetResizable(false);
    myImage = new XImage();
    myImage->setObjectName("myImage");
    scrollArea->setWidget(myImage);
    // 构建左侧工具栏垂直布局 (QVBoxLayout)
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(openB);
    leftLayout->addWidget(saveButton);
    leftLayout->addWidget(penButton);
    leftLayout->addWidget(eraseButton);
    leftLayout->addWidget(rectButton);
    // 撤销和重做按钮并排显示比较好看，套一个水平布局
    QHBoxLayout* historyLayout = new QHBoxLayout();
    historyLayout->addWidget(undoButton);
    historyLayout->addWidget(redoButton);
    leftLayout->addLayout(historyLayout);
    leftLayout->addWidget(penSizeSlider);
    leftLayout->addWidget(colorButton);
    // 加一个弹簧 (Spacer)，把上面的按钮全顶到最上面
    QSpacerItem* spacer =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftLayout->addItem(spacer);
    // 构建全局水平布局 (QHBoxLayout)
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    // 把左侧工具栏加进来
    mainLayout->addLayout(leftLayout);
    // 把滚动区域加进来，参数 1 表示拉伸因子，让它占据所有剩余空间
    mainLayout->addWidget(scrollArea, 1);
    // 应用布局到主窗口
    this->setLayout(mainLayout);

    setupIconButton(openB, ":/Resources/open.svg");
    setupIconButton(penButton, ":/Resources/pen.svg");
    setupIconButton(eraseButton, ":/Resources/eraser.svg");
    setupIconButton(rectButton, ":/Resources/rect.svg");
    setupIconButton(undoButton, ":/Resources/undo.svg", {50, 40});
    setupIconButton(redoButton, ":/Resources/redo.svg", {50, 40});
    setupIconButton(colorButton, ":/Resources/color.svg");
    setupIconButton(saveButton, ":/Resources/save.svg");
}
void MyImageEdit::initConnect(void) {
    connect(openB, SIGNAL(clicked()), myImage, SLOT(Open()));
    connect(penButton, SIGNAL(clicked()), myImage, SLOT(SetPen()));
    connect(eraseButton, SIGNAL(clicked()), myImage, SLOT(SetErase()));
    connect(rectButton, SIGNAL(clicked()), myImage, SLOT(SetRect()));
    connect(undoButton, SIGNAL(clicked()), myImage, SLOT(Undo()));
    connect(redoButton, SIGNAL(clicked()), myImage, SLOT(Redo()));
    connect(penSizeSlider, SIGNAL(valueChanged(int)), myImage,
            SLOT(SetPenSize(int)));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(SetColor()));
    connect(saveButton, SIGNAL(clicked()), myImage, SLOT(SavePicture()));
}

void MyImageEdit::SetColor() {
    QColor col = QColorDialog::getColor(Qt::red, this);
    // 如果取消，则直接返回，不修改颜色
    if (!col.isValid()) {
        return;
    }
    QString sty = QString("background-color:rgba(%1, %2, %3, %4);")
                      .arg(col.red())
                      .arg(col.green())
                      .arg(col.blue())
                      .arg(col.alpha());
    colorButton->setStyleSheet(sty);
    myImage->SetPenColor(col.red(), col.green(), col.blue(), col.alpha());
}
