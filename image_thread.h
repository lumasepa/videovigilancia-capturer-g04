#ifndef IMAGE_THREAD_H
#define IMAGE_THREAD_H

#include "cvmatandqimage.h"
#include <opencv2/opencv.hpp>

typedef std::vector<cv::Mat> ImagesType;
typedef std::vector<std::vector<cv::Point> > ContoursType;

class Image_Thread : public QObject
{
    Q_OBJECT

    signals:
        // Señal emitida cuando el frame ha sido procesado
        void Mandar_imagen(const QImage &image,const QVector<QRect> &VRect);

    public slots:
        // Slot para procesar la imagen
        void Procesador_imagen(const QImage &image);
    public:
        Image_Thread();

private:
        cv::BackgroundSubtractorMOG2 *backgroundSubtractor;
        cv::Mat foregroundMask;
        QVector<QRect> VRect;
};
#endif // IMAGE_THREAD_H
