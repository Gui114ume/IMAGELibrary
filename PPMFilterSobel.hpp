#ifndef PPMFILTERSOBEL_H
#define PPMFILTERSOBEL_H

#include "IPPMFilter.hpp"

#include <iostream>
#include <cstdlib>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PPMFilterSobel : public IPPMFilter
{
public:
    virtual ~PPMFilterSobel(){};
    PPMFilterSobel() {};

    virtual void apply(PPMpicture& picture_in,
                       PPMpicture& picture_out) override;

private:
    QVector<qint32> Filtre_x = {-1 ,0 ,1
                               ,-2 ,0 ,2
                               ,-1, 0, 1};

    QVector<qint32> Filtre_y = {-1, -2, 1
                               , 0,  0, 0
                               , 1,  2, 2};
    pixel computeNewPixel(QVector<qint32>&  Filtre_i,
                          QVector<qint32>&  Filtre_j,
                          QVector<pixel>&   picture_in,
                          quint32&          pixel_index_i,
                          quint32&          pixel_index_j,
                          quint32&          nb_colonnes)
    {
        pixel pixel_result;
//application des filtre de sobels en x et y, sur chacun des R, G, B, puis renvoie le pixel sqrt(Fx^2 + Fy^2)
        QVector<double> tmp_pixel_x(3);
        QVector<double> tmp_pixel_y(3);

        //pour R, G et B !
        for(int i = 0 ; i < 1 ; i++) // i < 3
        {
            //calcul Gx

            tmp_pixel_x[0] = Filtre_i[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_i[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].R +
                             Filtre_i[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].R +
                             Filtre_i[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_i[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].R +
                             Filtre_i[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].R +
                             Filtre_i[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_i[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].R +
                             Filtre_i[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].R;

            tmp_pixel_x[1] = Filtre_i[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_i[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].G +
                             Filtre_i[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].G +
                             Filtre_i[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_i[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].G +
                             Filtre_i[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].G +
                             Filtre_i[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_i[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].G +
                             Filtre_i[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].G;

            tmp_pixel_x[2] = Filtre_i[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_i[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].B +
                             Filtre_i[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].B +
                             Filtre_i[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_i[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].B +
                             Filtre_i[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].B +
                             Filtre_i[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_i[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].B +
                             Filtre_i[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].B;

            //calcul Gy


            tmp_pixel_y[0] = Filtre_j[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_j[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].R +
                             Filtre_j[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].R +
                             Filtre_j[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_j[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].R +
                             Filtre_j[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].R +
                             Filtre_j[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].R +
                             Filtre_j[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].R +
                             Filtre_j[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].R;

            tmp_pixel_y[1] = Filtre_j[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_j[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].G +
                             Filtre_j[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].G +
                             Filtre_j[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_j[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].G +
                             Filtre_j[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].G +
                             Filtre_j[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].G +
                             Filtre_j[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].G +
                             Filtre_j[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].G;

            tmp_pixel_y[2] = Filtre_j[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_j[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ].B +
                             Filtre_j[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1].B +
                             Filtre_j[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_j[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j].B +
                             Filtre_j[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1].B +
                             Filtre_j[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1].B +
                             Filtre_j[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ].B +
                             Filtre_j[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1].B;

        }
        pixel_result.R = sqrt(tmp_pixel_x[0] * tmp_pixel_x[0] + tmp_pixel_y[0] * tmp_pixel_y[0]);
        pixel_result.G = sqrt(tmp_pixel_x[1] * tmp_pixel_x[0] + tmp_pixel_y[1] * tmp_pixel_y[1]);
        pixel_result.B = sqrt(tmp_pixel_x[2] * tmp_pixel_x[0] + tmp_pixel_y[2] * tmp_pixel_y[2]);
        return pixel_result;
    }

};



void PPMFilterSobel::apply(PPMpicture& picture_in,
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
            pixel tmp_pix =  this->computeNewPixel(this->Filtre_x,
                                                   this->Filtre_y,
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
#endif // PPMFILTERSOBEL_H
