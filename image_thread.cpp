#include "image_thread.h"
#include <QDebug>

Image_Thread::Image_Thread()
{
    //crea un backgroundSubtractor y desactiva la detecccion de sombras
    backgroundSubtractor = new cv::BackgroundSubtractorMOG2(500,16,false);
    backgroundSubtractor->set("nmixtures",3);
    cierre = false;
}
void Image_Thread::set_cierre(const bool &x)
{
    cierre = x;
}

void Image_Thread::Procesador_imagen(const QImage &image)
{
    if(!cierre)
    {
        //procesa la imagen
        qDebug() << "Procesando la imagen";

        // Pasa la imagen de Qimage a cv::Mat para ser procesada por opencv
        cv::Mat img = QtOcv::image2Mat(image);

        // Sustracción del fondo:
        (*backgroundSubtractor)(img, foregroundMask);
        // Operaciones morfolóficas para eliminar las regiones de
        // pequeño tamaño. Erode() las encoge y dilate() las vuelve a
        // agrandar.
        cv::erode(foregroundMask, foregroundMask, cv::Mat(),cv::Point(-1,-1),3);
        cv::dilate(foregroundMask, foregroundMask, cv::Mat(),cv::Point(-1,-1),3);
        // Obtener los contornos que bordean las regiones externas
        // (CV_RETR_EXTERNAL) encontradas.
        ContoursType contours;
        cv::findContours(foregroundMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        //Pasa el vector de contornos(rect) a vector de Qrect
       VRect.clear();
       for (ContoursType::const_iterator i = contours.begin(); i < contours.end(); ++i)
       {
            cv::Rect recta = cv::boundingRect(*i);
            QRect qrecta(recta.x,recta.y,recta.width,recta.height);
            VRect.push_back(qrecta);
       }
        qDebug() << "Imagen procesada";
        //manda la imagen ya procesada al hilo principal
        emit Mandar_imagen(image,VRect);
    }
}
