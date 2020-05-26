#include <iostream>

#include "PPMProcessor.hpp"
#include "PGMProcessor.hpp"
#include "PPMFilterSobel.hpp"
#include "PGMFilterSobel.hpp"
#include "PGMFilterBlur.hpp"
#include "PPMFilterBlur.hpp"
#include "DFTCalculator.hpp"
#include "GrayscaleConverter.hpp"


#include "pixeltype.h"


int main(int argc, char** argv)
{
    PPMProcessor* ppmProcessor = new PPMProcessor();
    PGMProcessor* pgmProcessor = new PGMProcessor();
    PPMFilterSobel* filtre_sobel = new PPMFilterSobel();
    PPMFilterBlur* filtre_blur = new PPMFilterBlur();
    PPMFilterDFT* filtre_dft = new PPMFilterDFT;
    PGMFilterBlur* blurPGM = new PGMFilterBlur();
    GrayscaleConverter* g_converter = new GrayscaleConverter();

    PPMpicture picture;
    PPMpicture picture_out;
    PGMpictureDFT picture_dft;
    PGMpicture image_gray;
    PGMpicture graycontour;
    PGMpicture pgm_picture;


    QString name("Lena512C_ASCII.ppm");
    QString outname("Lena2.pgm");
    QString outdftgray("Lenagraysobel.pgm");

    //il faudrait pouvoir load un PGM(grayscale) !
    ppmProcessor->loadPPM(name, picture);
    std::cout << "load terminé" << std::endl;

    g_converter->apply(picture, image_gray);
    std::cout << "grayscale applied" << std::endl;

    g_converter->save(image_gray, outname);
    std::cout << "gray saved" << std::endl;

    pgmProcessor->applyFilter(*blurPGM ,image_gray, graycontour);
    pgmProcessor->savePicture(outdftgray, graycontour);
    std::cout << "grayblured saved" << std::endl;

    //filtre_dft->applyDFT(pgm_picture, picture_dft);
    //ppmProcessor->applyFilter(*filtre_blur, picture, picture_out);
    //ppmProcessor->applyFilter(*filtre_sobel, picture, picture_out);
    //ppmProcessor->savePicture(outname, picture_out);
    //filtre_dft->save(picture_dft, outdftgray);


    delete g_converter;
    delete filtre_sobel;
    delete ppmProcessor;
    delete pgmProcessor;
    delete filtre_blur;
    delete filtre_dft;

    return 0;
}
