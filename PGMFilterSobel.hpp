#ifndef PGMFILTERSOBEL_H
#define PGMFILTERSOBEL_H

#include "IPGMFilter.hpp"

#include <iostream>
#include <cstdlib>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PGMFilterSobel : public IPGMFilter
{
public:
    virtual ~PGMFilterSobel(){};
    PGMFilterSobel() {};

    virtual void apply(PGMpicture& picture_in,
                       PGMpicture& picture_out) override;

private:
    QVector<qint32> Filtre_x = {-1 ,0 ,1
                               ,-2 ,0 ,2
                               ,-1, 0, 1};

    QVector<qint32> Filtre_y = {-1, -2, 1
                               , 0,  0, 0
                               , 1,  2, 2};
    quint32 computeNewPixel(QVector<qint32>&  Filtre_i,
                            QVector<qint32>&  Filtre_j,
                            QVector<quint32>&   picture_in,
                            quint32&          pixel_index_i,
                            quint32&          pixel_index_j,
                            quint32&          nb_colonnes)
    {
        quint32 pixel_result;
//application des filtre de sobels en x et y, sur chacun des R, G, B, puis renvoie le pixel sqrt(Fx^2 + Fy^2)
        double tmp_pixel_x;
        double tmp_pixel_y;

            //calcul Gx

            tmp_pixel_x    = Filtre_i[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1] +
                             Filtre_i[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ] +
                             Filtre_i[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1] +
                             Filtre_i[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1] +
                             Filtre_i[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j] +
                             Filtre_i[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1] +
                             Filtre_i[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1] +
                             Filtre_i[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ] +
                             Filtre_i[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1];

            //calcul Gy
            tmp_pixel_y = Filtre_j[0] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j - 1] +
                             Filtre_j[1] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j ] +
                             Filtre_j[2] * picture_in[ (pixel_index_i - 1) * nb_colonnes + pixel_index_j + 1] +
                             Filtre_j[3] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j - 1] +
                             Filtre_j[4] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j] +
                             Filtre_j[5] * picture_in[  pixel_index_i * nb_colonnes + pixel_index_j + 1] +
                             Filtre_j[6] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j - 1] +
                             Filtre_j[7] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j ] +
                             Filtre_j[8] * picture_in[ (pixel_index_i + 1) * nb_colonnes + pixel_index_j + 1];

        //needed in order to have pixel value less or equal to 255
        pixel_result = static_cast<quint32>(sqrt(tmp_pixel_x * tmp_pixel_x + tmp_pixel_y * tmp_pixel_y) );
        if(pixel_result > 255)
            pixel_result = 255;
        return pixel_result;
    };


};


void PGMFilterSobel::apply(PGMpicture &picture_in, PGMpicture &picture_out)
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
            quint32 tmp_pix =  this->computeNewPixel(this->Filtre_x,
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

#endif // PGMFILTERSOBEL_H
