#ifndef DFTCALCULATOR_HPP
#define DFTCALCULATOR_HPP

#include "pixeltype.h"
#include "IDFTCalculator.hpp"

#include <iostream>
#include <cstdlib>
#include <complex>

#include <QtMath>
#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>

class DFTCalculator : public IDFTCalculator
{
public:
    DFTCalculator() {};
    ~DFTCalculator(){};

    void computeDFT(PGMpicture& picture_in,
                    PGMpictureDFT& picture_out) override;

    void computeInvDFT(PGMpictureDFT &picture_in,
                       PGMpicture &picture_out) override;

    void save(PGMpictureDFT& picture,
              QString& filename); //à implementer

private:
    //compute DFT with naive algorithm (for PGM file)
    std::complex<double> computeNewPixelPGMDFT(QVector<quint32>&   picture_in,
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

    quint32 computeNewPixelPGMinvDFT(QVector<std::complex<double>>&   picture_in,
                                     quint32&          x, // pixel_index_i
                                     quint32&          y, // pixel_index_j
                                     quint32&          nb_colonnes,
                                     quint32&          nb_lignes)
    {
        double tmp_result = 0;
        quint32 grayscale_result = 0;

        for(quint32 i = 0 ; i < nb_lignes ; i++)
        {
            for(quint32 j = 0 ;  j < nb_colonnes ; j++)
            {
                tmp_result += (picture_in[i * nb_colonnes + j].real() * cos(2 * M_PI * ( ( (double)x * (double)i / (double)nb_lignes) + ( (double)y * (double)j / (double)nb_colonnes) ) )
                        - picture_in[i * nb_colonnes + j].imag() * sin(2 * M_PI * ( ( (double)x * (double)i / (double)nb_lignes) + ( (double)y * (double)j / (double)nb_colonnes) ) ));
            }
        }
        tmp_result = tmp_result / (nb_lignes * nb_colonnes);
        grayscale_result = static_cast<quint32>(tmp_result);
        return grayscale_result;
    }
};

//apply DFT for PGM file
void DFTCalculator::computeDFT(PGMpicture &picture_in,
                               PGMpictureDFT &picture_out)
{
    for(quint32 u = 0 ; u < picture_in.width ; u++)
    {
        for(quint32 v = 0 ; v < picture_in.length ; v++)
        {
                picture_out.picture.push_back( computeNewPixelPGMDFT(picture_in.picture,
                                                                  u,
                                                                  v,
                                                                  picture_in.width,
                                                                  picture_in.length));
                std::cout << "u : "<< u << "  v : " << v <<std::endl;
                std::cout << picture_out.picture.last() << std::endl;
        }
    }
}

void DFTCalculator::computeInvDFT(PGMpictureDFT &picture_in, PGMpicture &picture_out)
{
    for(quint32 u = 0 ; u < picture_in.width ; u++)
    {
        for(quint32 v = 0 ; v < picture_in.length ; v++)
        {
                picture_out.picture.push_back( computeNewPixelPGMinvDFT(picture_in.picture,
                                                                  u,
                                                                  v,
                                                                  picture_in.width,
                                                                  picture_in.length));
                std::cout << "u : "<< u << "  v : " << v <<std::endl;
                std::cout << picture_out.picture.last() << std::endl;
        }
    }
}

void DFTCalculator::save(PGMpictureDFT &picture, QString &filename)
{
       //ecrire la DFT dans un fichier de la meme maniere qu'un PGM sauf que l'on ecrit partie reel/ partie imagianire au lieu
       // du niveau de gris
    std::cout << "pas fait" << std::endl;
}

#endif
