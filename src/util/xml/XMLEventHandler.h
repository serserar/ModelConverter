/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef XMLEVENTHANDLER_H
#define XMLEVENTHANDLER_H

#include <libxml/parserInternals.h>
#include <string.h>

class XMLEventHandler {
public:

    XMLEventHandler() {
    };
    virtual void startElement(void * user_data, const xmlChar *name, const xmlChar **attrs) = 0;
    virtual void characters(void * user_data, const xmlChar * ch, int len) = 0;
    virtual void endElement(void * user_data, const xmlChar * name) = 0;

    ~XMLEventHandler() {
    };

};

#endif // XMLEVENTHANDLER_H
