/********************************************************************************
** Form generated from reading UI file 'QtPastePic.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPASTEPIC_H
#define UI_QTPASTEPIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtPastePicClass
{
public:
    QWidget *centralWidget;
    QScrollArea *source_pic_show;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *target_pic_show;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *source_pic_lable;
    QLabel *target_pic_lable;
    QPushButton *source_pic_load_button;
    QPushButton *target_pic_load_button;
    QPushButton *LittleButton;
    QPushButton *BigButton;
    QPushButton *UpButton;
    QPushButton *DownButton;
    QPushButton *RightButton;
    QPushButton *LiftButton;
    QPushButton *source_mask_load_button;
    QScrollArea *source_mask_show;
    QWidget *scrollAreaWidgetContents_3;
    QPushButton *target_mask_load_button;
    QLabel *source_pic_lable_2;
    QScrollArea *target_mask_show;
    QWidget *scrollAreaWidgetContents_4;
    QLabel *target_mask_lable;
    QLabel *target_depth_lable;
    QPushButton *target_depth_load_button;
    QScrollArea *target_depth_show;
    QWidget *scrollAreaWidgetContents_5;
    QScrollArea *output_show;
    QWidget *scrollAreaWidgetContents_6;
    QPushButton *output;
    QLabel *label;
    QPushButton *mask;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtPastePicClass)
    {
        if (QtPastePicClass->objectName().isEmpty())
            QtPastePicClass->setObjectName(QStringLiteral("QtPastePicClass"));
        QtPastePicClass->resize(1155, 921);
        QtPastePicClass->setMouseTracking(true);
        QtPastePicClass->setTabletTracking(true);
        QtPastePicClass->setFocusPolicy(Qt::WheelFocus);
        QtPastePicClass->setAcceptDrops(true);
        QtPastePicClass->setAutoFillBackground(true);
        QtPastePicClass->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        QtPastePicClass->setDocumentMode(true);
        QtPastePicClass->setDockNestingEnabled(true);
        QtPastePicClass->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(QtPastePicClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        source_pic_show = new QScrollArea(centralWidget);
        source_pic_show->setObjectName(QStringLiteral("source_pic_show"));
        source_pic_show->setGeometry(QRect(600, 50, 250, 188));
        source_pic_show->setWidgetResizable(false);
        source_pic_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(10, 39, 229, 109));
        source_pic_show->setWidget(scrollAreaWidgetContents);
        target_pic_show = new QScrollArea(centralWidget);
        target_pic_show->setObjectName(QStringLiteral("target_pic_show"));
        target_pic_show->setGeometry(QRect(600, 300, 250, 188));
        target_pic_show->setWidgetResizable(false);
        target_pic_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(10, 49, 229, 89));
        target_pic_show->setWidget(scrollAreaWidgetContents_2);
        source_pic_lable = new QLabel(centralWidget);
        source_pic_lable->setObjectName(QStringLiteral("source_pic_lable"));
        source_pic_lable->setGeometry(QRect(600, 20, 101, 21));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        source_pic_lable->setFont(font);
        target_pic_lable = new QLabel(centralWidget);
        target_pic_lable->setObjectName(QStringLiteral("target_pic_lable"));
        target_pic_lable->setGeometry(QRect(600, 270, 111, 21));
        target_pic_lable->setFont(font);
        source_pic_load_button = new QPushButton(centralWidget);
        source_pic_load_button->setObjectName(QStringLiteral("source_pic_load_button"));
        source_pic_load_button->setGeometry(QRect(730, 20, 121, 23));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        source_pic_load_button->setFont(font1);
        target_pic_load_button = new QPushButton(centralWidget);
        target_pic_load_button->setObjectName(QStringLiteral("target_pic_load_button"));
        target_pic_load_button->setGeometry(QRect(730, 270, 121, 23));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(10);
        target_pic_load_button->setFont(font2);
        LittleButton = new QPushButton(centralWidget);
        LittleButton->setObjectName(QStringLiteral("LittleButton"));
        LittleButton->setGeometry(QRect(881, 570, 250, 27));
        QFont font3;
        font3.setFamily(QStringLiteral("Times New Roman"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        LittleButton->setFont(font3);
        BigButton = new QPushButton(centralWidget);
        BigButton->setObjectName(QStringLiteral("BigButton"));
        BigButton->setGeometry(QRect(881, 535, 250, 27));
        BigButton->setFont(font3);
        UpButton = new QPushButton(centralWidget);
        UpButton->setObjectName(QStringLiteral("UpButton"));
        UpButton->setGeometry(QRect(881, 605, 250, 27));
        UpButton->setFont(font3);
        DownButton = new QPushButton(centralWidget);
        DownButton->setObjectName(QStringLiteral("DownButton"));
        DownButton->setGeometry(QRect(881, 640, 250, 27));
        DownButton->setFont(font3);
        RightButton = new QPushButton(centralWidget);
        RightButton->setObjectName(QStringLiteral("RightButton"));
        RightButton->setGeometry(QRect(881, 710, 250, 27));
        RightButton->setFont(font3);
        LiftButton = new QPushButton(centralWidget);
        LiftButton->setObjectName(QStringLiteral("LiftButton"));
        LiftButton->setGeometry(QRect(881, 675, 250, 27));
        LiftButton->setFont(font3);
        source_mask_load_button = new QPushButton(centralWidget);
        source_mask_load_button->setObjectName(QStringLiteral("source_mask_load_button"));
        source_mask_load_button->setGeometry(QRect(1010, 20, 121, 23));
        source_mask_load_button->setFont(font2);
        source_mask_show = new QScrollArea(centralWidget);
        source_mask_show->setObjectName(QStringLiteral("source_mask_show"));
        source_mask_show->setGeometry(QRect(880, 50, 250, 188));
        source_mask_show->setWidgetResizable(false);
        source_mask_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(10, 39, 229, 109));
        source_mask_show->setWidget(scrollAreaWidgetContents_3);
        target_mask_load_button = new QPushButton(centralWidget);
        target_mask_load_button->setObjectName(QStringLiteral("target_mask_load_button"));
        target_mask_load_button->setGeometry(QRect(1010, 270, 121, 23));
        target_mask_load_button->setFont(font2);
        source_pic_lable_2 = new QLabel(centralWidget);
        source_pic_lable_2->setObjectName(QStringLiteral("source_pic_lable_2"));
        source_pic_lable_2->setGeometry(QRect(880, 20, 131, 21));
        source_pic_lable_2->setFont(font);
        target_mask_show = new QScrollArea(centralWidget);
        target_mask_show->setObjectName(QStringLiteral("target_mask_show"));
        target_mask_show->setGeometry(QRect(880, 300, 250, 188));
        target_mask_show->setWidgetResizable(false);
        target_mask_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(10, 49, 229, 89));
        target_mask_show->setWidget(scrollAreaWidgetContents_4);
        target_mask_lable = new QLabel(centralWidget);
        target_mask_lable->setObjectName(QStringLiteral("target_mask_lable"));
        target_mask_lable->setGeometry(QRect(880, 270, 131, 21));
        target_mask_lable->setFont(font);
        target_depth_lable = new QLabel(centralWidget);
        target_depth_lable->setObjectName(QStringLiteral("target_depth_lable"));
        target_depth_lable->setGeometry(QRect(599, 522, 121, 21));
        target_depth_lable->setFont(font);
        target_depth_load_button = new QPushButton(centralWidget);
        target_depth_load_button->setObjectName(QStringLiteral("target_depth_load_button"));
        target_depth_load_button->setGeometry(QRect(730, 522, 121, 23));
        target_depth_load_button->setFont(font2);
        target_depth_show = new QScrollArea(centralWidget);
        target_depth_show->setObjectName(QStringLiteral("target_depth_show"));
        target_depth_show->setGeometry(QRect(600, 552, 250, 188));
        target_depth_show->setWidgetResizable(false);
        target_depth_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QStringLiteral("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(10, 49, 229, 89));
        target_depth_show->setWidget(scrollAreaWidgetContents_5);
        output_show = new QScrollArea(centralWidget);
        output_show->setObjectName(QStringLiteral("output_show"));
        output_show->setGeometry(QRect(20, 470, 550, 380));
        output_show->setLineWidth(0);
        output_show->setWidgetResizable(false);
        output_show->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QStringLiteral("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 548, 378));
        output_show->setWidget(scrollAreaWidgetContents_6);
        output = new QPushButton(centralWidget);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(880, 780, 250, 50));
        QFont font4;
        font4.setFamily(QStringLiteral("Times New Roman"));
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setWeight(75);
        output->setFont(font4);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 440, 91, 21));
        label->setFont(font);
        mask = new QPushButton(centralWidget);
        mask->setObjectName(QStringLiteral("mask"));
        mask->setGeometry(QRect(600, 780, 250, 50));
        mask->setFont(font4);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 20, 91, 21));
        label_2->setFont(font);
        QtPastePicClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtPastePicClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1155, 21));
        QtPastePicClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtPastePicClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtPastePicClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtPastePicClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtPastePicClass->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        source_pic_lable->setBuddy(source_pic_load_button);
        target_pic_lable->setBuddy(target_pic_load_button);
        source_pic_lable_2->setBuddy(source_pic_load_button);
        target_mask_lable->setBuddy(target_pic_load_button);
        target_depth_lable->setBuddy(target_pic_load_button);
#endif // QT_NO_SHORTCUT

        retranslateUi(QtPastePicClass);
        QObject::connect(LittleButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_little_clicked()));
        QObject::connect(UpButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_up_clicked()));
        QObject::connect(DownButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_down_clicked()));
        QObject::connect(LiftButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_left_clicked()));
        QObject::connect(RightButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_right_clicked()));
        QObject::connect(BigButton, SIGNAL(clicked()), QtPastePicClass, SLOT(on_big_clicked()));

        QMetaObject::connectSlotsByName(QtPastePicClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtPastePicClass)
    {
        QtPastePicClass->setWindowTitle(QApplication::translate("QtPastePicClass", "QtPastePic", nullptr));
        source_pic_lable->setText(QApplication::translate("QtPastePicClass", "Source Pic", nullptr));
        target_pic_lable->setText(QApplication::translate("QtPastePicClass", "Target Pic", nullptr));
        source_pic_load_button->setText(QApplication::translate("QtPastePicClass", "Source Pic Load ", nullptr));
        target_pic_load_button->setText(QApplication::translate("QtPastePicClass", "Target Pic Load ", nullptr));
        LittleButton->setText(QApplication::translate("QtPastePicClass", "Zoom Out", nullptr));
        BigButton->setText(QApplication::translate("QtPastePicClass", "Zoom In", nullptr));
        UpButton->setText(QApplication::translate("QtPastePicClass", "Up", nullptr));
        DownButton->setText(QApplication::translate("QtPastePicClass", "Down", nullptr));
        RightButton->setText(QApplication::translate("QtPastePicClass", "Right", nullptr));
        LiftButton->setText(QApplication::translate("QtPastePicClass", "Left", nullptr));
        source_mask_load_button->setText(QApplication::translate("QtPastePicClass", "Segment", nullptr));
        target_mask_load_button->setText(QApplication::translate("QtPastePicClass", "Segment", nullptr));
        source_pic_lable_2->setText(QApplication::translate("QtPastePicClass", "Source Mask", nullptr));
        target_mask_lable->setText(QApplication::translate("QtPastePicClass", "Target Mask", nullptr));
        target_depth_lable->setText(QApplication::translate("QtPastePicClass", "Target Depth", nullptr));
        target_depth_load_button->setText(QApplication::translate("QtPastePicClass", "Depth Estimation", nullptr));
        output->setText(QApplication::translate("QtPastePicClass", "Make Pic", nullptr));
        label->setText(QApplication::translate("QtPastePicClass", "Output", nullptr));
        mask->setText(QApplication::translate("QtPastePicClass", "Make Mask", nullptr));
        label_2->setText(QApplication::translate("QtPastePicClass", "Painter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtPastePicClass: public Ui_QtPastePicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPASTEPIC_H
