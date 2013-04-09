/********************************************************************************
** Form generated from reading UI file 'imageviewerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWERWINDOW_H
#define UI_IMAGEVIEWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

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
            ImageViewerWindow->setObjectName(QStringLiteral("ImageViewerWindow"));
        ImageViewerWindow->resize(400, 300);
        action_Abrir = new QAction(ImageViewerWindow);
        action_Abrir->setObjectName(QStringLiteral("action_Abrir"));
        action_Salir = new QAction(ImageViewerWindow);
        action_Salir->setObjectName(QStringLiteral("action_Salir"));
        centralWidget = new QWidget(ImageViewerWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        Imagen = new QLabel(centralWidget);
        Imagen->setObjectName(QStringLiteral("Imagen"));
        Imagen->setGeometry(QRect(10, 0, 371, 191));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Imagen->sizePolicy().hasHeightForWidth());
        Imagen->setSizePolicy(sizePolicy1);
        Imagen->setScaledContents(true);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 209, 381, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtSalir = new QPushButton(horizontalLayoutWidget);
        BtSalir->setObjectName(QStringLiteral("BtSalir"));

        horizontalLayout->addWidget(BtSalir);

        ImageViewerWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageViewerWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menu_Archivo = new QMenu(menuBar);
        menu_Archivo->setObjectName(QStringLiteral("menu_Archivo"));
        ImageViewerWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageViewerWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageViewerWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageViewerWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Archivo->menuAction());
        menu_Archivo->addAction(action_Abrir);
        menu_Archivo->addAction(action_Salir);

        retranslateUi(ImageViewerWindow);

        QMetaObject::connectSlotsByName(ImageViewerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewerWindow)
    {
        ImageViewerWindow->setWindowTitle(QApplication::translate("ImageViewerWindow", "ImageViewerWindow", 0));
        action_Abrir->setText(QApplication::translate("ImageViewerWindow", "&Abrir", 0));
        action_Salir->setText(QApplication::translate("ImageViewerWindow", "&Salir", 0));
        Imagen->setText(QApplication::translate("ImageViewerWindow", "label", 0));
        BtSalir->setText(QApplication::translate("ImageViewerWindow", "&Salir", 0));
        menu_Archivo->setTitle(QApplication::translate("ImageViewerWindow", "&Archivo", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerWindow: public Ui_ImageViewerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWERWINDOW_H
