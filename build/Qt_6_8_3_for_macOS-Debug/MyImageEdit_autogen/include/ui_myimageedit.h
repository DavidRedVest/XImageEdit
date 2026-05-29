/********************************************************************************
** Form generated from reading UI file 'myimageedit.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYIMAGEEDIT_H
#define UI_MYIMAGEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyImageEdit
{
public:

    void setupUi(QWidget *MyImageEdit)
    {
        if (MyImageEdit->objectName().isEmpty())
            MyImageEdit->setObjectName("MyImageEdit");
        MyImageEdit->resize(800, 600);

        retranslateUi(MyImageEdit);

        QMetaObject::connectSlotsByName(MyImageEdit);
    } // setupUi

    void retranslateUi(QWidget *MyImageEdit)
    {
        MyImageEdit->setWindowTitle(QCoreApplication::translate("MyImageEdit", "MyImageEdit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyImageEdit: public Ui_MyImageEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYIMAGEEDIT_H
