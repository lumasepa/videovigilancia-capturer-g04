#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"

#include <QFileDialog>

#include <QMovie>

#include <QDebug>

#include <QPixmap>
#include <QImage>
#include <QPainter>

#include <QSettings>

#include "protocol.pb.h"



ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);
    // Registra QVector<QRect> como tipo en qt para reconocerlo al hacer connect
    qRegisterMetaType< QVector<QRect> >("QVector<QRect>");

    QObject::connect(&server, SIGNAL(received(const std::string &)),
                     this, SLOT(deserilaize(const std::string &)));
    //CONFIGURACION DEL SOCKET USANDO QSETTINGS
        // Creamos el objeto de acceso a archivo datos
            QSettings config("config", QSettings::IniFormat);
            server.port = config.value("puerto", "").toInt();
            server.key = config.value("key", "").toString();
            server.certificate = config.value("cert", "").toString();
   //FIN DE CONFIGURACIÓN DEL SERVER.

    server.listen();

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

void ImageViewerWindow::Pintar_Imagen(const QImage &image,const QVector<QRect> &VRect)
{
    //recive la imagen y la muestra
    qDebug() << "Mostrando imagen";
    QPixmap img_pix;
    // Pasa la imagen a Qpixmap para mostrarla en el label y la muestra*/
    img_pix.convertFromImage(image);
    ui->Imagen->setPixmap(img_pix);
}

void ImageViewerWindow::deserilaize(const std::string & buffer)
{
    paquete msg;
    msg.ParseFromString(buffer);

    QImage imagen;
    imagen.loadFromData((const uchar *)msg.img().c_str(), msg.img().size(), "jpeg");

    QVector<QRect> cuadros;
    for(int i = 0; i < msg.recta_size(); ++i)
    {
        QRect recta(msg.recta(i).x(), msg.recta(i).y(), msg.recta(i).width(), msg.recta(i).height());
        cuadros.push_back(recta);
    }

    Pintar_Imagen(imagen,cuadros);
}


