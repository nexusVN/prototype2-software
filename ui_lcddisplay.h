/********************************************************************************
** Form generated from reading UI file 'lcddisplay.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LCDDISPLAY_H
#define UI_LCDDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lcddisplay
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QPushButton *loadButton;
    QPushButton *removeButton;
    QLabel *loadstatusLabel;
    QPushButton *printButton;
    QPushButton *resetButton;
    QPushButton *cancelButton;
    QProgressBar *progressBar;
    QFrame *line;
    QFrame *line_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lcddisplay)
    {
        if (lcddisplay->objectName().isEmpty())
            lcddisplay->setObjectName(QString::fromUtf8("lcddisplay"));
        lcddisplay->resize(800, 480);
        centralWidget = new QWidget(lcddisplay);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(460, 20, 171, 111));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(650, 20, 131, 51));
        removeButton = new QPushButton(centralWidget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(650, 80, 131, 51));
        loadstatusLabel = new QLabel(centralWidget);
        loadstatusLabel->setObjectName(QString::fromUtf8("loadstatusLabel"));
        loadstatusLabel->setGeometry(QRect(460, 150, 171, 16));
        printButton = new QPushButton(centralWidget);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(650, 170, 131, 111));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(650, 320, 131, 51));
        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(650, 380, 131, 51));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(460, 130, 171, 16));
        progressBar->setValue(0);
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(650, 290, 131, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(650, 140, 131, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        lcddisplay->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(lcddisplay);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        lcddisplay->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(lcddisplay);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        lcddisplay->setStatusBar(statusBar);

        retranslateUi(lcddisplay);

        QMetaObject::connectSlotsByName(lcddisplay);
    } // setupUi

    void retranslateUi(QMainWindow *lcddisplay)
    {
        lcddisplay->setWindowTitle(QApplication::translate("lcddisplay", "lcddisplay", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("lcddisplay", "LOAD", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("lcddisplay", "REMOVE", 0, QApplication::UnicodeUTF8));
        loadstatusLabel->setText(QApplication::translate("lcddisplay", "Load your file", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("lcddisplay", "PRINT", 0, QApplication::UnicodeUTF8));
        resetButton->setText(QApplication::translate("lcddisplay", "RESET", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("lcddisplay", "CANCEL", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class lcddisplay: public Ui_lcddisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCDDISPLAY_H
