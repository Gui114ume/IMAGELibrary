#ifndef PGMFILTERBLUR_HPP
#define PGMFILTERBLUR_HPP

#include "IPGMFilter.hpp"

#include <iostream>
#include <cstdlib>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PGMFilterBlur : public IPGMFilter
{
public:
    PGMFilterBlur() {};
    virtual ~PGMFilterBlur(){};

    virtual void apply(PGMpicture& picture_in,
                       PGMpicture& picture_out) override;

private:
    QVector<double> BoxBlurMatrix= {1/9.f, 1/9.f, 1/9.f,
                                    1/9.f, 1/9.f, 1/9.f,
                                    1/9.f, 1/9.f, 1/9.f};

    quint32 computeNewPixel(QVector<double>&  BoxBlurMatrix,
                          QVector<quint32>&   picture_in,
                          quint32&          pixel_index_i,
                          quint32&          pixel_index_j,
                          quint32&          nb_colonnes)
    {
        quint32 pixel_result;
//application des filtre de sobels en x et y, sur chacun des R, G, B, puis renvoie le pixel sqrt(Fx^2 + Fy^2)
        double tmp_pixel;
        tmp_pixel =    BoxBlurMatrix[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1] +
                       BoxBlurMatrix[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ] +
                       BoxBlurMatrix[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1] +
                       BoxBlurMatrix[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1] +
                       BoxBlurMatrix[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j] +
                       BoxBlurMatrix[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1] +
                       BoxBlurMatrix[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1] +
                       BoxBlurMatrix[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ] +
                       BoxBlurMatrix[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1];

        pixel_result = static_cast<quint32>(tmp_pixel);
        if(pixel_result > 255)
            pixel_result = 255;
        return pixel_result;
    }

};



void PGMFilterBlur::apply(PGMpicture& picture_in,
                          PGMpicture& picture_out)
{
    //push_back la premiere ligne qui reste identique
    for(quint32 j = 0 ; j < picture_in.width ; j++)
        picture_out.picture.push_back(picture_in.picture[0 * picture_in.width + j]);

    //balayage ligne par ligne de toute l'image
    for(quint32 pixel_index_i = 1 ;  pixel_index_i < picture_in.length - 1 ; pixel_index_i++)
    {
        //push_back le premier element de la ligne i
        picture_out.picture.push_back(picture_in.picture[pixel_index_i * picture_in.width + 0]);

        //calcul et push_back des nouveaux elements calcules pour chaque colonne de l'image
        for(quint32 pixel_index_j = 1 ; pixel_index_j < picture_in.width - 1 ; pixel_index_j++)
        {
            quint32 tmp_pix =  this->computeNewPixel(this->BoxBlurMatrix,
                                                   picture_in.picture,
                                                   pixel_index_i,
                                                   pixel_index_j,
                                                   picture_in.width);
            picture_out.picture.push_back(tmp_pix);
        }
        //push_back le dernier element de la ligne i
        picture_out.picture.push_back(picture_in.picture[ pixel_index_i * picture_in.width + ( picture_in.width - 1)]);
    }
    //push_back la derniere ligne qui reste identique
    for(quint32 j = 0 ; j < picture_in.width ; j++)
        picture_out.picture.push_back(picture_in.picture[ ( picture_in.length - 1 ) * picture_in.width + j]);

}
#endif //PGMFILTERBLUR_HPP
