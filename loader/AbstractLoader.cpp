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
#include "AbstractLoader.h"
using namespace std;
AbstractLoader::AbstractLoader(const string &filename)
{
    //ctor
    nameFile    =   filename;

}
AbstractLoader::~AbstractLoader()
{
    this->UnLoad(true);
}
void AbstractLoader::Load()
{
    string buf ="";
    file.open(nameFile.c_str());
    if (file)
    {
         while (getline(file, buf))
         {
             if (buf.size() > 1)
                buf = buf.substr(0, buf.size() - 1);
             contenu.push_back(buf);
         }
    }
    else
    {
        cerr << "Erreur impossible d'ouvrir: " << nameFile << endl;
    }

}
vector<string> AbstractLoader::GetStringVector()
{
    return this->contenu;
}
void AbstractLoader::UnLoad(bool allVector)
{
    if (allVector)
    {
        file.close();
        contenu.clear();
    }
    else
        file.close();
}


