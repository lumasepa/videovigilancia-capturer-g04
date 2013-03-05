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

#include <QPainter>

#include<opencv2/opencv.hpp>

#include <QWaitCondition>
#include <QMutex>


ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);

    qRegisterMetaType< QVector<QRect> >("QVector<QRect>");

    QObject::connect(&video,SIGNAL(updated(const QRect&)),this,SLOT(on_movie_updated(const QRect&)));
    // Pasar la petición de procesar el frame
    QObject::connect(this, SIGNAL(img_ProcesorRequest(const QImage &)),
        &imageProcesor_, SLOT(process_image(const QImage &)));

    // Ser notificado cuando el frame ha sido procesado
    QObject::connect(&imageProcesor_, SIGNAL(send_image(const QImage &,const QVector<QRect> &)),
       this, SLOT(img_Procesed(const QImage &,const QVector<QRect> &)));

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
        //video.setSpeed(25);

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

void ImageViewerWindow::img_Procesed(const QImage &image,const QVector<QRect> &VRect)
{
    //recive la imagen del hilo ya procesada y la muestra
    qDebug() << "Mostrando imagen";
    QPixmap img;
    QImage imagen = image;
    QPainter pintura(&imagen);
    QColor verde(0,255,0,255);
    pintura.setPen(verde);

    pintura.drawRects(VRect);
    //qDebug() <<"main "<<VRect[0].left()<<" "<<VRect[0].top()<< " "<<VRect[0].width()<<" "<<VRect[0].height();
    //img = pintura.
    img.convertFromImage(imagen);
    ui->Imagen->setPixmap(img);
}

void Image_Thread::process_image(const QImage &image)
{
    //procesa la imagen
    qDebug() << "Procesando la imagen";

    cv::Mat img = QtOcv::image2Mat(image);
    // Instancia de la clase del sustractor de fondo
    // cv::BackgroundSubtractorMOG2 backgroundSubtractor(500,16,false);
    //cv::BackgroundSubtractorMOG2 backgroundSubtractor;
    // backgroundSubtractor.set("nmixtures",3);
    // Desactivar la detección de sombras
    //backgroundSubtractor.bShadowDetection = false;
    // Sustracción del fondo:
    //  1. El objeto sustractor compara la imagen en i con su
    //     estimación del fondo y devuelve en foregroundMask una
    //     máscara (imagen binaria) con un 1 en los píxeles de
    //     primer plano.
    //  2. El objeto sustractor actualiza su estimación del fondo
    //     usando la imagen en i.
    (*backgroundSubtractor)(img, foregroundMask);
    // Operaciones morfolóficas para eliminar las regiones de
    // pequeño tamaño. Erode() las encoge y dilate() las vuelve a
    // agrandar.
    cv::erode(foregroundMask, foregroundMask, cv::Mat());
    cv::dilate(foregroundMask, foregroundMask, cv::Mat());
    // Obtener los contornos que bordean las regiones externas
    // (CV_RETR_EXTERNAL) encontradas. Cada contorno es un vector
    // de puntos y se devuelve uno por región en la máscara.
    ContoursType contours;
    cv::findContours(foregroundMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    //Pasa el vector de contornos(rect) a vector de Qrect
   QVector<QRect> VRect;
   VRect.clear();
   for(unsigned i = 0;i< contours.size();i++)
   {
        cv::Rect recta = cv::boundingRect(contours[i]);
        QRect qrecta(recta.x,recta.y,recta.width,recta.height);
        qDebug() <<"hilo"<<recta.x<< " "<<recta.y<<" "<<recta.width<<" "<<recta.height;
        VRect.push_back(qrecta);
   }
    qDebug() << "Imagen procesada";
    //manda la imagen ya procesada al hilo principal
    emit send_image(image,VRect);
}

