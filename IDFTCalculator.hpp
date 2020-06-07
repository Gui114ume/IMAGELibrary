#ifndef IDFTCALCULATOR_HPP
#define IDFTCALCULATOR_HPP

#include "pixeltype.h"

#include <QString>

class IDFTCalculator
{
public:
    virtual ~IDFTCalculator() {};

    void virtual computeDFT(PGMpicture&    picture_in,
                            PGMpictureDFT& picture_out) = 0;

    void virtual computeInvDFT(PGMpictureDFT&    picture_in,
                               PGMpicture& picture_out) = 0;

    /* plus tard
    void virtual saveDFT(PGMpictureDFT& picture,
                         QString& filename) = 0;

    void virtual saveLogDFT(PGMpictureDFT& picture,
                            QString& filename) = 0; // log de quoi ?

    void virtual saveRealDFT(PGMpictureDFT& picture,
                             QString& filename) = 0;

    void virtual saveImaginaryDFT(PGMpictureDFT& picture,
                                  QString& filename) = 0;

    void virtual loadDFT(QString& filename,
                         PGMpictureDFT& picture) = 0; //on ne peut load que la DFT complete, avec partie imaginaire et partie reel

*/

protected:
    IDFTCalculator() {};
};

#endif
