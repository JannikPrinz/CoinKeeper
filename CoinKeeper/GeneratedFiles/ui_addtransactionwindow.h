/********************************************************************************
** Form generated from reading UI file 'addtransactionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRANSACTIONWINDOW_H
#define UI_ADDTRANSACTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
    QWidget *widgetAccount;
    QHBoxLayout *horizontalLayout;
    QLabel *lblAccount;
    QComboBox *comboBoxChooseAccount;
    QWidget *widgetLabel;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblLabel;
    QComboBox *comboBoxChooseLabel;
    QWidget *widgetValueDateDescription;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widgetValueDescription;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetValue;
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
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBoxInternalTransaction;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxActivateInternalTransaction;
    QWidget *widgetTargetAccount;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lblTargetAccount;
    QComboBox *comboBoxChooseTargetAccount;
    QWidget *widgetButtons;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonAddTransaction;
    QPushButton *buttonCancel;

    void setupUi(QWidget *AddTransactionWindow)
    {
        if (AddTransactionWindow->objectName().isEmpty())
            AddTransactionWindow->setObjectName(QStringLiteral("AddTransactionWindow"));
        AddTransactionWindow->resize(865, 535);
        verticalLayout = new QVBoxLayout(AddTransactionWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widgetAccount = new QWidget(AddTransactionWindow);
        widgetAccount->setObjectName(QStringLiteral("widgetAccount"));
        widgetAccount->setMaximumSize(QSize(16777215, 63));
        horizontalLayout = new QHBoxLayout(widgetAccount);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblAccount = new QLabel(widgetAccount);
        lblAccount->setObjectName(QStringLiteral("lblAccount"));
        lblAccount->setMinimumSize(QSize(60, 20));
        lblAccount->setMaximumSize(QSize(85, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblAccount->setFont(font);

        horizontalLayout->addWidget(lblAccount);

        comboBoxChooseAccount = new QComboBox(widgetAccount);
        comboBoxChooseAccount->addItem(QString());
        comboBoxChooseAccount->setObjectName(QStringLiteral("comboBoxChooseAccount"));
        comboBoxChooseAccount->setFont(font);
        comboBoxChooseAccount->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(comboBoxChooseAccount);


        verticalLayout->addWidget(widgetAccount);

        widgetLabel = new QWidget(AddTransactionWindow);
        widgetLabel->setObjectName(QStringLiteral("widgetLabel"));
        horizontalLayout_7 = new QHBoxLayout(widgetLabel);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lblLabel = new QLabel(widgetLabel);
        lblLabel->setObjectName(QStringLiteral("lblLabel"));
        lblLabel->setMinimumSize(QSize(60, 20));
        lblLabel->setMaximumSize(QSize(85, 16777215));
        lblLabel->setFont(font);

        horizontalLayout_7->addWidget(lblLabel);

        comboBoxChooseLabel = new QComboBox(widgetLabel);
        comboBoxChooseLabel->setObjectName(QStringLiteral("comboBoxChooseLabel"));
        comboBoxChooseLabel->setFont(font);
        comboBoxChooseLabel->setDuplicatesEnabled(true);

        horizontalLayout_7->addWidget(comboBoxChooseLabel);


        verticalLayout->addWidget(widgetLabel);

        widgetValueDateDescription = new QWidget(AddTransactionWindow);
        widgetValueDateDescription->setObjectName(QStringLiteral("widgetValueDateDescription"));
        horizontalLayout_4 = new QHBoxLayout(widgetValueDateDescription);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 0);
        widgetValueDescription = new QWidget(widgetValueDateDescription);
        widgetValueDescription->setObjectName(QStringLiteral("widgetValueDescription"));
        verticalLayout_2 = new QVBoxLayout(widgetValueDescription);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, -1, 0);
        widgetValue = new QWidget(widgetValueDescription);
        widgetValue->setObjectName(QStringLiteral("widgetValue"));
        horizontalLayout_2 = new QHBoxLayout(widgetValue);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, -1);
        lblValue = new QLabel(widgetValue);
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

        radioButtonPositiv = new QRadioButton(widgetValue);
        radioButtonPositiv->setObjectName(QStringLiteral("radioButtonPositiv"));
        radioButtonPositiv->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonPositiv);

        radioButtonNegativ = new QRadioButton(widgetValue);
        radioButtonNegativ->setObjectName(QStringLiteral("radioButtonNegativ"));

        horizontalLayout_2->addWidget(radioButtonNegativ);

        spinBoxVK = new QSpinBox(widgetValue);
        spinBoxVK->setObjectName(QStringLiteral("spinBoxVK"));
        spinBoxVK->setMinimumSize(QSize(91, 22));
        spinBoxVK->setMaximumSize(QSize(91, 22));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        spinBoxVK->setFont(font2);
        spinBoxVK->setMaximum(999999999);

        horizontalLayout_2->addWidget(spinBoxVK);

        label_3 = new QLabel(widgetValue);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBoxNK = new QSpinBox(widgetValue);
        spinBoxNK->setObjectName(QStringLiteral("spinBoxNK"));
        spinBoxNK->setMinimumSize(QSize(41, 22));
        spinBoxNK->setMaximumSize(QSize(41, 22));
        spinBoxNK->setFont(font2);

        horizontalLayout_2->addWidget(spinBoxNK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widgetValue);

        lblDescription = new QLabel(widgetValueDescription);
        lblDescription->setObjectName(QStringLiteral("lblDescription"));
        lblDescription->setFont(font1);

        verticalLayout_2->addWidget(lblDescription);

        textEditDescription = new QPlainTextEdit(widgetValueDescription);
        textEditDescription->setObjectName(QStringLiteral("textEditDescription"));

        verticalLayout_2->addWidget(textEditDescription);


        horizontalLayout_4->addWidget(widgetValueDescription);

        calendarWidget = new QCalendarWidget(widgetValueDateDescription);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(320, 191));
        calendarWidget->setGridVisible(true);

        horizontalLayout_4->addWidget(calendarWidget);


        verticalLayout->addWidget(widgetValueDateDescription);

        widget = new QWidget(AddTransactionWindow);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBoxInternalTransaction = new QGroupBox(widget);
        groupBoxInternalTransaction->setObjectName(QStringLiteral("groupBoxInternalTransaction"));
        groupBoxInternalTransaction->setFont(font1);
        verticalLayout_3 = new QVBoxLayout(groupBoxInternalTransaction);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkBoxActivateInternalTransaction = new QCheckBox(groupBoxInternalTransaction);
        checkBoxActivateInternalTransaction->setObjectName(QStringLiteral("checkBoxActivateInternalTransaction"));
        checkBoxActivateInternalTransaction->setFont(font1);

        verticalLayout_3->addWidget(checkBoxActivateInternalTransaction);

        widgetTargetAccount = new QWidget(groupBoxInternalTransaction);
        widgetTargetAccount->setObjectName(QStringLiteral("widgetTargetAccount"));
        horizontalLayout_9 = new QHBoxLayout(widgetTargetAccount);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, -1, 0, -1);
        lblTargetAccount = new QLabel(widgetTargetAccount);
        lblTargetAccount->setObjectName(QStringLiteral("lblTargetAccount"));
        lblTargetAccount->setEnabled(false);
        lblTargetAccount->setMaximumSize(QSize(160, 16777215));
        lblTargetAccount->setFont(font);

        horizontalLayout_9->addWidget(lblTargetAccount);

        comboBoxChooseTargetAccount = new QComboBox(widgetTargetAccount);
        comboBoxChooseTargetAccount->addItem(QString());
        comboBoxChooseTargetAccount->setObjectName(QStringLiteral("comboBoxChooseTargetAccount"));
        comboBoxChooseTargetAccount->setEnabled(false);
        comboBoxChooseTargetAccount->setFont(font);
        comboBoxChooseTargetAccount->setDuplicatesEnabled(true);

        horizontalLayout_9->addWidget(comboBoxChooseTargetAccount);


        verticalLayout_3->addWidget(widgetTargetAccount);


        horizontalLayout_6->addWidget(groupBoxInternalTransaction);


        verticalLayout->addWidget(widget);

        widgetButtons = new QWidget(AddTransactionWindow);
        widgetButtons->setObjectName(QStringLiteral("widgetButtons"));
        widgetButtons->setMaximumSize(QSize(16777215, 41));
        horizontalLayout_3 = new QHBoxLayout(widgetButtons);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonAddTransaction = new QPushButton(widgetButtons);
        buttonAddTransaction->setObjectName(QStringLiteral("buttonAddTransaction"));
        buttonAddTransaction->setMinimumSize(QSize(130, 25));
        buttonAddTransaction->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonAddTransaction);

        buttonCancel = new QPushButton(widgetButtons);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(90, 25));
        buttonCancel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(buttonCancel);


        verticalLayout->addWidget(widgetButtons);

        QWidget::setTabOrder(comboBoxChooseAccount, comboBoxChooseLabel);
        QWidget::setTabOrder(comboBoxChooseLabel, radioButtonPositiv);
        QWidget::setTabOrder(radioButtonPositiv, radioButtonNegativ);
        QWidget::setTabOrder(radioButtonNegativ, spinBoxVK);
        QWidget::setTabOrder(spinBoxVK, spinBoxNK);
        QWidget::setTabOrder(spinBoxNK, textEditDescription);
        QWidget::setTabOrder(textEditDescription, calendarWidget);
        QWidget::setTabOrder(calendarWidget, checkBoxActivateInternalTransaction);
        QWidget::setTabOrder(checkBoxActivateInternalTransaction, comboBoxChooseTargetAccount);
        QWidget::setTabOrder(comboBoxChooseTargetAccount, buttonAddTransaction);
        QWidget::setTabOrder(buttonAddTransaction, buttonCancel);

        retranslateUi(AddTransactionWindow);
        QObject::connect(buttonCancel, SIGNAL(clicked()), AddTransactionWindow, SLOT(close()));

        buttonAddTransaction->setDefault(true);


        QMetaObject::connectSlotsByName(AddTransactionWindow);
    } // setupUi

    void retranslateUi(QWidget *AddTransactionWindow)
    {
        AddTransactionWindow->setWindowTitle(QApplication::translate("AddTransactionWindow", "Transaktion hinzuf\303\274gen", nullptr));
        lblAccount->setText(QApplication::translate("AddTransactionWindow", "Konto:", nullptr));
        comboBoxChooseAccount->setItemText(0, QApplication::translate("AddTransactionWindow", "Konto ausw\303\244hlen", nullptr));

        lblLabel->setText(QApplication::translate("AddTransactionWindow", "Kategorie:", nullptr));
        lblValue->setText(QApplication::translate("AddTransactionWindow", "Wert:", nullptr));
        radioButtonPositiv->setText(QApplication::translate("AddTransactionWindow", "+", nullptr));
        radioButtonNegativ->setText(QApplication::translate("AddTransactionWindow", "-", nullptr));
        label_3->setText(QApplication::translate("AddTransactionWindow", ",", nullptr));
        lblDescription->setText(QApplication::translate("AddTransactionWindow", "Beschreibung:", nullptr));
        groupBoxInternalTransaction->setTitle(QApplication::translate("AddTransactionWindow", "Profilinterne Transaktion", nullptr));
        checkBoxActivateInternalTransaction->setText(QApplication::translate("AddTransactionWindow", "Aktivieren", nullptr));
        lblTargetAccount->setText(QApplication::translate("AddTransactionWindow", "Verbundenes Konto:", nullptr));
        comboBoxChooseTargetAccount->setItemText(0, QApplication::translate("AddTransactionWindow", "Konto ausw\303\244hlen", nullptr));

        buttonAddTransaction->setText(QApplication::translate("AddTransactionWindow", "Transaktion hinzuf\303\274gen", nullptr));
        buttonCancel->setText(QApplication::translate("AddTransactionWindow", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTransactionWindow: public Ui_AddTransactionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRANSACTIONWINDOW_H
