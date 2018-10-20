/********************************************************************************
** Form generated from reading UI file 'addtransactionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRANSACTIONWINDOW_H
#define UI_ADDTRANSACTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTransactionWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblAccount;
    QComboBox *comboBoxChooseAccount;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblLabel;
    QComboBox *comboBoxChooseLabel;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblValue;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButtonPositiv;
    QRadioButton *radioButtonNegativ;
    QSpinBox *spinBoxVK;
    QLabel *label_3;
    QSpinBox *spinBoxNK;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblDescription;
    QPlainTextEdit *textEditDescription;
    QCalendarWidget *calendarWidget;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonAddTransaction;
    QPushButton *buttonCancel;

    void setupUi(QWidget *AddTransactionWindow)
    {
        if (AddTransactionWindow->objectName().isEmpty())
            AddTransactionWindow->setObjectName(QStringLiteral("AddTransactionWindow"));
        AddTransactionWindow->resize(865, 511);
        verticalLayout = new QVBoxLayout(AddTransactionWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(AddTransactionWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 63));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblAccount = new QLabel(widget);
        lblAccount->setObjectName(QStringLiteral("lblAccount"));
        lblAccount->setMinimumSize(QSize(60, 20));
        lblAccount->setMaximumSize(QSize(80, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblAccount->setFont(font);

        horizontalLayout->addWidget(lblAccount);

        comboBoxChooseAccount = new QComboBox(widget);
        comboBoxChooseAccount->setObjectName(QStringLiteral("comboBoxChooseAccount"));
        comboBoxChooseAccount->setFont(font);
        comboBoxChooseAccount->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(comboBoxChooseAccount);


        verticalLayout->addWidget(widget);

        widget_6 = new QWidget(AddTransactionWindow);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        horizontalLayout_7 = new QHBoxLayout(widget_6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lblLabel = new QLabel(widget_6);
        lblLabel->setObjectName(QStringLiteral("lblLabel"));
        lblLabel->setMinimumSize(QSize(60, 20));
        lblLabel->setMaximumSize(QSize(80, 16777215));
        lblLabel->setFont(font);

        horizontalLayout_7->addWidget(lblLabel);

        comboBoxChooseLabel = new QComboBox(widget_6);
        comboBoxChooseLabel->setObjectName(QStringLiteral("comboBoxChooseLabel"));
        comboBoxChooseLabel->setFont(font);
        comboBoxChooseLabel->setDuplicatesEnabled(true);

        horizontalLayout_7->addWidget(comboBoxChooseLabel);


        verticalLayout->addWidget(widget_6);

        widget_3 = new QWidget(AddTransactionWindow);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 0);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, -1, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        lblValue = new QLabel(widget_5);
        lblValue->setObjectName(QStringLiteral("lblValue"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        lblValue->setFont(font1);

        horizontalLayout_2->addWidget(lblValue);

        horizontalSpacer = new QSpacerItem(25, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radioButtonPositiv = new QRadioButton(widget_5);
        radioButtonPositiv->setObjectName(QStringLiteral("radioButtonPositiv"));
        radioButtonPositiv->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonPositiv);

        radioButtonNegativ = new QRadioButton(widget_5);
        radioButtonNegativ->setObjectName(QStringLiteral("radioButtonNegativ"));

        horizontalLayout_2->addWidget(radioButtonNegativ);

        spinBoxVK = new QSpinBox(widget_5);
        spinBoxVK->setObjectName(QStringLiteral("spinBoxVK"));
        spinBoxVK->setMinimumSize(QSize(91, 22));
        spinBoxVK->setMaximumSize(QSize(91, 22));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        spinBoxVK->setFont(font2);
        spinBoxVK->setMinimum(-999999999);
        spinBoxVK->setMaximum(999999999);

        horizontalLayout_2->addWidget(spinBoxVK);

        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBoxNK = new QSpinBox(widget_5);
        spinBoxNK->setObjectName(QStringLiteral("spinBoxNK"));
        spinBoxNK->setMinimumSize(QSize(41, 22));
        spinBoxNK->setMaximumSize(QSize(41, 22));
        spinBoxNK->setFont(font2);

        horizontalLayout_2->addWidget(spinBoxNK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget_5);

        lblDescription = new QLabel(widget_4);
        lblDescription->setObjectName(QStringLiteral("lblDescription"));
        lblDescription->setFont(font1);

        verticalLayout_2->addWidget(lblDescription);

        textEditDescription = new QPlainTextEdit(widget_4);
        textEditDescription->setObjectName(QStringLiteral("textEditDescription"));

        verticalLayout_2->addWidget(textEditDescription);


        horizontalLayout_4->addWidget(widget_4);

        calendarWidget = new QCalendarWidget(widget_3);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(251, 191));
        calendarWidget->setGridVisible(true);

        horizontalLayout_4->addWidget(calendarWidget);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(AddTransactionWindow);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 41));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonAddTransaction = new QPushButton(widget_2);
        buttonAddTransaction->setObjectName(QStringLiteral("buttonAddTransaction"));
        buttonAddTransaction->setMinimumSize(QSize(130, 25));
        buttonAddTransaction->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonAddTransaction);

        buttonCancel = new QPushButton(widget_2);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(90, 25));
        buttonCancel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonCancel);


        verticalLayout->addWidget(widget_2);


        retranslateUi(AddTransactionWindow);
        QObject::connect(buttonCancel, SIGNAL(clicked()), AddTransactionWindow, SLOT(close()));

        buttonAddTransaction->setDefault(true);


        QMetaObject::connectSlotsByName(AddTransactionWindow);
    } // setupUi

    void retranslateUi(QWidget *AddTransactionWindow)
    {
        AddTransactionWindow->setWindowTitle(QApplication::translate("AddTransactionWindow", "Transaktion hinzuf\303\274gen", Q_NULLPTR));
        lblAccount->setText(QApplication::translate("AddTransactionWindow", "Konto:", Q_NULLPTR));
        comboBoxChooseAccount->clear();
        comboBoxChooseAccount->insertItems(0, QStringList()
         << QApplication::translate("AddTransactionWindow", "Konto ausw\303\244hlen", Q_NULLPTR)
        );
        lblLabel->setText(QApplication::translate("AddTransactionWindow", "Kategorie:", Q_NULLPTR));
        lblValue->setText(QApplication::translate("AddTransactionWindow", "Wert:", Q_NULLPTR));
        radioButtonPositiv->setText(QApplication::translate("AddTransactionWindow", "+", Q_NULLPTR));
        radioButtonNegativ->setText(QApplication::translate("AddTransactionWindow", "-", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddTransactionWindow", ",", Q_NULLPTR));
        lblDescription->setText(QApplication::translate("AddTransactionWindow", "Beschreibung:", Q_NULLPTR));
        buttonAddTransaction->setText(QApplication::translate("AddTransactionWindow", "Transaktion hinzuf\303\274gen", Q_NULLPTR));
        buttonCancel->setText(QApplication::translate("AddTransactionWindow", "Abbrechen", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddTransactionWindow: public Ui_AddTransactionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRANSACTIONWINDOW_H
