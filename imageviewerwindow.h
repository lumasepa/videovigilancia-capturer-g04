#ifndef IMAGEVIEWERWINDOW_H
#define IMAGEVIEWERWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QThread>
#include <QtNetwork>

#include "image_thread.h"

// Definimos algunos tipos para que el código se lea mejor
typedef std::vector<cv::Mat> ImagesType;
typedef std::vector<std::vector<cv::Point> > ContoursType;


namespace Ui {
class ImageViewerWindow;
}


class ImageViewerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImageViewerWindow(QWidget *parent = 0);
    ~ImageViewerWindow();
signals:
    void Procesar_Imagen(const QImage &image);

private slots:
    void on_BtSalir_clicked();

    void on_action_Salir_triggered();

    void on_action_Abrir_triggered();

    void on_movie_updated(const QRect&);
    // Slot que se llama cuando la imagen ya ha sido procesada
    void Pintar_Imagen(const QImage &image,const QVector<QRect> &VRect);
    //slot que se llama cuando el socket esta preparado
    void socket_ready();
    void socket_down();
private:
    QThread workingThread_;
    Image_Thread imageProcesor_;
    Ui::ImageViewerWindow *ui;
    QMovie video;
    int puerto;
    QString ip;
    QSslSocket * socket;
};



#endif // IMAGEVIEWERWINDOW_H
