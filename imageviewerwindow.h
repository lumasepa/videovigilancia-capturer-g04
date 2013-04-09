#ifndef IMAGEVIEWERWINDOW_H
#define IMAGEVIEWERWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QThread>
#include <string>

#include "sslserver.h"

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

private slots:
    void on_BtSalir_clicked();
    void on_action_Salir_triggered();
    void deserilaize(const std::string &);

private:
    // Funcion que se llama cuando la imagen esta deserializada
    void Pintar_Imagen(const QImage &image,const QVector<QRect> &VRect);
    sslserver server;
    Ui::ImageViewerWindow *ui;
};



#endif // IMAGEVIEWERWINDOW_H
