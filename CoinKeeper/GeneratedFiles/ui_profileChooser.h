/********************************************************************************
** Form generated from reading UI file 'profileChooser.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILECHOOSER_H
#define UI_PROFILECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *horizontalWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListWidget *listProfiles;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonNewProfile;
    QPushButton *buttonOpenProfile;
    QPushButton *buttonDeleteProfile;
    QPushButton *buttonAddFolder;
    QPushButton *buttonRefreshList;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(626, 398);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(626, 398));
        MainWindow->setMaximumSize(QSize(626, 398));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalWidget = new QWidget(centralwidget);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalWidget->sizePolicy().hasHeightForWidth());
        horizontalWidget->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(horizontalWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(horizontalWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setMargin(0);

        verticalLayout_2->addWidget(label);

        listProfiles = new QListWidget(horizontalWidget);
        listProfiles->setObjectName(QStringLiteral("listProfiles"));
        listProfiles->setSortingEnabled(false);

        verticalLayout_2->addWidget(listProfiles);


        horizontalLayout->addWidget(horizontalWidget);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 30, -1, -1);
        buttonNewProfile = new QPushButton(widget);
        buttonNewProfile->setObjectName(QStringLiteral("buttonNewProfile"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonNewProfile->sizePolicy().hasHeightForWidth());
        buttonNewProfile->setSizePolicy(sizePolicy2);
        buttonNewProfile->setMinimumSize(QSize(0, 35));
        buttonNewProfile->setMaximumSize(QSize(16777215, 50));
        buttonNewProfile->setFont(font);

        verticalLayout->addWidget(buttonNewProfile);

        buttonOpenProfile = new QPushButton(widget);
        buttonOpenProfile->setObjectName(QStringLiteral("buttonOpenProfile"));
        sizePolicy2.setHeightForWidth(buttonOpenProfile->sizePolicy().hasHeightForWidth());
        buttonOpenProfile->setSizePolicy(sizePolicy2);
        buttonOpenProfile->setMinimumSize(QSize(0, 35));
        buttonOpenProfile->setMaximumSize(QSize(16777215, 50));
        buttonOpenProfile->setFont(font);

        verticalLayout->addWidget(buttonOpenProfile);

        buttonDeleteProfile = new QPushButton(widget);
        buttonDeleteProfile->setObjectName(QStringLiteral("buttonDeleteProfile"));
        sizePolicy2.setHeightForWidth(buttonDeleteProfile->sizePolicy().hasHeightForWidth());
        buttonDeleteProfile->setSizePolicy(sizePolicy2);
        buttonDeleteProfile->setMinimumSize(QSize(0, 35));
        buttonDeleteProfile->setMaximumSize(QSize(16777215, 50));
        buttonDeleteProfile->setFont(font);

        verticalLayout->addWidget(buttonDeleteProfile);

        buttonAddFolder = new QPushButton(widget);
        buttonAddFolder->setObjectName(QStringLiteral("buttonAddFolder"));
        sizePolicy2.setHeightForWidth(buttonAddFolder->sizePolicy().hasHeightForWidth());
        buttonAddFolder->setSizePolicy(sizePolicy2);
        buttonAddFolder->setMinimumSize(QSize(0, 35));
        buttonAddFolder->setMaximumSize(QSize(16777215, 50));
        buttonAddFolder->setFont(font);

        verticalLayout->addWidget(buttonAddFolder);

        buttonRefreshList = new QPushButton(widget);
        buttonRefreshList->setObjectName(QStringLiteral("buttonRefreshList"));
        sizePolicy2.setHeightForWidth(buttonRefreshList->sizePolicy().hasHeightForWidth());
        buttonRefreshList->setSizePolicy(sizePolicy2);
        buttonRefreshList->setMinimumSize(QSize(0, 35));
        buttonRefreshList->setMaximumSize(QSize(16777215, 50));
        buttonRefreshList->setFont(font);

        verticalLayout->addWidget(buttonRefreshList);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        buttonOpenProfile->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CoinKeeper  -  Profilauswahl", nullptr));
        label->setText(QApplication::translate("MainWindow", "Profile", nullptr));
        buttonNewProfile->setText(QApplication::translate("MainWindow", "Neu", nullptr));
        buttonOpenProfile->setText(QApplication::translate("MainWindow", "\303\226ffnen", nullptr));
        buttonDeleteProfile->setText(QApplication::translate("MainWindow", "L\303\266schen", nullptr));
        buttonAddFolder->setText(QApplication::translate("MainWindow", "Ordner hinzuf\303\274gen", nullptr));
        buttonRefreshList->setText(QApplication::translate("MainWindow", "Liste aktualisieren", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILECHOOSER_H
