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

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdlib>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

class Tokenizer
{
public:
    // ctor/dtor
    Tokenizer();
    Tokenizer(const char*const filename, const std::string& delimiter=DEFAULT_DELIMITER);
    ~Tokenizer();
    void setDelimiter(const std::string& delimiter);    // set delimiter string only
    std::string next();                                 // return the next token, return "" if it ends
    void nextLine();
    int nextAsInt();                                 // return the next token, return "" if it ends
    double nextAsDouble();                                 // return the next token, return "" if it ends
    double* nextLineAsDouble();
    float nextAsFloat();
    bool hasnext();
    static constexpr auto DEFAULT_DELIMITER = " \t\v\n\r\f";// default delimiter string (space, tab, newline, carriage return, form feed)

private:
    std::ifstream file;
    std::stringstream line;
    void skipDelimiter();                               // ignore leading delimiters
    bool isDelimiter(char c);                           // check if the current char is delimiter
    std::string token;                                  // output string
    std::string delimiter;                              // delimiter string
    std::string::const_iterator currPos;                // string iterator pointing the current position

};

#endif // TOKENIZER_H
