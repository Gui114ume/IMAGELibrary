#ifndef GRAYSCALECONVERTE_HPP
#define GRAYSCALECONVERTE_HPP

#include "pixeltype.h"

#include <QtDebug>
#include <QtMath>

#include <QVector>
#include <QFile>
#include <QString>

#include <iostream>
#include <cstdlib>


class GrayscaleConverter
{
public:
    GrayscaleConverter() {};
    ~GrayscaleConverter() {};


    void apply(PPMpicture& picture_in,
               QVector<quint32>& vector_out);

    void save(QVector<quint32>& vector_gray_img,
              quint32& width,
              quint32& length,
              QString& filename);

private:
    quint32 computeNewPixel(pixel& pixel_in);

};


void GrayscaleConverter::apply(PPMpicture &picture_in,
                               QVector<quint32> &vector_out) //il faut rmeplacer le type par PGMpicture
{
   for(auto& i : picture_in.picture)
   {
        vector_out.push_back(this->computeNewPixel(i));
   }
}

//on doit utiliser un PPMGrayscalePicture
void GrayscaleConverter::save(QVector<quint32> &vector_gray_img,
                              quint32& width,
                              quint32& length,
                              QString &filename)
{
//comment sont stockes les images niveaux de gris ?
    //stocker P2
    //stocker  width/length
    //stocker la valeur max
    //stcoker en ligne comme pour ppm, sans trop ecrire à chaque ligne
    //Etape 1 : Open the  file
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
         {
             qDebug() << filename <<" badly opened, in savePicture" << endl;
             exit(-1); //utiliser exception ?
         }
    QTextStream outfile(&fileHandle);
    //Etape 2 : Write Format (P3 here)
    outfile << "P2" << endl;

    //Etape 3 : Write width length
    outfile << QString::number(width) << " " << QString::number(length) << endl;

    //Etape 4 : Write max value of pixel (255 here)
    outfile << QString::number(255) << endl;

    //Etape 5 : Write the pixels, not more than 70 (?) characters per line ! (here is the difficulty, how to do this ? -> Consider the worst case : each color need 3 characters to be written )
    //D'apres l'image test, on peut ecrire plus que 70 caracteres...
    quint32 n = 0;
    for(auto& pix : vector_gray_img)
    {
        outfile << QString::number(pix) << " ";
        ++n;
        if(n == 5)
        {
            outfile << endl;
            n = 0;
        }

    }
    fileHandle.close();
}

quint32 GrayscaleConverter::computeNewPixel(pixel &pixel_in)
{
    double pixel_result;

    pixel_result = (double)pixel_in.R * 0.299 + (double)pixel_in.G * 0.587+ (double)pixel_in.B * 0.114;
    return static_cast<quint32>(pixel_result);
}


#endif
