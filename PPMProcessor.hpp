#ifndef PPMPROCESSOR_HPP
#define PPMPROCESSOR_HPP

#include "IPPMProcessor.hpp"

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PPMProcessor : public IPPMProcessor
{
public:
    virtual ~PPMProcessor(){};
    PPMProcessor(){};

    //on donne un nom de fichier ou un QFile ? -> QFile
    //creer loadPPM() avec isPPM() et loadPicture() -> mettre isPPM() et loadPicture() en private

    virtual void loadPPM(QString& filename,
                         PPMpicture& picture) override;

    virtual void applyFilter(IPPMFilter& filter,
                             PPMpicture& picture,
                             PPMpicture& picture_out) override;

    //il faut des metadonnees sur l'image pour l'ecrire sur disque, on peut pas deviner la largeur/hauteur
    //ce truc doit etre dans une classe dedié au stockage, hors de PPMProcessor
    virtual void savePicture(QString& filename,
                             PPMpicture& picture) override;



private:
    virtual bool isPPMFile(QString& filename,
                           PPMpicture& picture) override;

    virtual void loadPicture(QString& filename,
                             PPMpicture& picture) override;

};



#endif // PPMPROCESSOR_HPP

void PPMProcessor::loadPPM(QString& filename,
                           PPMpicture& picture)
{
    if(this->isPPMFile(filename,picture))
    {
        this->loadPicture(filename, picture);
    }
    else
    {
        qDebug() << filename << " is not a P3 PPM picture" << endl;
        exit(-1);
    }
}

void PPMProcessor::applyFilter(IPPMFilter &filter, PPMpicture &picture, PPMpicture &picture_out)
{
    filter.apply(picture,picture_out);
    picture_out.width = 512;
    picture_out.length = 512;
}

void PPMProcessor::savePicture(QString &filename, PPMpicture &picture)
{
    //à mettre dans une classe PPMSaver ou faire une fonction dans un namespace
    //Comment ecrire dans le fichier ?

    //Etape 1 : Open the  file
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
         {
             qDebug() << filename <<" badly opened, in savePicture" << endl;
             exit(-1); //utiliser exception ?
         }
    QTextStream outfile(&fileHandle);
    //Etape 2 : Write Format (P3 here)
    outfile << "P3" << endl;

    //Etape 3 : Write width length
    outfile << QString::number(picture.width) << " " << QString::number(picture.length) << endl;

    //Etape 4 : Write max value of pixel (255 here)
    outfile << QString::number(255) << endl;

    //Etape 5 : Write the pixels, not more than 70 (?) characters per line ! (here is the difficulty, how to do this ? -> Consider the worst case : each color need 3 characters to be written )
    //D'apres l'image test, on peut ecrire plus que 70 caracteres...
    quint32 n = 0;
    for(auto& pix : picture.picture)
    {
        outfile << QString::number(pix.R) << " " << QString::number(pix.G) << " " << QString::number(pix.B) << " ";
        ++n;
        if(n == 5)
        {
            outfile << endl;
            n = 0;
        }

    }
    fileHandle.close();


}

bool PPMProcessor::isPPMFile(QString& filename,
                             PPMpicture& picture)
{
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             qDebug() <<" fileHandle badly opened, in isPPMFile" << endl;
             exit(-1); //utiliser exception ?
         }
    QTextStream in(&fileHandle);
    QString line = in.readLine();

    if(line == QString::fromStdString("P3"))
    {
        picture.PPMformat = QString::fromStdString("P3");
        fileHandle.close();
        //qDebug() << "ok cest un ppm"<<endl;
        return true;
    }
    else
    {
        fileHandle.close();
        return false;
    }
}

void PPMProcessor::loadPicture(QString& filename,
                               PPMpicture& picture)
{
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             qDebug() <<" fileHandle badly opened, in isPPMFile" << endl;
             exit(-1); //utiliser exception ?
         }
    QTextStream in(&fileHandle);
    QString line;
    QStringList List;

    line = in.readLine(); // la premiere ligne on la relit pas

    //get width and height
    line = in.readLine(); // probleme ici, il lit des nombres qu'il ne devrait pas size() = 55 !!
    List = line.split(QString(" "));

    if(List.size() != 2)
    {
        qDebug() << " Wrong file data, verify width/length line" << endl;
        fileHandle.close();
        exit(-1);
    }

    picture.width = List[0].toUInt();
    picture.length =List[1].toUInt();

    //qDebug() << picture.width << "  " << picture.length << endl;

    //get max pixel color value (don't care for now)
    line = in.readLine();


    //get picture

    pixel tmp;

    //first reading
    line = in.readLine();
    List = line.split(" ");

    //on parcours tout le fichier PPM
    while( !line.isEmpty() )
    {
        //si la ligne lu n'est pas un commentaire
        if(List[0] != QString::fromStdString("#"))
        {
            //on rempli l'image avec les valeurs des pixels contenus dans List[]
            for( quint32 List_index = 0 ; List_index < List.size() - 3; List_index += 3)
            {
                tmp.R = List[List_index].toUInt();
                tmp.G = List[List_index + 1].toUInt();
                tmp.B = List[List_index + 2].toUInt();
                picture.picture.push_back(tmp);
      //          std::cout << tmp.R << " " << tmp.G << " " << tmp.B << " ";
            }
           //std::cout << std::endl;
           line = in.readLine();
           List = line.split(" ");
        }
        else
        {
            line = in.readLine();
            List = line.split(" ");
            continue;
        }

    }
    fileHandle.close();
}
