#ifndef PPMFILTERBLUR_H
#define PPMFILTERBLUR_H

#include "IPPMFilter.hpp"

#include <iostream>
#include <cstdlib>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PPMFilterBlur : public IPPMFilter
{
public:
    PPMFilterBlur() {};
    virtual ~PPMFilterBlur(){};

    virtual void apply(PPMpicture& picture_in,
                       PPMpicture& picture_out) override;

private:
    QVector<double> BoxBlurMatrix= {1/9.f, 1/9.f, 1/9.f,
                                    1/9.f, 1/9.f, 1/9.f,
                                    1/9.f, 1/9.f, 1/9.f};

    pixel computeNewPixel(QVector<double>&  BoxBlurMatrix,
                          QVector<pixel>&   picture_in,
                          quint32&          pixel_index_i,
                          quint32&          pixel_index_j,
                          quint32&          nb_colonnes)
    {
        pixel pixel_result;
//application des filtre de sobels en x et y, sur chacun des R, G, B, puis renvoie le pixel sqrt(Fx^2 + Fy^2)
        QVector<double> tmp_pixel(3);


        tmp_pixel[0] = BoxBlurMatrix[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].R +
                       BoxBlurMatrix[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].R +
                       BoxBlurMatrix[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].R +
                       BoxBlurMatrix[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].R +
                       BoxBlurMatrix[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].R +
                       BoxBlurMatrix[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].R +
                       BoxBlurMatrix[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].R +
                       BoxBlurMatrix[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].R +
                       BoxBlurMatrix[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].R;

        tmp_pixel[1] = BoxBlurMatrix[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].G +
                       BoxBlurMatrix[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].G +
                       BoxBlurMatrix[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].G +
                       BoxBlurMatrix[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].G +
                       BoxBlurMatrix[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].G +
                       BoxBlurMatrix[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].G +
                       BoxBlurMatrix[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].G +
                       BoxBlurMatrix[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].G +
                       BoxBlurMatrix[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].G;

        tmp_pixel[2] = BoxBlurMatrix[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].B +
                       BoxBlurMatrix[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].B +
                       BoxBlurMatrix[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].B +
                       BoxBlurMatrix[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].B +
                       BoxBlurMatrix[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].B +
                       BoxBlurMatrix[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].B +
                       BoxBlurMatrix[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].B +
                       BoxBlurMatrix[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].B +
                       BoxBlurMatrix[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].B;

        pixel_result.R = static_cast<quint32>(tmp_pixel[0])%256;
        pixel_result.G = static_cast<quint32>(tmp_pixel[1])%256;
        pixel_result.B = static_cast<quint32>(tmp_pixel[2])%256;
        return pixel_result;
    }

};

#endif

void PPMFilterBlur::apply(PPMpicture& picture_in,
                          PPMpicture& picture_out)
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
            pixel tmp_pix =  this->computeNewPixel(this->BoxBlurMatrix,
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
