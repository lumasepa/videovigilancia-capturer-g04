#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"

#include <QFileDialog>

#include <QMovie>

#include <QDebug>

#include <QPixmap>
#include <QImage>
#include <QPainter>

#include<opencv2/opencv.hpp>



ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);
    // Registra QVector<QRect> como tipo en qt para reconocerlo al hacer connect
    qRegisterMetaType< QVector<QRect> >("QVector<QRect>");
    // Capturar la imagen cuando cambia en el video
    QObject::connect(&video,SIGNAL(updated(const QRect&)),
                     this,SLOT(on_movie_updated(const QRect&)));

    // Pasar la petición de procesar el frame
    QObject::connect(this, SIGNAL(Procesar_Imagen(const QImage &)),
        &imageProcesor_, SLOT(Procesador_imagen(const QImage &)));

    // Ser notificado cuando el frame ha sido procesado
    QObject::connect(&imageProcesor_, SIGNAL(Mandar_imagen(const QImage &,const QVector<QRect> &)),
       this, SLOT(Pintar_Imagen(const QImage &,const QVector<QRect> &)));

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
    // Abre cuadro de dialogo para escoger archivo y guarda la ruta en filename
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QString(),tr("Video Files (*.mjpeg)"));

    if (!fileName.isEmpty())
    {
        // Para el video
        video.stop();
        //pone la velocidad de video a 10% sobre el normal para que no falle en el portatil
        video.setSpeed(10);
        // Pone como nuevo video fileName
        video.setFileName(fileName);
        // Inicia el video
        video.start();
        qDebug() << "Inicio de video";
    }
}

void ImageViewerWindow::on_movie_updated(const QRect&)
{;
    //le manda al hilo la imagen para procesarla
    QImage img = video.currentImage();
    qDebug() << "Mandando a procesar imagen";
    emit Procesar_Imagen(img);
}

void ImageViewerWindow::Pintar_Imagen(const QImage &image,const QVector<QRect> &VRect)
{
    //recive la imagen del hilo ya procesada y la muestra
    qDebug() << "Mostrando imagen";
    QPixmap img_pix;
    // Quita el const para poder pintar en la imagen
    QImage imagen = image;
    // Crea un Qpainter para pintar los rectangulos en la imagen
    QPainter pintura(&imagen);
    //Pone a rojo el color que se usa para pintar
    QColor rojo(255,0,0,255);
    pintura.setPen(rojo);
    // Dibuja los rectangulos en la imagen
    pintura.drawRects(VRect);
    // Pasa la imagen a Qpixmap para mostrarla en el label y la muestra
    img_pix.convertFromImage(imagen);
    ui->Imagen->setPixmap(img_pix);
}



