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
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cmath>

class Parser
{
    public:
        Parser();
        virtual double StringToDouble(const std::string &chaine);
        virtual bool isValid();
        virtual ~Parser();
    protected:
        bool valide;
    private:
};

#endif // PARSER_H
