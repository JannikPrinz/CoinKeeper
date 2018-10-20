/********************************************************************************
** Form generated from reading UI file 'managestandingorders.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGESTANDINGORDERS_H
#define UI_MANAGESTANDINGORDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageStandingOrders
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableStandingOrders;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonAddOrder;
    QPushButton *buttonChangeOrder;
    QPushButton *buttonDeleteOrder;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QPushButton *buttonBack;

    void setupUi(QDialog *ManageStandingOrders)
    {
        if (ManageStandingOrders->objectName().isEmpty())
            ManageStandingOrders->setObjectName(QStringLiteral("ManageStandingOrders"));
        ManageStandingOrders->resize(940, 470);
        ManageStandingOrders->setMinimumSize(QSize(715, 355));
        verticalLayout_2 = new QVBoxLayout(ManageStandingOrders);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(ManageStandingOrders);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableStandingOrders = new QTableWidget(widget);
        if (tableStandingOrders->columnCount() < 6)
            tableStandingOrders->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableStandingOrders->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableStandingOrders->setObjectName(QStringLiteral("tableStandingOrders"));
        tableStandingOrders->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableStandingOrders->setSelectionMode(QAbstractItemView::SingleSelection);
        tableStandingOrders->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout->addWidget(tableStandingOrders);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, 0, 0);
        buttonAddOrder = new QPushButton(widget_2);
        buttonAddOrder->setObjectName(QStringLiteral("buttonAddOrder"));
        buttonAddOrder->setMinimumSize(QSize(170, 30));

        verticalLayout->addWidget(buttonAddOrder);

        buttonChangeOrder = new QPushButton(widget_2);
        buttonChangeOrder->setObjectName(QStringLiteral("buttonChangeOrder"));
        buttonChangeOrder->setMinimumSize(QSize(170, 30));

        verticalLayout->addWidget(buttonChangeOrder);

        buttonDeleteOrder = new QPushButton(widget_2);
        buttonDeleteOrder->setObjectName(QStringLiteral("buttonDeleteOrder"));
        buttonDeleteOrder->setMinimumSize(QSize(170, 30));

        verticalLayout->addWidget(buttonDeleteOrder);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        line = new QFrame(widget_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        buttonBack = new QPushButton(widget_2);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));
        buttonBack->setMinimumSize(QSize(170, 30));

        verticalLayout->addWidget(buttonBack);


        horizontalLayout->addWidget(widget_2);


        verticalLayout_2->addWidget(widget);


        retranslateUi(ManageStandingOrders);
        QObject::connect(buttonBack, SIGNAL(clicked()), ManageStandingOrders, SLOT(close()));

        QMetaObject::connectSlotsByName(ManageStandingOrders);
    } // setupUi

    void retranslateUi(QDialog *ManageStandingOrders)
    {
        ManageStandingOrders->setWindowTitle(QApplication::translate("ManageStandingOrders", "Dauerauftr\303\244ge verwalten", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableStandingOrders->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ManageStandingOrders", "Konto", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableStandingOrders->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ManageStandingOrders", "Typ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableStandingOrders->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ManageStandingOrders", "Wert", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableStandingOrders->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ManageStandingOrders", "N\303\244chste Ausf\303\274hrung", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableStandingOrders->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("ManageStandingOrders", "Kategorie", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableStandingOrders->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("ManageStandingOrders", "Beschreibung", Q_NULLPTR));
        buttonAddOrder->setText(QApplication::translate("ManageStandingOrders", "Dauerauftrag hinzuf\303\274gen", Q_NULLPTR));
        buttonChangeOrder->setText(QApplication::translate("ManageStandingOrders", "Dauerauftrag \303\244ndern", Q_NULLPTR));
        buttonDeleteOrder->setText(QApplication::translate("ManageStandingOrders", "Dauerauftrag l\303\266schen", Q_NULLPTR));
        buttonBack->setText(QApplication::translate("ManageStandingOrders", "Zur\303\274ck", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ManageStandingOrders: public Ui_ManageStandingOrders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGESTANDINGORDERS_H
