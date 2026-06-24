#ifndef MYIMAGEEDIT_H
#define MYIMAGEEDIT_H

#include <QButtonGroup>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QWidget>

//  添加前向声明
class XImage;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MyImageEdit;
}
QT_END_NAMESPACE

class MyImageEdit : public QWidget
{
    Q_OBJECT

   public:
    MyImageEdit(QWidget* parent = nullptr);
    ~MyImageEdit();

   private:
    Ui::MyImageEdit* ui;

   public:
    void initDate();
    void initUI();
    void initConnect();

    QPushButton* openB;
    QScrollArea* scrollArea;
    //   QWidget *myImage;
    XImage* myImage;

    QPushButton* penButton;
    QPushButton* eraseButton;
    QButtonGroup* toolGroup;
    QPushButton* rectButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* saveButton;
    QSlider* penSizeSlider;
    QPushButton* colorButton;

   public slots:
    void SetColor();
};
#endif  // MYIMAGEEDIT_H
