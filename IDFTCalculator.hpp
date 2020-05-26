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

    void virtual saveDFT(PGMpictureDFT& picture,
                         QString& filename) = 0;

    void virtual saveLogDFT(PGMpictureDFT& picture,
                            QString& filename) = 0;

    void virtual saveRealDFT(PGMpictureDFT& picture,
                             QString& filename) = 0;

    void virtual saveImaginaryDFT(PGMpictureDFT& picture,
                                  QString& filename) = 0;

protected:
    IDFTCalculator() {};
};

#endif
