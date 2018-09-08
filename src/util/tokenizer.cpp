/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "tokenizer.h"
#include <cstdlib>

Tokenizer::Tokenizer() :  token(""), delimiter(DEFAULT_DELIMITER)
{
}

Tokenizer::Tokenizer(const char*const filename, const std::string& delimiter) : file(filename), token(""), delimiter(delimiter)
{
}


///////////////////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////////////////
Tokenizer::~Tokenizer()
{
}

void Tokenizer::setDelimiter(const std::string& delimiter)
{
    this->delimiter = delimiter;
}

///////////////////////////////////////////////////////////////////////////////
// return the next token
// If cannot find a token anymore, return "".
///////////////////////////////////////////////////////////////////////////////
std::string Tokenizer::next()
{
    if (this->line.str().empty() || !this->line || !(this->line >> this->token)) {
        std::getline(this->file, this->token,'\n');
        this->line.clear();
        this->line.str(token);
        this->line >> this->token;
    }
    return this->token;
}

void Tokenizer::nextLine()
{
    std::getline(this->file, this->token);
    this->line.clear();
    this->line.str(token);
}


bool Tokenizer::hasnext()
{
    return !this->file.eof();
}

int Tokenizer::nextAsInt()
{
    int i;
    if (this->line.str().empty() || !this->line || !(this->line >> this->token)) {
        std::getline(this->file, this->token,'\n');
        this->line.clear();
        this->line.str(token);
	this->line >> this->token;
    }
    std::stringstream si(token);
    si >> i;
    return i;
}

double Tokenizer::nextAsDouble()
{
    double d;
    if (this->line.str().empty() || !this->line || !(this->line >> this->token)) {
        std::getline(this->file, this->token,'\n');
        this->line.clear();
        this->line.str(token);
	this->line >> this->token;
    }
    std::stringstream sd(token);
    sd >> d;
    return d;
}

float Tokenizer::nextAsFloat()
{
    float d;
    if (this->line.str().empty() || !this->line || !(this->line >> this->token)) {
        std::getline(this->file, this->token,'\n');
        this->line.clear();
        this->line.str(token);
	this->line >> this->token;
    }
    std::stringstream sd(token);
    sd >> d;
    return d;
}


double* Tokenizer::nextLineAsDouble()
{
    double* darray = 0;
    if (this->line.str().empty() || !this->line || !(this->line >> this->token)) {
        std::getline(this->file, this->token,'\n');
        this->line.clear();
        this->line.str(token);
    }
    std::stringstream sd(token);
    int components = 0;
    double d;
    while (sd >> d) {
        darray = (double *) realloc (darray,(components+2) * sizeof(double));
	darray[components+1] = d;
        components++;
	darray[0]= (double)components;
    }
    return darray;
}


///////////////////////////////////////////////////////////////////////////////
// skip ang leading delimiters
///////////////////////////////////////////////////////////////////////////////
void Tokenizer::skipDelimiter()
{

}

///////////////////////////////////////////////////////////////////////////////
// return true if the current character is delimiter
///////////////////////////////////////////////////////////////////////////////
bool Tokenizer::isDelimiter(char c)
{
    return (delimiter.find(c) != std::string::npos);
}



