#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qmessagebox.h"
#include "qimagereader.h"
#include "qpixmap.h"
#include <QMovie>

#include <QWaitCondition>
#include <QMutex>

ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);

    QObject::connect(&video,SIGNAL(updated(const QRect&)),this,SLOT(on_movie_updated(const QRect&)));
}

ImageViewerWindow::~ImageViewerWindow()
{
    delete ui;
}

void ImageViewerWindow::on_BtSalir_clicked()
{
    qApp->quit();
}

void ImageViewerWindow::on_action_Salir_triggered()
{
    qApp->quit();
}

void ImageViewerWindow::on_action_Abrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QString(),tr("Video Files (*.mjpeg)"));

    if (!fileName.isEmpty())
    {
        video.stop();
        video.setFileName(fileName);
        video.start();

        QWaitCondition sleep;
        QMutex mutex;
        sleep.wait(&mutex,20000);

        /*QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"),tr("No se pudo abrir el archivo"));
            return;
        }

        QImageReader imgc(&file);

        QPixmap img = QPixmap::fromImageReader(&imgc);

        ui->Imagen->setPixmap(img);
        file.close();*/
    }
}

void ImageViewerWindow::on_movie_updated(const QRect&)
{
    ui->Imagen->setPixmap(video.currentPixmap());
}
