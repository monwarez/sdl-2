/*
Copyright (C) 2014 Payet thibault

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef MAPLOAD_H
#define MAPLOAD_H

#include "AbstractLoader.h"

#include "../util/Parser.h"

#include <vector>
#include <string>
#include <iostream>

struct Mlerror
{
    std::string erreur;
    int         indice;
};
template <typename T>
class MapLoad : public AbstractLoader
{
    public:
        MapLoad(const std::string &filename);
        ~MapLoad();
        void Read(std::vector<T>& pos, std::vector<T>& posTexture);
        void LoadVector(std::vector <T>& vect ,const std::string &filename, const unsigned int& qte = 4);

        std::vector< std::string > getVectorTexture (std::string filename);

    protected:
        std::vector <unsigned int> texture;
        std::vector< std::vector<double > > position2D;
    private:
};

template <typename T>
void MapLoad<T>::LoadVector(std::vector <T>& vect ,const std::string &filename, const unsigned int& qte)
{

    nameFile = filename;
    this->Load();


    std::string buf;

    int index = 0;
    Parser parse;

    unsigned int quantite = 0;


    if (!contenu.empty())
    {
        for (unsigned int i = 0; i < contenu.size() ; i++)
        {

            buf = contenu[i];

            index = buf.find("*");
            if (index > 0)
                {
                    quantite = (unsigned int) parse.StringToDouble(buf.substr(0,index));
                    buf = buf.substr(index+1);
                }
            else
                quantite = qte;

                for (unsigned int ii = 0; ii< quantite; ii++)
                {
                    index = buf.find("*");
                    if (index > 0)
                    {
                        vect.push_back((T) parse.StringToDouble(buf.substr(0,index)));
                        buf = buf.substr(index+1);
                        }
                }

        }

    }
    else
        std::cerr << "erreur contenu vide " << std::endl;


this->UnLoad(true);

}
template <typename T>
MapLoad<T>::MapLoad(const std::string &filename) : AbstractLoader (filename)
{
    //ctor
    #ifdef Test
    std::cout << "Construction de MapLoad filename: " << filename << std::endl;
    #endif

}

template <typename T>
void MapLoad<T>::Read(std::vector<T>& pos, std::vector<T>& posTexture)
{
    this->Load();


    std::vector<T> position;
    std::string buf;

    int index = 0;
    Parser parse;



    if (!contenu.empty())
    {
        for (unsigned int i = 0; i < contenu.size() ; i++)
        {

            buf = contenu[i];

            position2D.resize(contenu.size());




                for (unsigned int ii = 0; ii<= 20; ii++)
                {
                    index = buf.find("*");
                    if (index > 0)
                    {
                        position.push_back(parse.StringToDouble(buf.substr(0,index)));
                        buf = buf.substr(index+1);


                    }

                }
                position2D[i].push_back(position.size() + 1);
                for (unsigned int ii = 0; ii< position.size(); ii++)
                    position2D[i].push_back(position[ii]);

                position.clear();




        }

        int count1 = 0;

        for (unsigned int i = 0; i < position2D.size(); i++)
        {

            for (unsigned int ii = 1; ii < position2D[i][0]; ii++)
                {

                    switch (count1)
                    {

                    case 0:
                    case 1:
                    case 2:
                        pos.push_back(position2D[i][ii]);
                        count1++;
                        break;
                    case 3:
                        posTexture.push_back(position2D[i][ii]);
                        count1++;
                        break;
                    case 4:
                        posTexture.push_back(position2D[i][ii]);
                        count1 = 0;
                        break;
                    default:
                        std::cerr << "error position & texture " << i <<std::endl;
                        break;

                    }

                }
        }

    }


this->UnLoad(true);

}
template <typename T>
std::vector<std::string> MapLoad<T>::getVectorTexture(std::string filename)
{


    nameFile = filename;
    this->Load();

    std::vector<std::string> tab;
    std::string buf;
    int index = 0;

    if (!contenu.empty())
    {
        for (unsigned int indice = 0; indice < contenu.size(); indice++)
        {
            buf = contenu[indice];
            if (!buf.empty())
            {
                if (buf[0] != '#')
                {
                    index = buf.find("*");
                    if (index < 0)
                    {
                        Mlerror mlerror;
                        std::string a = "erreur dans le fichier \n index : ";
                        mlerror.erreur = a;
                        mlerror.indice = index;
                        throw mlerror;
                    }

                    tab.push_back(buf.substr(0,index));
                    buf = buf.substr(index + 1);
                    while (index > 0)
                    {
                        index = buf.find("*");
                        if (index > 0)
                        {
                            tab.push_back(buf.substr(0,index));
                            buf = buf.substr(index + 1);
                        }
                    }
                }
            }
        }
        return tab;
    }
    else
    {
        return tab;
    }
}

template <typename T>
MapLoad<T>::~MapLoad()
{
    #ifdef Test
    std::cout << "Destruction de MapLoad filename : " << this->nameFile << std::endl;
    #endif
    this->UnLoad(true);
}

#endif // MAPLOAD_H
