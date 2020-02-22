/********************************************************************************
** Form generated from reading UI file 'coinkeeper.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COINKEEPER_H
#define UI_COINKEEPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoinKeeperClass
{
public:
    QAction *actionBeenden;
    QAction *actionEinstellungen;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableAccounts;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonAddAccount;
    QPushButton *buttonModifyAccount;
    QPushButton *buttonDeleteAccount;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelDate;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTime;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_5;
    QGridLayout *gridLayout;
    QSpinBox *spinBoxYear;
    QLineEdit *txtBalance;
    QComboBox *comboBoxMonth;
    QComboBox *comboBoxAccount;
    QSpacerItem *horizontalSpacer;
    QLabel *labelBalance;
    QTableWidget *tableMonthOverview;
    QLabel *label;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *buttonAddTransaction;
    QPushButton *buttonChangeTransaction;
    QPushButton *buttonDeleteTransaction;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonManageStandingOrders;
    QPushButton *buttonManageLabels;
    QFrame *line;
    QPushButton *buttonChangeProfile;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuEinstellungen;

    void setupUi(QMainWindow *CoinKeeperClass)
    {
        if (CoinKeeperClass->objectName().isEmpty())
            CoinKeeperClass->setObjectName(QStringLiteral("CoinKeeperClass"));
        CoinKeeperClass->resize(1080, 726);
        actionBeenden = new QAction(CoinKeeperClass);
        actionBeenden->setObjectName(QStringLiteral("actionBeenden"));
        actionEinstellungen = new QAction(CoinKeeperClass);
        actionEinstellungen->setObjectName(QStringLiteral("actionEinstellungen"));
        centralWidget = new QWidget(CoinKeeperClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, 0, 0);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 100));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableAccounts = new QTableWidget(widget);
        if (tableAccounts->columnCount() < 2)
            tableAccounts->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableAccounts->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableAccounts->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableAccounts->setObjectName(QStringLiteral("tableAccounts"));
        tableAccounts->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableAccounts->setAlternatingRowColors(true);
        tableAccounts->setSelectionMode(QAbstractItemView::SingleSelection);
        tableAccounts->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableAccounts->horizontalHeader()->setDefaultSectionSize(500);
        tableAccounts->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout->addWidget(tableAccounts);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        buttonAddAccount = new QPushButton(widget_2);
        buttonAddAccount->setObjectName(QStringLiteral("buttonAddAccount"));
        buttonAddAccount->setMinimumSize(QSize(181, 30));

        verticalLayout->addWidget(buttonAddAccount);

        buttonModifyAccount = new QPushButton(widget_2);
        buttonModifyAccount->setObjectName(QStringLiteral("buttonModifyAccount"));
        buttonModifyAccount->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(buttonModifyAccount);

        buttonDeleteAccount = new QPushButton(widget_2);
        buttonDeleteAccount->setObjectName(QStringLiteral("buttonDeleteAccount"));
        buttonDeleteAccount->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(buttonDeleteAccount);

        verticalSpacer_2 = new QSpacerItem(20, 99, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        labelDate = new QLabel(widget_3);
        labelDate->setObjectName(QStringLiteral("labelDate"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelDate->setFont(font);
        labelDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(labelDate);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        horizontalLayout_2 = new QHBoxLayout(widget_7);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTime = new QLabel(widget_7);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QStringLiteral("System"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        labelTime->setFont(font1);

        horizontalLayout_2->addWidget(labelTime);


        verticalLayout_2->addWidget(widget_7);

        verticalSpacer_3 = new QSpacerItem(20, 143, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout->addWidget(widget_3);


        verticalLayout_4->addWidget(widget);

        widget_6 = new QWidget(centralWidget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(933, 338));
        horizontalLayout_3 = new QHBoxLayout(widget_6);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        widget_5 = new QWidget(widget_6);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        gridLayout = new QGridLayout(widget_5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBoxYear = new QSpinBox(widget_5);
        spinBoxYear->setObjectName(QStringLiteral("spinBoxYear"));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        spinBoxYear->setFont(font2);
        spinBoxYear->setMinimum(1000);
        spinBoxYear->setMaximum(9999);

        gridLayout->addWidget(spinBoxYear, 0, 2, 1, 1);

        txtBalance = new QLineEdit(widget_5);
        txtBalance->setObjectName(QStringLiteral("txtBalance"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(txtBalance->sizePolicy().hasHeightForWidth());
        txtBalance->setSizePolicy(sizePolicy2);
        txtBalance->setFont(font);
        txtBalance->setLayoutDirection(Qt::LeftToRight);
        txtBalance->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtBalance->setReadOnly(true);
        txtBalance->setClearButtonEnabled(false);

        gridLayout->addWidget(txtBalance, 0, 6, 1, 1);

        comboBoxMonth = new QComboBox(widget_5);
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->addItem(QString());
        comboBoxMonth->setObjectName(QStringLiteral("comboBoxMonth"));
        comboBoxMonth->setMinimumSize(QSize(120, 0));
        comboBoxMonth->setFont(font2);

        gridLayout->addWidget(comboBoxMonth, 0, 0, 1, 1);

        comboBoxAccount = new QComboBox(widget_5);
        comboBoxAccount->addItem(QString());
        comboBoxAccount->setObjectName(QStringLiteral("comboBoxAccount"));
        comboBoxAccount->setMinimumSize(QSize(200, 0));
        comboBoxAccount->setFont(font2);

        gridLayout->addWidget(comboBoxAccount, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        labelBalance = new QLabel(widget_5);
        labelBalance->setObjectName(QStringLiteral("labelBalance"));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        labelBalance->setFont(font3);

        gridLayout->addWidget(labelBalance, 0, 5, 1, 1);

        tableMonthOverview = new QTableWidget(widget_5);
        if (tableMonthOverview->columnCount() < 4)
            tableMonthOverview->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableMonthOverview->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setForeground(brush);
        tableMonthOverview->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableMonthOverview->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QFont font4;
        font4.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font4);
        tableMonthOverview->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        tableMonthOverview->setObjectName(QStringLiteral("tableMonthOverview"));
        tableMonthOverview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableMonthOverview->setAlternatingRowColors(true);
        tableMonthOverview->setSelectionMode(QAbstractItemView::SingleSelection);
        tableMonthOverview->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableMonthOverview->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableMonthOverview, 1, 0, 1, 7);

        label = new QLabel(widget_5);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font2);

        gridLayout->addWidget(label, 0, 1, 1, 1);


        horizontalLayout_3->addWidget(widget_5);

        widget_4 = new QWidget(widget_6);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        buttonAddTransaction = new QPushButton(widget_4);
        buttonAddTransaction->setObjectName(QStringLiteral("buttonAddTransaction"));
        buttonAddTransaction->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(buttonAddTransaction);

        buttonChangeTransaction = new QPushButton(widget_4);
        buttonChangeTransaction->setObjectName(QStringLiteral("buttonChangeTransaction"));
        buttonChangeTransaction->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(buttonChangeTransaction);

        buttonDeleteTransaction = new QPushButton(widget_4);
        buttonDeleteTransaction->setObjectName(QStringLiteral("buttonDeleteTransaction"));
        buttonDeleteTransaction->setMinimumSize(QSize(181, 30));

        verticalLayout_3->addWidget(buttonDeleteTransaction);

        verticalSpacer = new QSpacerItem(20, 324, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        buttonManageStandingOrders = new QPushButton(widget_4);
        buttonManageStandingOrders->setObjectName(QStringLiteral("buttonManageStandingOrders"));
        buttonManageStandingOrders->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(buttonManageStandingOrders);

        buttonManageLabels = new QPushButton(widget_4);
        buttonManageLabels->setObjectName(QStringLiteral("buttonManageLabels"));
        buttonManageLabels->setMinimumSize(QSize(181, 30));

        verticalLayout_3->addWidget(buttonManageLabels);

        line = new QFrame(widget_4);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        buttonChangeProfile = new QPushButton(widget_4);
        buttonChangeProfile->setObjectName(QStringLiteral("buttonChangeProfile"));
        buttonChangeProfile->setMinimumSize(QSize(181, 30));

        verticalLayout_3->addWidget(buttonChangeProfile);


        horizontalLayout_3->addWidget(widget_4);


        verticalLayout_4->addWidget(widget_6);

        CoinKeeperClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CoinKeeperClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1080, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuEinstellungen = new QMenu(menuBar);
        menuEinstellungen->setObjectName(QStringLiteral("menuEinstellungen"));
        CoinKeeperClass->setMenuBar(menuBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuEinstellungen->menuAction());
        menuDatei->addAction(actionBeenden);
        menuEinstellungen->addAction(actionEinstellungen);

        retranslateUi(CoinKeeperClass);
        QObject::connect(actionBeenden, SIGNAL(triggered()), CoinKeeperClass, SLOT(close()));

        QMetaObject::connectSlotsByName(CoinKeeperClass);
    } // setupUi

    void retranslateUi(QMainWindow *CoinKeeperClass)
    {
        CoinKeeperClass->setWindowTitle(QApplication::translate("CoinKeeperClass", "CoinKeeper", nullptr));
        actionBeenden->setText(QApplication::translate("CoinKeeperClass", "Beenden", nullptr));
        actionEinstellungen->setText(QApplication::translate("CoinKeeperClass", "Einstellungen", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableAccounts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CoinKeeperClass", "Konto", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableAccounts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CoinKeeperClass", "Wert", nullptr));
        buttonAddAccount->setText(QApplication::translate("CoinKeeperClass", "Konto hinzuf\303\274gen", nullptr));
        buttonModifyAccount->setText(QApplication::translate("CoinKeeperClass", "Konto \303\244ndern", nullptr));
        buttonDeleteAccount->setText(QApplication::translate("CoinKeeperClass", "Konto l\303\266schen", nullptr));
        labelDate->setText(QApplication::translate("CoinKeeperClass", "02.04.2015", nullptr));
        labelTime->setText(QApplication::translate("CoinKeeperClass", "15:22:33", nullptr));
        txtBalance->setText(QApplication::translate("CoinKeeperClass", "3.789.100,63\342\202\254", nullptr));
        comboBoxMonth->setItemText(0, QApplication::translate("CoinKeeperClass", "Alle Monate", nullptr));
        comboBoxMonth->setItemText(1, QApplication::translate("CoinKeeperClass", "Dezember", nullptr));
        comboBoxMonth->setItemText(2, QApplication::translate("CoinKeeperClass", "November", nullptr));
        comboBoxMonth->setItemText(3, QApplication::translate("CoinKeeperClass", "Oktober", nullptr));
        comboBoxMonth->setItemText(4, QApplication::translate("CoinKeeperClass", "September", nullptr));
        comboBoxMonth->setItemText(5, QApplication::translate("CoinKeeperClass", "August", nullptr));
        comboBoxMonth->setItemText(6, QApplication::translate("CoinKeeperClass", "Juli", nullptr));
        comboBoxMonth->setItemText(7, QApplication::translate("CoinKeeperClass", "Juni", nullptr));
        comboBoxMonth->setItemText(8, QApplication::translate("CoinKeeperClass", "Mai", nullptr));
        comboBoxMonth->setItemText(9, QApplication::translate("CoinKeeperClass", "April", nullptr));
        comboBoxMonth->setItemText(10, QApplication::translate("CoinKeeperClass", "M\303\244rz", nullptr));
        comboBoxMonth->setItemText(11, QApplication::translate("CoinKeeperClass", "Februar", nullptr));
        comboBoxMonth->setItemText(12, QApplication::translate("CoinKeeperClass", "Januar", nullptr));

        comboBoxAccount->setItemText(0, QApplication::translate("CoinKeeperClass", "Alle Konten", nullptr));

        labelBalance->setText(QApplication::translate("CoinKeeperClass", "Bilanz:", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableMonthOverview->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("CoinKeeperClass", "Datum", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableMonthOverview->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("CoinKeeperClass", "Kategorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableMonthOverview->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("CoinKeeperClass", "Beschreibung", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableMonthOverview->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("CoinKeeperClass", "Wert", nullptr));
        label->setText(QApplication::translate("CoinKeeperClass", "Jahr:", nullptr));
        buttonAddTransaction->setText(QApplication::translate("CoinKeeperClass", "Transaktion hinzuf\303\274gen", nullptr));
        buttonChangeTransaction->setText(QApplication::translate("CoinKeeperClass", "Eintrag \303\244ndern", nullptr));
        buttonDeleteTransaction->setText(QApplication::translate("CoinKeeperClass", "Eintrag l\303\266schen", nullptr));
        buttonManageStandingOrders->setText(QApplication::translate("CoinKeeperClass", "Dauerauftr\303\244ge verwalten", nullptr));
        buttonManageLabels->setText(QApplication::translate("CoinKeeperClass", "Kategorien verwalten", nullptr));
        buttonChangeProfile->setText(QApplication::translate("CoinKeeperClass", "Profil wechseln", nullptr));
        menuDatei->setTitle(QApplication::translate("CoinKeeperClass", "Datei", nullptr));
        menuEinstellungen->setTitle(QApplication::translate("CoinKeeperClass", "Optionen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoinKeeperClass: public Ui_CoinKeeperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COINKEEPER_H
