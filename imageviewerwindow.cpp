#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qmessagebox.h"
#include "qimagereader.h"
#include "qpixmap.h"
#include <QMovie>
#include <QDebug>
#include <QImage>

#include <QWaitCondition>
#include <QMutex>

ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);

    QObject::connect(&video,SIGNAL(updated(const QRect&)),this,SLOT(on_movie_updated(const QRect&)));
    // Pasar la petición de procesar el frame
    QObject::connect(this, SIGNAL(img_ProcesorRequest(const QImage &)),
        &imageProcesor_, SLOT(process_image(const QImage &)));

    // Ser notificado cuando el frame ha sido procesado
    QObject::connect(&imageProcesor_, SIGNAL(send_image(const QImage &)),
       this, SLOT(img_Procesed(const QImage &)));

    // Migrar la instancia de imageProcesor al hilo de trabajo
    imageProcesor_.moveToThread(&workingThread_);

    // Iniciar el hilo de trabajo
    workingThread_.start();
}

ImageViewerWindow::~ImageViewerWindow()
{
    // Le decimos al bucle de mensajes del hilo que se detenga
    workingThread_.quit();
    // Ahora esperamos a que el hilo de trabajo termine
    workingThread_.wait();
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
        // Para el video
        video.stop();

        // Pone como nuevo video fileName
        video.setFileName(fileName);

        // Inicia el video
        video.start();
        qDebug() << "Inicio de video";
    }
}

void ImageViewerWindow::on_movie_updated(const QRect&)
{
    //ui->Imagen->setPixmap(video.currentPixmap());
    //le manda al hilo la imagen para procesarla
    QImage img = video.currentImage();
    qDebug() << "emitiendo señal de intento de proceso";
    emit img_ProcesorRequest(img);
}

void ImageViewerWindow::img_Procesed(const QImage &image)
{
    //recive la imagen del hilo ya procesada y la muestra
    qDebug() << "Mostrando imagen";
    QPixmap img;
    img.convertFromImage(image);
    ui->Imagen->setPixmap(img);
}

void Image_Thread::process_image(const QImage &image)
{
    //procesa la imagen
    qDebug() << "Procesando la imagen";

    //manda la imagen ya procesada al hilo principal
    emit send_image(image);
}

