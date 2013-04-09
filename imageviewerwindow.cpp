#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"
#include <QFileDialog>
#include <QMovie>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <QIODevice>
#include "protocol.pb.h"
#include <ctime>




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
       this, SLOT(envio_paquete(const QImage &,const QVector<QRect> &)));

    // Migrar la instancia de imageProcesor al hilo de trabajo
    imageProcesor_.moveToThread(&workingThread_);

    // Iniciar el hilo de trabajo
    workingThread_.start();

    //CONFIGURACION DEL SOCKET USANDO QSETTINGS
    // Creamos el objeto de acceso a archivo datos
        QSettings config("config", QSettings::IniFormat);
        puerto = config.value("puerto", "").toInt();
        ip = config.value("ip", "").toString();
        devicename = config.value("nombre", "").toString();
        qDebug() << puerto << " " << ip << " " << devicename;
        socket_up = false;//El socket desconectado por defecto antes de crearlo.
        socket = new QSslSocket(this); //Creamos una instancia del socket ssl.

        QObject::connect(socket, SIGNAL(encrypted()), this, SLOT(socket_ready()));
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(socket_down()));
        QObject::connect(socket, SIGNAL(sslErrors(const QList<QSslError>&)),this, SLOT(socket_ssl_error(const QList<QSslError>&)));
        QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socketError()));

        socket->setProtocol(QSsl::SslV3);
        socket->connectToHostEncrypted(ip,puerto);
        socket->ignoreSslErrors();
   //FIN DE CONFIGURACIÓN DEL SOCKET.

}

ImageViewerWindow::~ImageViewerWindow()
{
    // Le decimos al bucle de mensajes del hilo que se detenga
    imageProcesor_.set_cierre(true);
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

void ImageViewerWindow::envio_paquete(const QImage &image,const QVector<QRect> &VRect)
{
    paquete msg;
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    image.save(&buffer, "jpeg");
    std::string img_string(buffer.buffer().data(), buffer.buffer().size());
    msg.set_img(img_string);

    msg.set_devicename(devicename.toStdString().c_str());

    time_t t1 = 0;
    time_t* pt1 = &t1;
    time(pt1);
    msg.set_timestamp(t1);

    for (int i=0;i<VRect.size();i++)
    {
        paquete_rect * r = msg.add_recta();
        r->set_x(VRect[i].x());
        r->set_y(VRect[i].y());
        r->set_width(VRect[i].width());
        r->set_height(VRect[i].height());
    }

    emit socket_write(msg.SerializeAsString());
}

void ImageViewerWindow::socket_ready()
{
    qDebug() << "Conexion del socket realizada";
    socket_up = true;
}

void ImageViewerWindow::socket_down()
{
    qDebug() << "Desconexion del socket realizada";
    socket_up = false;
}

void ImageViewerWindow::socketError()
{
  qDebug() << "Error de conexion de socket: " << socket->errorString();
  socket->close();
}

void ImageViewerWindow::socket_ssl_error(const QList<QSslError> &error)
{
    QString errorStrings;
    for(int i=0;i<error.size();++i)
      {
          errorStrings += error[i].errorString();
          errorStrings += '\n';
      }

      //Muestra que ha ocurrido un error de certificado y pregunta si desea continuar o no
      QMessageBox::StandardButton result = QMessageBox::question(this, "SSL Errors",
        QString("Han ocurrido los siguientes errores de certificación SSL:\n\n%1\n\nContinuar?").arg(errorStrings),
        QMessageBox::Yes|QMessageBox::No);
      if (result == QMessageBox::Yes)
      {
        socket->ignoreSslErrors();
      }
}

void ImageViewerWindow::socket_write(std::string msg)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        int64_t size = msg.size();
        socket->write((char*)&size,sizeof(size));
        socket->write(msg.c_str(),size);
        qDebug() << "Mensaje enviado";
    }
    else
    {
        qDebug() << "No se a podido enviar el mensaje";
    }

}



