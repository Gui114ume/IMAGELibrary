#include <iostream>

#include "PPMProcessor.hpp"
#include "PPMFilterSobel.hpp"

#include "pixeltype.h"


int main(int argc, char** argv)
{
    PPMProcessor* ppmProcessor = new PPMProcessor();
    PPMFilterSobel* filtre_sobel = new PPMFilterSobel();

    PPMpicture picture;
    PPMpicture picture_out;

    QString name("Lena512C_ASCII.ppm");
    QString outname("Lena2.ppm");

    ppmProcessor->loadPPM(name, picture);
    ppmProcessor->applyFilter(*filtre_sobel, picture, picture_out);
    ppmProcessor->savePicture(outname, picture_out);

    delete filtre_sobel;
    delete ppmProcessor;

    return 0;
}
