/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

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
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Userwindow
{
public:
    QLabel *welcom_lbl;
    QGroupBox *groupBox;
    QLabel *welcom_lbl_2;
    QLabel *welcom_lbl_3;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QRadioButton *radioButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Userwindow)
    {
        if (Userwindow->objectName().isEmpty())
            Userwindow->setObjectName(QStringLiteral("Userwindow"));
        Userwindow->resize(390, 309);
        welcom_lbl = new QLabel(Userwindow);
        welcom_lbl->setObjectName(QStringLiteral("welcom_lbl"));
        welcom_lbl->setGeometry(QRect(10, 0, 241, 21));
        groupBox = new QGroupBox(Userwindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 191, 91));
        welcom_lbl_2 = new QLabel(groupBox);
        welcom_lbl_2->setObjectName(QStringLiteral("welcom_lbl_2"));
        welcom_lbl_2->setGeometry(QRect(20, 20, 151, 31));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(false);
        welcom_lbl_2->setFont(font);
        welcom_lbl_3 = new QLabel(groupBox);
        welcom_lbl_3->setObjectName(QStringLiteral("welcom_lbl_3"));
        welcom_lbl_3->setGeometry(QRect(20, 50, 151, 31));
        welcom_lbl_3->setFont(font);
        groupBox_2 = new QGroupBox(Userwindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 371, 181));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(120, 30, 231, 20));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 61, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 91, 16));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 60, 231, 20));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 91, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 120, 91, 16));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 90, 231, 20));
        lineEdit_3->setEchoMode(QLineEdit::Password);
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(120, 120, 231, 20));
        lineEdit_4->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(251, 150, 101, 23));
        groupBox_3 = new QGroupBox(Userwindow);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(210, 30, 171, 91));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 51, 16));
        lineEdit_5 = new QLineEdit(groupBox_3);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(60, 20, 101, 20));
        lineEdit_5->setEchoMode(QLineEdit::Password);
        radioButton = new QRadioButton(groupBox_3);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 40, 151, 21));
        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 60, 101, 23));

        retranslateUi(Userwindow);

        QMetaObject::connectSlotsByName(Userwindow);
    } // setupUi

    void retranslateUi(QDialog *Userwindow)
    {
        Userwindow->setWindowTitle(QApplication::translate("Userwindow", "Dialog", 0));
        welcom_lbl->setText(QApplication::translate("Userwindow", "Welcome M5Owner!", 0));
        groupBox->setTitle(QApplication::translate("Userwindow", "Score and level", 0));
        welcom_lbl_2->setText(QApplication::translate("Userwindow", "Score: 12635", 0));
        welcom_lbl_3->setText(QApplication::translate("Userwindow", "Current level: 2", 0));
        groupBox_2->setTitle(QApplication::translate("Userwindow", "Change password", 0));
        lineEdit->setText(QApplication::translate("Userwindow", "M5Owner", 0));
        label->setText(QApplication::translate("Userwindow", "Username", 0));
        label_2->setText(QApplication::translate("Userwindow", "Current password", 0));
        label_3->setText(QApplication::translate("Userwindow", "New password", 0));
        label_4->setText(QApplication::translate("Userwindow", "Repeat password", 0));
        pushButton->setText(QApplication::translate("Userwindow", "Update password", 0));
        groupBox_3->setTitle(QApplication::translate("Userwindow", "Delete account", 0));
        label_5->setText(QApplication::translate("Userwindow", "Password", 0));
        radioButton->setText(QApplication::translate("Userwindow", "Yes, Delete my account", 0));
        pushButton_2->setText(QApplication::translate("Userwindow", "Delete account", 0));
    } // retranslateUi

};

namespace Ui {
    class Userwindow: public Ui_Userwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
