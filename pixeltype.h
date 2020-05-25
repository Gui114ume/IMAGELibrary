#ifndef PIXELTYPE_H
#define PIXELTYPE_H

#include <QString>
#include <QVector>

#include <complex>

//each color has value comprise in [0,255]
struct pixel
{
    qint32 R; //Red
    qint32 G; //Green
    qint32 B; //Blue
};


struct PPMpicture
{
    QString PPMformat; // P3 -> ASCII PPM
    quint32 length;
    quint32 width;
    QVector<pixel> picture;
};

struct pixel_complexe
{
    std::complex<double> R; //Red
    std::complex<double> G; //Green
    std::complex<double> B; //Blue
};


struct PPMpictureDFT
{
    QString PPMformat; // P3 -> ASCII PPM
    quint32 length;
    quint32 width;
    QVector<pixel_complexe> picture;
};




#endif
