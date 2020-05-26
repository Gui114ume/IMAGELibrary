#ifndef DFTCALCULATOR_HPP
#define DFTCALCULATOR_HPP

#include "pixeltype.h"

#include <iostream>
#include <cstdlib>
#include <complex>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>

//N'HERITE PAS DE IPPMfilter volontairement
//c'est une classe standalone, sinon on allait casser toute l'archi du code
//Le probleme etant que le ressultat de la DFT donne des complexes


class PPMFilterDFT
{
public:
    PPMFilterDFT() {};
    ~PPMFilterDFT(){};

    void applyDFT(PPMpicture& picture_in,
                  PPMpictureDFT& picture_out);

    void applyDFT(PGMpicture& picture_in,
                  PGMpictureDFT& picture_out);


    //QU'est-ce que ça fout là en fait ????
    void save(PPMpictureDFT& picture,
              QString& filename); //à implementer

    void save(PGMpictureDFT& picture,
              QString& filename); //à implementer

private:
    //compute DFT with naive algorithm (for PGM file)
    std::complex<double> computeNewPixelPGM(QVector<quint32>&   picture_in,
                                             quint32&          u, // pixel_index_i
                                             quint32&          v, // pixel_index_j
                                             quint32&          nb_colonnes,
                                             quint32&          nb_lignes)
    {
        std::complex<double> grayscale_result;
        double reel = 0;
        double imaginaire = 0;

        for(quint32 i = 0 ; i < nb_lignes ; i++)
        {
            for(quint32 j = 0 ;  j < nb_colonnes ; j++)
            {
                reel += picture_in[i * nb_colonnes + j] * cos(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );
                imaginaire -= picture_in[i * nb_colonnes + j] * sin(2 * M_PI * ( ( (double)u * (double)i / (double)nb_lignes) + ( (double)v * (double)j / (double)nb_colonnes) ) );
            }
        }

        grayscale_result.imag(imaginaire);
        grayscale_result.real(reel);
        return grayscale_result;
    }

    //compute the DFT with naive algorithm (for PPM file)
    pixel_complexe computeNewPixelPPM(QVector<pixel>&   picture_in,
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


//apply DFT for PPM file
void PPMFilterDFT::applyDFT(PPMpicture &picture_in,
                            PPMpictureDFT &picture_out)
{
    //calcul de la DFT de l'image "picture_in" et l'ecrit dans picture_out
    for(quint32 u = 0 ; u < picture_in.width ; u++)
    {
        for(quint32 v = 0 ; v < picture_in.length ; v++)
        {
                picture_out.picture.push_back( computeNewPixelPPM(picture_in.picture,
                                                              u,
                                                              v,
                                                              picture_in.width,
                                                              picture_in.length));
                std::cout << "u : "<< u << "  v : " << v <<std::endl;;
        }
    }
}

//apply DFT for PGM file
void PPMFilterDFT::applyDFT(PGMpicture &picture_in,
                            PGMpictureDFT &picture_out)
{
    for(quint32 u = 0 ; u < picture_in.width ; u++)
    {
        for(quint32 v = 0 ; v < picture_in.length ; v++)
        {
                picture_out.picture.push_back( computeNewPixelPGM(picture_in.picture,
                                                                  u,
                                                                  v,
                                                                  picture_in.width,
                                                                  picture_in.length));
                std::cout << "u : "<< u << "  v : " << v <<std::endl;
        }
    }
}

void PPMFilterDFT::save(PPMpictureDFT &picture, QString &filename)
{
    //ecrire comme un ppm normal mais avec partie reel et partie imaginaire pour chaque RGB
    std::cout << "pas fait" << std::endl;
}

void PPMFilterDFT::save(PGMpictureDFT &picture, QString &filename)
{
       //ecrire la DFT dans un fichier de la meme maniere qu'un PGM sauf que l'on ecrit partie reel/ partie imagianire au lieu
       // du niveau de gris
    std::cout << "pas fait" << std::endl;
}

#endif
