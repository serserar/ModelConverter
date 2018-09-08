/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Font.h -- Copyright (c) 2006 David Henry
// last modification: mar. 3, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definition of an OpenGL True Type Font class.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __FONT_H__
#define __FONT_H__

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // _WIN32

#include <GL/gl.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdarg>

using std::string;
using std::vector;


/////////////////////////////////////////////////////////////////////////////
//
// class TTFont - An OpenGL True Type Font object.
//
/////////////////////////////////////////////////////////////////////////////

class TTFont
{
public:
  // Constructor/destructor
  TTFont (const string &fontPath, int size, int border = 0);
    //throw (std::runtime_error);
  ~TTFont ();

public:
  // Public interface
  void printText (const char *format, ...) const;
  void printText (int x, int y, const char *format, ...) const;

  // Accessors
  int getLineSkip () const { return _lineSkip; }

  // Test functions
  void test (int x, int y);

private:
  // Internal functions
  void printTextOneLine (const char *text, int length) const;

  void getGlyphMetrics (TTF_Font *font);
  void buildFontMap (TTF_Font *font);
  void buildDisplayLists ();

private:
  // Member variables
  GLuint _texFontId;
  GLuint _startList;

  int _texWidth;
  int _texHeight;

  int _maxHeight;
  int _fontAscent;
  int _fontDescent;
  int _lineSkip;

  int _border;

  // Glyph metrics advance parameter
  vector<int> _advance; // for each glyph
  int _maxAdvance; // store the max

  // TrueTypeFont counter
  static int _ttfCount;
};

#endif // __FONT_H__
