#include <iostream>

#include "PPMProcessor.hpp"
#include "PPMFilterSobel.hpp"
#include "PPMFilterBlur.hpp"
#include "PPMFilterDFT.hpp"


#include "pixeltype.h"


int main(int argc, char** argv)
{
    PPMProcessor* ppmProcessor = new PPMProcessor();
    PPMFilterSobel* filtre_sobel = new PPMFilterSobel();
    PPMFilterBlur* filtre_blur = new PPMFilterBlur();
    PPMFilterDFT* filtre_dft = new PPMFilterDFT;

    PPMpicture picture;
    PPMpicture picture_out;
    PPMpictureDFT picture_dft;


    QString name("Lena512C_ASCII.ppm");
    QString outname("Lena2.ppm");

    ppmProcessor->loadPPM(name, picture);
    filtre_dft->applyDFT(picture, picture_dft);
    //ppmProcessor->applyFilter(*filtre_blur, picture, picture_out);
    //ppmProcessor->applyFilter(*filtre_sobel, picture, picture_out);
    //ppmProcessor->savePicture(outname, picture_out);


    delete filtre_sobel;
    delete ppmProcessor;
    delete filtre_blur;
    delete filtre_dft;

    return 0;
}
