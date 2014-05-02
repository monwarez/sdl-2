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
#include "Parser.h"

using namespace std;

Parser::Parser()
{
    //ctor
    valide = false;
}
bool Parser::isValid()
{
    return valide;
}
double Parser::StringToDouble(const string &chaine)
{

    double signe = 1.0;

    if (chaine[0] == '-')
        signe = - 1.0;

    int index = chaine.find(".");

    double nb = 0.0;
    double id = 0;
    valide = true;

    if (index < 0){
        index = chaine.size();
        for (int i = 0; i < index ; i++)
        {
            id = fabs((double)(index - i)-1);
            switch (chaine[i])
            {
            case '1':
                nb += pow(10,id);
                break;
            case '2':
                nb += 2*pow(10,id);
                break;
            case '3':
                nb += 3*pow(10,id);
                break;
            case '4':
                nb += 4*pow(10,id);
                break;
                case '5':
                nb += 5*pow(10,id);
                break;
            case '6':
                nb += 6*pow(10,id);
                break;
            case '7':
                nb += 7*pow(10,id);
                break;
            case '8':
                nb += 8*pow(10,id);
                break;
            case '9':
                nb += 9*pow(10,id);
                break;
            case '0':
                break;
            default:
                valide = false;
            }
        }

        return nb*signe;
    }
    for (int i = 0; i < index ; i++)
        {
            id = fabs((double)(index - i)-1);
            switch (chaine[i])
            {
            case '1':
                nb += pow(10,id);
                break;
            case '2':
                nb += 2*pow(10,id);
                break;
            case '3':
                nb += 3*pow(10,id);
                break;
            case '4':
                nb += 4*pow(10,id);
                break;
                case '5':
                nb += 5*pow(10,id);
                break;
            case '6':
                nb += 6*pow(10,id);
                break;
            case '7':
                nb += 7*pow(10,id);
                break;
            case '8':
                nb += 8*pow(10,id);
                break;
            case '9':
                nb += 9*pow(10,id);
                break;
            case '0':
                nb += 0.0;
                break;
            default:
                valide = false;
            }
        }
    string chaine2 = chaine.substr(index+1);
    for (unsigned int i = 0; i < chaine2.size(); i++)
    {
        id = (double)((i+1));
        switch (chaine2[i])
        {
        case '1':
            nb += 1/pow(10,id);
            break;
        case '2':
            nb += 2/pow(10,id);
            break;
        case '3':
            nb += 3/pow(10,id);
            break;
        case '4':
            nb += 4/pow(10,id);
            break;
        case '5':
            nb += 5/pow(10,id);
            break;
        case '6':
            nb += 6/pow(10,id);
            break;
        case '7':
            nb += 7/pow(10,id);
            break;
        case '8':
            nb += 8/pow(10,id);
            break;
        case '9':
            nb += 9/pow(10,id);
            break;
        case '0':
            nb += 0.0;
            break;
        default:
            valide = false;
        }
    }

    return nb*signe;
}
Parser::~Parser()
{
    //dtor
}
