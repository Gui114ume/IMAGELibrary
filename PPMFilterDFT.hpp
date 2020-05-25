#ifndef PPMFILTERDFT_HPP
#define PPMFILTERDFT_HPP

#include "pixeltype.h"

#include <iostream>
#include <cstdlib>
#include <complex>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>

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


class PPMFilterDFT
{
public:
    PPMFilterDFT() {};
    ~PPMFilterDFT(){};

    void applyDFT(PPMpicture& picture_in,
                  PPMpictureDFT& picture_out);

private:
    //compute the DFT with naive algorithme
    pixel_complexe computeNewPixel(QVector<pixel>&   picture_in,
                                   quint32&          u, // pixel_index_i
                                   quint32&          v, // pixel_index_j
                                   quint32&          nb_colonnes,
                                   quint32&          nb_lignes)
    {
        //Calcul de la DFT pour le pixel (pixel_index_i, pixel_index_j) = (u, v) sur chacun des canaux RGB.
        //renvoie un pixel complexe contenant RGB, chaque couleur est "complexe"
        pixel_complexe pixel_result;
        QVector<double> reel(3,0);
        QVector<double> imaginaire(3,0);

        for(quint32 i = 0 ; i < nb_lignes ; i++)
        {
            for(quint32 j = 0 ;  j < nb_colonnes ; j++)
            {
                reel[0] += picture_in[i * nb_colonnes + j].R * cos(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );
                imaginaire[0] -= picture_in[i * nb_colonnes + j].R * sin(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );

                reel[1] += picture_in[i * nb_colonnes + j].R * cos(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );
                imaginaire[1] -= picture_in[i * nb_colonnes + j].R * sin(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );

                reel[2] += picture_in[i * nb_colonnes + j].R * cos(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );
                imaginaire[2] -= picture_in[i * nb_colonnes + j].R * sin(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );

            }
        }
        pixel_result.R.imag(reel[0]);
        pixel_result.R.real(imaginaire[0]);

        pixel_result.G.imag(reel[1]);
        pixel_result.G.real(imaginaire[1]);

        pixel_result.B.imag(reel[2]);
        pixel_result.B.real(imaginaire[2]);
        return pixel_result;
    }
};



void PPMFilterDFT::applyDFT(PPMpicture &picture_in,
                            PPMpictureDFT &picture_out)
{
    //calcul de la DFT de l'image "picture_in" et l'ecrit dans picture_out
    for(quint32 u = 0 ; u < picture_in.width ; u++)
    {
        for(quint32 v = 0 ; v < picture_in.length ; v++)
        {
                picture_out.picture.push_back( computeNewPixel(picture_in.picture,
                                                              u,
                                                              v,
                                                              picture_in.width,
                                                              picture_in.length));
                std::cout << "u : "<< u << "  v : " << v <<std::endl;;
        }
    }
}

#endif
