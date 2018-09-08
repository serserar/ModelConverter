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

#ifndef XMLPARSERUTIL_H
#define XMLPARSERUTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parserInternals.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include "XMLEventHandler.h"

class XmlParserUtil {
public:
    XmlParserUtil();
    bool parseXML(const char* xmlPath, XMLEventHandler& xmlEventHandler);
    static void startElement(void * user_data, const xmlChar *name, const xmlChar **attrs);
    static void characters(void * user_data, const xmlChar * ch, int len);
    static void endElement(void * user_data, const xmlChar * name);
    ~XmlParserUtil();
private:
    static XMLEventHandler* xmlEventHandler;
};

#endif // XMLPARSERUTIL_H
