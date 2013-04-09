/********************************************************************************
** Form generated from reading UI file 'imageviewerwindow.ui'
**
** Created: Tue Apr 9 18:01:15 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWERWINDOW_H
#define UI_IMAGEVIEWERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewerWindow
{
public:
    QAction *action_Abrir;
    QAction *action_Salir;
    QWidget *centralWidget;
    QLabel *Imagen;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtSalir;
    QMenuBar *menuBar;
    QMenu *menu_Archivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageViewerWindow)
    {
        if (ImageViewerWindow->objectName().isEmpty())
            ImageViewerWindow->setObjectName(QString::fromUtf8("ImageViewerWindow"));
        ImageViewerWindow->resize(400, 300);
        action_Abrir = new QAction(ImageViewerWindow);
        action_Abrir->setObjectName(QString::fromUtf8("action_Abrir"));
        action_Salir = new QAction(ImageViewerWindow);
        action_Salir->setObjectName(QString::fromUtf8("action_Salir"));
        centralWidget = new QWidget(ImageViewerWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        Imagen = new QLabel(centralWidget);
        Imagen->setObjectName(QString::fromUtf8("Imagen"));
        Imagen->setGeometry(QRect(10, 0, 371, 191));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Imagen->sizePolicy().hasHeightForWidth());
        Imagen->setSizePolicy(sizePolicy1);
        Imagen->setScaledContents(true);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 209, 381, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtSalir = new QPushButton(horizontalLayoutWidget);
        BtSalir->setObjectName(QString::fromUtf8("BtSalir"));

        horizontalLayout->addWidget(BtSalir);

        ImageViewerWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageViewerWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        menu_Archivo = new QMenu(menuBar);
        menu_Archivo->setObjectName(QString::fromUtf8("menu_Archivo"));
        ImageViewerWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ImageViewerWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageViewerWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ImageViewerWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Archivo->menuAction());
        menu_Archivo->addAction(action_Abrir);
        menu_Archivo->addAction(action_Salir);

        retranslateUi(ImageViewerWindow);

        QMetaObject::connectSlotsByName(ImageViewerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewerWindow)
    {
        ImageViewerWindow->setWindowTitle(QApplication::translate("ImageViewerWindow", "Cliente", 0, QApplication::UnicodeUTF8));
        action_Abrir->setText(QApplication::translate("ImageViewerWindow", "&Abrir", 0, QApplication::UnicodeUTF8));
        action_Salir->setText(QApplication::translate("ImageViewerWindow", "&Salir", 0, QApplication::UnicodeUTF8));
        Imagen->setText(QApplication::translate("ImageViewerWindow", "label", 0, QApplication::UnicodeUTF8));
        BtSalir->setText(QApplication::translate("ImageViewerWindow", "&Salir", 0, QApplication::UnicodeUTF8));
        menu_Archivo->setTitle(QApplication::translate("ImageViewerWindow", "&Archivo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerWindow: public Ui_ImageViewerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWERWINDOW_H
