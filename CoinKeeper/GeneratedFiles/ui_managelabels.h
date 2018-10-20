/********************************************************************************
** Form generated from reading UI file 'managelabels.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGELABELS_H
#define UI_MANAGELABELS_H

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

class Ui_ManageLabelsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableLabels;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonNewLabel;
    QPushButton *buttonDeleteLabel;
    QPushButton *buttonChangeName;
    QPushButton *buttonChangeColor;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QPushButton *buttonBack;

    void setupUi(QDialog *ManageLabelsWindow)
    {
        if (ManageLabelsWindow->objectName().isEmpty())
            ManageLabelsWindow->setObjectName(QStringLiteral("ManageLabelsWindow"));
        ManageLabelsWindow->resize(704, 425);
        ManageLabelsWindow->setMinimumSize(QSize(704, 425));
        verticalLayout = new QVBoxLayout(ManageLabelsWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(ManageLabelsWindow);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        tableLabels = new QTableWidget(widget);
        if (tableLabels->columnCount() < 2)
            tableLabels->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableLabels->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableLabels->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableLabels->setObjectName(QStringLiteral("tableLabels"));
        tableLabels->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableLabels->setSelectionMode(QAbstractItemView::SingleSelection);
        tableLabels->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableLabels->setColumnCount(2);
        tableLabels->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout->addWidget(tableLabels);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(140, 0));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonNewLabel = new QPushButton(widget_2);
        buttonNewLabel->setObjectName(QStringLiteral("buttonNewLabel"));
        buttonNewLabel->setMinimumSize(QSize(160, 30));

        verticalLayout_2->addWidget(buttonNewLabel);

        buttonDeleteLabel = new QPushButton(widget_2);
        buttonDeleteLabel->setObjectName(QStringLiteral("buttonDeleteLabel"));
        buttonDeleteLabel->setMinimumSize(QSize(160, 30));

        verticalLayout_2->addWidget(buttonDeleteLabel);

        buttonChangeName = new QPushButton(widget_2);
        buttonChangeName->setObjectName(QStringLiteral("buttonChangeName"));
        buttonChangeName->setMinimumSize(QSize(160, 30));

        verticalLayout_2->addWidget(buttonChangeName);

        buttonChangeColor = new QPushButton(widget_2);
        buttonChangeColor->setObjectName(QStringLiteral("buttonChangeColor"));
        buttonChangeColor->setMinimumSize(QSize(160, 30));

        verticalLayout_2->addWidget(buttonChangeColor);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, -1, 0, 0);
        line = new QFrame(widget_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        buttonBack = new QPushButton(widget_3);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));
        buttonBack->setMinimumSize(QSize(160, 30));

        verticalLayout_3->addWidget(buttonBack);


        verticalLayout_2->addWidget(widget_3);


        horizontalLayout->addWidget(widget_2);


        verticalLayout->addWidget(widget);


        retranslateUi(ManageLabelsWindow);
        QObject::connect(buttonBack, SIGNAL(clicked()), ManageLabelsWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(ManageLabelsWindow);
    } // setupUi

    void retranslateUi(QDialog *ManageLabelsWindow)
    {
        ManageLabelsWindow->setWindowTitle(QApplication::translate("ManageLabelsWindow", "Kategorien verwalten", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableLabels->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ManageLabelsWindow", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableLabels->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ManageLabelsWindow", "Farbe", Q_NULLPTR));
        buttonNewLabel->setText(QApplication::translate("ManageLabelsWindow", "Neue Kategorie", Q_NULLPTR));
        buttonDeleteLabel->setText(QApplication::translate("ManageLabelsWindow", "Kategorie l\303\266schen", Q_NULLPTR));
        buttonChangeName->setText(QApplication::translate("ManageLabelsWindow", "Name \303\244ndern", Q_NULLPTR));
        buttonChangeColor->setText(QApplication::translate("ManageLabelsWindow", "Farbe \303\244ndern", Q_NULLPTR));
        buttonBack->setText(QApplication::translate("ManageLabelsWindow", "Zur\303\274ck", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ManageLabelsWindow: public Ui_ManageLabelsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGELABELS_H
