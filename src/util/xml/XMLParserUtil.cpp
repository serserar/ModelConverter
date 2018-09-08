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

#include "XMLParserUtil.h"

XmlParserUtil::XmlParserUtil() {

}

bool XmlParserUtil::parseXML(const char* xmlPath, XMLEventHandler& xmlEventHandler) {
    // Initialize all fields to zero
    xmlSAXHandler sh = {0};

    // register callback

    sh.startElement = startElement;
    sh.characters = characters;
    sh.endElement = endElement;
    xmlParserCtxtPtr ctxt;

    // create the context
    if ((ctxt = xmlCreateFileParserCtxt(xmlPath)) == NULL) {
        fprintf(stderr, "Error al crear contexto\n");
        return false;
    }
    // register sax handler with the context
    ctxt->sax = &sh;
    ctxt->userData = (void*) &xmlEventHandler;
    // parse the doc
    xmlParseDocument(ctxt);
    // well-formed document?
    if (!ctxt->wellFormed) {
        fprintf(stderr, "XML Document isn't well formed\n");
        //xmlFreeParserCtxt(ctxt);
        return false;
    }

    // free the memory
    //xmlFreeParserCtxt(ctxt);


    return true;
}

void XmlParserUtil::startElement(void* user_data, const xmlChar* name, const xmlChar** attrs) {
    ((XMLEventHandler*) user_data)->startElement(user_data, name, attrs);
}

void XmlParserUtil::characters(void* user_data, const xmlChar* ch, int len) {
    ((XMLEventHandler*) user_data)->characters(user_data, ch, len);
}

void XmlParserUtil::endElement(void* user_data, const xmlChar* name) {
    ((XMLEventHandler*) user_data)->endElement(user_data, name);
}

XmlParserUtil::~XmlParserUtil() {

}
