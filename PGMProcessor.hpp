#ifndef PGMPROCESSOR_HPP
#define PGMPROCESSOR_HPP

#include "IPGMProcessor.hpp"

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>


class PGMProcessor : public IPGMProcessor
{
public:
    virtual ~PGMProcessor(){};
    PGMProcessor(){};

    virtual void loadPGM(QString& filename,
                         PGMpicture& picture) override;

    virtual void applyFilter(IPGMFilter& filter,
                             PGMpicture& picture,
                             PGMpicture& picture_out) override;

    //ce truc doit etre dans une classe dedié au stockage, hors de PGMProcessor
    virtual void savePicture(QString& filename,
                             PGMpicture& picture) override;


private:
    virtual bool isPGMFile(QString& filename,
                           PGMpicture& picture) override;

    virtual void loadPicture(QString& filename,
                             PGMpicture& picture) override;

};




void PGMProcessor::loadPGM(QString& filename,
                           PGMpicture& picture)
{
    if(this->isPGMFile(filename,picture))
    {
        this->loadPicture(filename, picture);
    }
    else
    {
        qDebug() << filename << " is not a P3 PGM picture" << endl;
        exit(-1);
    }
}

void PGMProcessor::applyFilter(IPGMFilter &filter, PGMpicture &picture, PGMpicture &picture_out)
{
    filter.apply(picture,picture_out);
    picture_out.width = picture.width;
    picture_out.length = picture.length;
}

void PGMProcessor::savePicture(QString &filename, PGMpicture &picture)
{
    //à mettre dans une classe PGMSaver ou faire une fonction dans un namespace
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
    outfile << "P2" << endl;

    //Etape 3 : Write width length
    outfile << QString::number(picture.width) << " " << QString::number(picture.length) << endl;

    //Etape 4 : Write max value of pixel (255 here)
    outfile << QString::number(255) << endl;

    //Etape 5 : Write the pixels, not more than 70 (?) characters per line ! (here is the difficulty, how to do this ? -> Consider the worst case : each color need 3 characters to be written )
    //D'apres l'image test, on peut ecrire plus que 70 caracteres...
    quint32 n = 0;
    for(auto& pix : picture.picture)
    {
        outfile << QString::number(pix) << " ";
        ++n;
        if(n == 5)
        {
            outfile << endl;
            n = 0;
        }

    }
    fileHandle.close();


}

bool PGMProcessor::isPGMFile(QString& filename,
                             PGMpicture& picture)
{
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             qDebug() <<" fileHandle badly opened, in isPGMFile" << endl;
             exit(-1); //utiliser exception ?
         }
    QTextStream in(&fileHandle);
    QString line = in.readLine();

    if(line == QString::fromStdString("P3"))
    {
        picture.PGMformat = QString::fromStdString("P3");
        fileHandle.close();
        //qDebug() << "ok cest un PGM"<<endl;
        return true;
    }
    else
    {
        fileHandle.close();
        return false;
    }
}

void PGMProcessor::loadPicture(QString& filename,
                               PGMpicture& picture)
{
    QFile fileHandle(filename);
    if(!fileHandle.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             qDebug() <<" fileHandle badly opened, in isPGMFile" << endl;
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

    quint32 tmp;

    //first reading
    line = in.readLine();
    List = line.split(" ");

    //on parcours tout le fichier PGM
    while( !line.isEmpty() )
    {
        //si la ligne lu n'est pas un commentaire
        if(List[0] != QString::fromStdString("#"))
        {
            //on rempli l'image avec les valeurs des pixels contenus dans List[]
            for( quint32 List_index = 0 ; List_index < List.size() ; List_index++)
            {
                tmp = List[List_index].toUInt();
                picture.picture.push_back(tmp);
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


#endif // PGMPROCESSOR_HPP
