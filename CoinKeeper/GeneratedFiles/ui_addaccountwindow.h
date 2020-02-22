/********************************************************************************
** Form generated from reading UI file 'addaccountwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDACCOUNTWINDOW_H
#define UI_ADDACCOUNTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddAccountWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelNameOfAccount;
    QLabel *labelStartBalance;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtNameOfAccount;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonPositiv;
    QRadioButton *radioButtonNegativ;
    QSpinBox *spinBoxVK;
    QLabel *labelComma;
    QSpinBox *spinBoxNK;
    QLabel *labelCurrency;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *AddAccountWindow)
    {
        if (AddAccountWindow->objectName().isEmpty())
            AddAccountWindow->setObjectName(QStringLiteral("AddAccountWindow"));
        AddAccountWindow->resize(597, 183);
        AddAccountWindow->setMinimumSize(QSize(568, 0));
        AddAccountWindow->setMaximumSize(QSize(16777215, 280));
        verticalLayout = new QVBoxLayout(AddAccountWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        widget_4 = new QWidget(AddAccountWindow);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelNameOfAccount = new QLabel(widget_5);
        labelNameOfAccount->setObjectName(QStringLiteral("labelNameOfAccount"));

        verticalLayout_2->addWidget(labelNameOfAccount);

        labelStartBalance = new QLabel(widget_5);
        labelStartBalance->setObjectName(QStringLiteral("labelStartBalance"));

        verticalLayout_2->addWidget(labelStartBalance);


        horizontalLayout_4->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        verticalLayout_3 = new QVBoxLayout(widget_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget = new QWidget(widget_6);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        txtNameOfAccount = new QLineEdit(widget);
        txtNameOfAccount->setObjectName(QStringLiteral("txtNameOfAccount"));

        horizontalLayout->addWidget(txtNameOfAccount);


        verticalLayout_3->addWidget(widget);

        widget_2 = new QWidget(widget_6);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButtonPositiv = new QRadioButton(widget_2);
        radioButtonPositiv->setObjectName(QStringLiteral("radioButtonPositiv"));
        radioButtonPositiv->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonPositiv);

        radioButtonNegativ = new QRadioButton(widget_2);
        radioButtonNegativ->setObjectName(QStringLiteral("radioButtonNegativ"));

        horizontalLayout_2->addWidget(radioButtonNegativ);

        spinBoxVK = new QSpinBox(widget_2);
        spinBoxVK->setObjectName(QStringLiteral("spinBoxVK"));
        spinBoxVK->setMinimum(0);
        spinBoxVK->setMaximum(999999999);

        horizontalLayout_2->addWidget(spinBoxVK);

        labelComma = new QLabel(widget_2);
        labelComma->setObjectName(QStringLiteral("labelComma"));

        horizontalLayout_2->addWidget(labelComma);

        spinBoxNK = new QSpinBox(widget_2);
        spinBoxNK->setObjectName(QStringLiteral("spinBoxNK"));

        horizontalLayout_2->addWidget(spinBoxNK);

        labelCurrency = new QLabel(widget_2);
        labelCurrency->setObjectName(QStringLiteral("labelCurrency"));

        horizontalLayout_2->addWidget(labelCurrency);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(widget_2);


        horizontalLayout_4->addWidget(widget_6);


        verticalLayout->addWidget(widget_4);

        widget_3 = new QWidget(AddAccountWindow);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        buttonOk = new QPushButton(widget_3);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));
        buttonOk->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(buttonOk);

        buttonCancel = new QPushButton(widget_3);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        horizontalLayout_3->addWidget(buttonCancel);


        verticalLayout->addWidget(widget_3);


        retranslateUi(AddAccountWindow);
        QObject::connect(buttonCancel, SIGNAL(clicked()), AddAccountWindow, SLOT(close()));

        buttonOk->setDefault(true);


        QMetaObject::connectSlotsByName(AddAccountWindow);
    } // setupUi

    void retranslateUi(QDialog *AddAccountWindow)
    {
        AddAccountWindow->setWindowTitle(QApplication::translate("AddAccountWindow", "Konto hinzuf\303\274gen", nullptr));
        labelNameOfAccount->setText(QApplication::translate("AddAccountWindow", "Name des Kontos:", nullptr));
        labelStartBalance->setText(QApplication::translate("AddAccountWindow", "Startwert:", nullptr));
        txtNameOfAccount->setText(QString());
        radioButtonPositiv->setText(QApplication::translate("AddAccountWindow", "+", nullptr));
        radioButtonNegativ->setText(QApplication::translate("AddAccountWindow", "-", nullptr));
        labelComma->setText(QApplication::translate("AddAccountWindow", ",", nullptr));
        labelCurrency->setText(QApplication::translate("AddAccountWindow", "EUR", nullptr));
        buttonOk->setText(QApplication::translate("AddAccountWindow", "Konto hinzuf\303\274gen", nullptr));
        buttonCancel->setText(QApplication::translate("AddAccountWindow", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddAccountWindow: public Ui_AddAccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDACCOUNTWINDOW_H
