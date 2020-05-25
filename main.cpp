#include <iostream>

#include "PPMProcessor.hpp"
#include "PPMFilterSobel.hpp"
#include "PPMFilterBlur.hpp"
#include "PPMFilterDFT.hpp"
#include "PPMFilterGrayscaleConverter.hpp"


#include "pixeltype.h"


int main(int argc, char** argv)
{
    PPMProcessor* ppmProcessor = new PPMProcessor();
    PPMFilterSobel* filtre_sobel = new PPMFilterSobel();
    PPMFilterBlur* filtre_blur = new PPMFilterBlur();
    PPMFilterDFT* filtre_dft = new PPMFilterDFT;
    GrayscaleConverter* g_converter = new GrayscaleConverter();

    PPMpicture picture;
    PPMpicture picture_out;
    PPMpictureDFT picture_dft;
    QVector<quint32> image_gray;


    QString name("Lena512C_ASCII.ppm");
    QString outname("Lena2.pgm");

    ppmProcessor->loadPPM(name, picture);
    g_converter->apply(picture, image_gray);
    g_converter->save(image_gray, picture.width, picture.length, outname);
    //filtre_dft->applyDFT(picture, picture_dft);
    //ppmProcessor->applyFilter(*filtre_blur, picture, picture_out);
    //ppmProcessor->applyFilter(*filtre_sobel, picture, picture_out);
    //ppmProcessor->savePicture(outname, picture_out);

    delete g_converter;
    delete filtre_sobel;
    delete ppmProcessor;
    delete filtre_blur;
    delete filtre_dft;

    return 0;
}
