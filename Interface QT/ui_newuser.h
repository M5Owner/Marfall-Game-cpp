/********************************************************************************
** Form generated from reading UI file 'newuser.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSER_H
#define UI_NEWUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewUser
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *input_pass2;
    QLabel *label_3;
    QLineEdit *input_pass1;
    QLineEdit *input_usr;
    QPushButton *submit;

    void setupUi(QDialog *NewUser)
    {
        if (NewUser->objectName().isEmpty())
            NewUser->setObjectName(QStringLiteral("NewUser"));
        NewUser->resize(379, 171);
        groupBox = new QGroupBox(NewUser);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 361, 151));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 30, 51, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 60, 51, 20));
        input_pass2 = new QLineEdit(groupBox);
        input_pass2->setObjectName(QStringLiteral("input_pass2"));
        input_pass2->setGeometry(QRect(157, 90, 151, 20));
        input_pass2->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 90, 111, 20));
        input_pass1 = new QLineEdit(groupBox);
        input_pass1->setObjectName(QStringLiteral("input_pass1"));
        input_pass1->setGeometry(QRect(157, 60, 151, 20));
        input_pass1->setEchoMode(QLineEdit::Password);
        input_usr = new QLineEdit(groupBox);
        input_usr->setObjectName(QStringLiteral("input_usr"));
        input_usr->setGeometry(QRect(157, 30, 151, 20));
        submit = new QPushButton(groupBox);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setGeometry(QRect(233, 120, 75, 23));

        retranslateUi(NewUser);

        QMetaObject::connectSlotsByName(NewUser);
    } // setupUi

    void retranslateUi(QDialog *NewUser)
    {
        NewUser->setWindowTitle(QApplication::translate("NewUser", "Marfall ui | Sign up", 0));
        groupBox->setTitle(QApplication::translate("NewUser", "New user", 0));
        label->setText(QApplication::translate("NewUser", "Username", 0));
        label_2->setText(QApplication::translate("NewUser", "Password", 0));
        label_3->setText(QApplication::translate("NewUser", "retype the password", 0));
        submit->setText(QApplication::translate("NewUser", "Submit", 0));
    } // retranslateUi

};

namespace Ui {
    class NewUser: public Ui_NewUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSER_H
