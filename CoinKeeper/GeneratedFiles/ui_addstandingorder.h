/********************************************************************************
** Form generated from reading UI file 'addstandingorder.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTANDINGORDER_H
#define UI_ADDSTANDINGORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddStandingOrderWindow
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
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
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
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblType;
    QComboBox *comboBoxChooseType;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBoxNextDate;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_3;
    QDateEdit *dateEditNextDate;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonAddOrder;
    QPushButton *buttonCancel;

    void setupUi(QDialog *AddStandingOrderWindow)
    {
        if (AddStandingOrderWindow->objectName().isEmpty())
            AddStandingOrderWindow->setObjectName(QStringLiteral("AddStandingOrderWindow"));
        AddStandingOrderWindow->resize(918, 593);
        AddStandingOrderWindow->setMinimumSize(QSize(666, 428));
        verticalLayout = new QVBoxLayout(AddStandingOrderWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(AddStandingOrderWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 63));
        horizontalLayout = new QHBoxLayout(widget);
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
        comboBoxChooseAccount->addItem(QString());
        comboBoxChooseAccount->setObjectName(QStringLiteral("comboBoxChooseAccount"));
        comboBoxChooseAccount->setFont(font);
        comboBoxChooseAccount->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(comboBoxChooseAccount);


        verticalLayout->addWidget(widget);

        widget_6 = new QWidget(AddStandingOrderWindow);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        horizontalLayout_7 = new QHBoxLayout(widget_6);
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

        widget_3 = new QWidget(AddStandingOrderWindow);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter = new QSplitter(widget_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        widget_4 = new QWidget(splitter);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, -1, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
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

        splitter->addWidget(widget_4);
        widget_7 = new QWidget(splitter);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        verticalLayout_3 = new QVBoxLayout(widget_7);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        widget_8 = new QWidget(widget_7);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        horizontalLayout_4 = new QHBoxLayout(widget_8);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, 0, -1);
        lblType = new QLabel(widget_8);
        lblType->setObjectName(QStringLiteral("lblType"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblType->sizePolicy().hasHeightForWidth());
        lblType->setSizePolicy(sizePolicy1);
        lblType->setMinimumSize(QSize(40, 0));
        lblType->setFont(font1);

        horizontalLayout_4->addWidget(lblType);

        comboBoxChooseType = new QComboBox(widget_8);
        comboBoxChooseType->setObjectName(QStringLiteral("comboBoxChooseType"));
        comboBoxChooseType->setMinimumSize(QSize(100, 0));
        comboBoxChooseType->setFont(font1);

        horizontalLayout_4->addWidget(comboBoxChooseType);


        verticalLayout_3->addWidget(widget_8);

        verticalSpacer = new QSpacerItem(20, 140, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        groupBoxNextDate = new QGroupBox(widget_7);
        groupBoxNextDate->setObjectName(QStringLiteral("groupBoxNextDate"));
        groupBoxNextDate->setFont(font1);
        verticalLayout_5 = new QVBoxLayout(groupBoxNextDate);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        dateEditNextDate = new QDateEdit(groupBoxNextDate);
        dateEditNextDate->setObjectName(QStringLiteral("dateEditNextDate"));
        dateEditNextDate->setCurrentSection(QDateTimeEdit::DaySection);
        dateEditNextDate->setCalendarPopup(true);
        dateEditNextDate->setCurrentSectionIndex(0);

        verticalLayout_5->addWidget(dateEditNextDate);

        verticalSpacer_4 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);


        verticalLayout_3->addWidget(groupBoxNextDate);

        splitter->addWidget(widget_7);

        verticalLayout_4->addWidget(splitter);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(AddStandingOrderWindow);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 41));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonAddOrder = new QPushButton(widget_2);
        buttonAddOrder->setObjectName(QStringLiteral("buttonAddOrder"));
        buttonAddOrder->setMinimumSize(QSize(150, 25));
        buttonAddOrder->setMaximumSize(QSize(220, 16777215));

        horizontalLayout_3->addWidget(buttonAddOrder);

        buttonCancel = new QPushButton(widget_2);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(90, 25));
        buttonCancel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonCancel);


        verticalLayout->addWidget(widget_2);


        retranslateUi(AddStandingOrderWindow);
        QObject::connect(buttonCancel, SIGNAL(clicked()), AddStandingOrderWindow, SLOT(close()));

        buttonAddOrder->setDefault(true);


        QMetaObject::connectSlotsByName(AddStandingOrderWindow);
    } // setupUi

    void retranslateUi(QDialog *AddStandingOrderWindow)
    {
        AddStandingOrderWindow->setWindowTitle(QApplication::translate("AddStandingOrderWindow", "Dauerauftrag hinzuf\303\274gen", nullptr));
        lblAccount->setText(QApplication::translate("AddStandingOrderWindow", "Konto:", nullptr));
        comboBoxChooseAccount->setItemText(0, QApplication::translate("AddStandingOrderWindow", "Konto ausw\303\244hlen", nullptr));

        lblLabel->setText(QApplication::translate("AddStandingOrderWindow", "Kategorie:", nullptr));
        lblValue->setText(QApplication::translate("AddStandingOrderWindow", "Wert:", nullptr));
        radioButtonPositiv->setText(QApplication::translate("AddStandingOrderWindow", "+", nullptr));
        radioButtonNegativ->setText(QApplication::translate("AddStandingOrderWindow", "-", nullptr));
        label_3->setText(QApplication::translate("AddStandingOrderWindow", ",", nullptr));
        lblDescription->setText(QApplication::translate("AddStandingOrderWindow", "Beschreibung:", nullptr));
        lblType->setText(QApplication::translate("AddStandingOrderWindow", "Typ:", nullptr));
        groupBoxNextDate->setTitle(QApplication::translate("AddStandingOrderWindow", "N\303\244chste Ausf\303\274hrung:", nullptr));
        dateEditNextDate->setDisplayFormat(QApplication::translate("AddStandingOrderWindow", "dd MMMM yyyy", nullptr));
        buttonAddOrder->setText(QApplication::translate("AddStandingOrderWindow", "Dauerauftrag hinzuf\303\274gen", nullptr));
        buttonCancel->setText(QApplication::translate("AddStandingOrderWindow", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddStandingOrderWindow: public Ui_AddStandingOrderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTANDINGORDER_H
