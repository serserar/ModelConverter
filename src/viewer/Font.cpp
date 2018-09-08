/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Font.cpp -- Copyright (c) 2006 David Henry
// last modification: mar. 3, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Implementation of an OpenGL True Type Font class.
//
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Font.h"

using std::cerr;
using std::endl;


/////////////////////////////////////////////////////////////////////////////
//
// class TTFont implementation.
//
/////////////////////////////////////////////////////////////////////////////

int TTFont::_ttfCount = 0;


// --------------------------------------------------------------------------
// TTFont::TTFont
//
// Constructor.  Build a texture font from a TTF and generate display
// lists for each character of the Latin1 ASCII table.
// --------------------------------------------------------------------------

TTFont::TTFont (const string &fontPath, int size, int border)
  //throw (std::runtime_error)
  : _texFontId (0), _startList (0), _texWidth (0), _texHeight (0),
    _maxHeight (0), _fontAscent (0), _fontDescent (0), _lineSkip (0),
    _border (border), _maxAdvance (0)
{
  if (!TTF_WasInit () && (TTF_Init() < 0))
    //throw std::runtime_error (string ("TTF_Init failed: ") + TTF_GetError ());
    return;
  _ttfCount++;

  TTF_Font *font = TTF_OpenFont (fontPath.c_str (), size);
  if (!font)
    //throw std::runtime_error (string ("TTF_OpenFont failed: ") + TTF_GetError ());
      return;

  getGlyphMetrics (font);

  buildFontMap (font);

  buildDisplayLists ();

  TTF_CloseFont (font);
}


// --------------------------------------------------------------------------
// TTFont::~TTFont
//
// Destructor.  Delete texture and display lists.
// --------------------------------------------------------------------------

TTFont::~TTFont ()
{
  if (glIsTexture (_texFontId))
    glDeleteTextures (1, &_texFontId);

  glDeleteLists (_startList, 256);

  _ttfCount--;

  if (!_ttfCount)
    TTF_Quit ();
}


// --------------------------------------------------------------------------
// TTFont::printText
//
// Print multiline formated text.
// --------------------------------------------------------------------------

void
TTFont::printText (const char *format, ...) const
{
  char buffer[1024];
  std::va_list arg;

  // Format the text
  va_start (arg, format);
    vsprintf (buffer, format, arg);
  va_end (arg);

  glPushAttrib (GL_ENABLE_BIT);
  glDisable (GL_LIGHTING);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, _texFontId);

  char *ptr = buffer;

  // Print each line separately
  do
    {
      int len;
      char *end = strchr (ptr, '\n');

      if (!end)
	len = strlen (ptr);
      else
	{
	  end++;
	  len = end - ptr - 1;
	}

      glPushMatrix ();
	// Print the current line
	printTextOneLine (ptr, len);
      glPopMatrix ();

      // Move to next line
      glTranslatef (0.0f, -_lineSkip, 0.0f);

      ptr = end;
    }
  while (ptr);

  // GL_ENABLE_BIT
  glPopAttrib ();
}


void
TTFont::printText (int x, int y, const char *format, ...) const
{
  // Setup text position
  glLoadIdentity ();
  glTranslatef (x, y, 0.0f);

  // Format the text
  char buffer[1024];
  std::va_list arg;

  va_start (arg, format);
    vsprintf (buffer, format, arg);
  va_end (arg);

  // Print it
  printText (buffer);
}


// --------------------------------------------------------------------------
// TTFont::printTextOneLine
//
// Print a single line text.
// --------------------------------------------------------------------------

void
TTFont::printTextOneLine (const char *text, int length) const
{
  glListBase (_startList);
  glCallLists (length, GL_UNSIGNED_BYTE, text);
}


// --------------------------------------------------------------------------
// TTFont::getGlyphMetrics
//
// Get metrics for each glyph of the font.
// --------------------------------------------------------------------------

void
TTFont::getGlyphMetrics (TTF_Font *font)
{
  _advance.reserve (256);
  _maxAdvance = 0;

  for (int i = 0; i < 256; ++i)
    {
      int dummy, advance;
      TTF_GlyphMetrics (font, static_cast<Uint16>(i), &dummy, &dummy,
			&dummy, &dummy, &advance);
      _advance.push_back (advance);

      if (advance > _maxAdvance)
	_maxAdvance = advance;
    }

  // NOTE: fontHeight == fontAscent - fontDescent + 1
  _maxHeight = TTF_FontHeight (font);
  _fontDescent = TTF_FontDescent (font) - 1;
  _fontAscent = TTF_FontAscent (font);
  _lineSkip = TTF_FontLineSkip (font);
}


// --------------------------------------------------------------------------
// TTFont::buildFontMap
//
// Build a texture holding each glyph of the font.
// --------------------------------------------------------------------------

void
TTFont::buildFontMap (TTF_Font *font)
{
  int width = (_maxAdvance + _border) * 16 + _border;
  int height = (_maxHeight + _border) * 16 + _border;

  _texWidth = 1;
  _texHeight = 1;

  // Get texture width and height (the first power of two
  // greater than original size)
  while (_texWidth < width)
    _texWidth = _texWidth << 1;

  while (_texHeight < height)
    _texHeight = _texHeight << 1;

  // Create a black texture with transparent alpha
  GLubyte *texels = new GLubyte[_texWidth * _texHeight * 4];
  memset (texels, 0, _texWidth * _texHeight * 4);

  glGenTextures (1, &_texFontId);
  glBindTexture (GL_TEXTURE_2D, _texFontId);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D (GL_TEXTURE_2D, 0, 4, _texWidth, _texHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texels);

  // We no longer need texture data
  delete [] texels;

  int xoffset = _border;
  int yoffset = _border;

  // Now "insert" each character in the texture
  for (int i = 0; i < 16; ++i)
    {
      for (int j = 0; j < 16; ++j)
	{
	  char letter[2];
	  letter[0] = static_cast<char>(i * 16 + j);
	  letter[1] = '\0';

	  if (letter[0] != 0)
	    {
	      // White with full alpha
	      SDL_Color foreground = { 255, 255, 255, 255 };
	      SDL_Surface *sLetter = TTF_RenderText_Blended (font,
					     letter, foreground);

	      if (sLetter)
		{
		  // Copy letter's surface to font texture
		  // at the appropriate place
		  glTexSubImage2D (GL_TEXTURE_2D, 0, xoffset,
				   yoffset, sLetter->w, sLetter->h,
				   GL_RGBA, GL_UNSIGNED_BYTE,
				   sLetter->pixels);

		  SDL_FreeSurface (sLetter);
		}
	    }

	  xoffset += _maxAdvance + _border;
	}

      xoffset = _border;
      yoffset += _maxHeight + _border;
    }
}


// --------------------------------------------------------------------------
// TTFont::buildDisplayLists
//
// Build a display list for each character.  A character is represented
// by a textured quad + a translation of its "width" about the X-axis.
// --------------------------------------------------------------------------

void
TTFont::buildDisplayLists ()
{
  _startList = glGenLists (256);

  GLfloat oneOverTexWidth = 1.0f / static_cast<GLfloat>(_texWidth);
  GLfloat oneOverTexHeight = 1.0f / static_cast<GLfloat>(_texHeight);

  GLfloat s = _border * oneOverTexWidth;
  GLfloat t = _border * oneOverTexHeight;

  GLfloat toffset = _fontAscent * oneOverTexHeight;

  for (int i = 0, c = 0; i < 16; ++i)
    {
      for (int j = 0; j < 16; ++j, ++c)
	{
	  /*
	    s = (j * (_maxAdvance + _border) + _border) * oneOverTexWidth;
	    t = (i * (_maxHeight + _border) + _border) * oneOverTexHeight;
	  */

	  GLfloat soffset = _advance[c] * oneOverTexWidth;

	  glNewList (_startList + c, GL_COMPILE);
	  glBegin (GL_QUADS);
	    glTexCoord2f (s, t + toffset
			  - (_fontDescent * oneOverTexHeight));
	    glVertex2i (0, _fontDescent);

	    glTexCoord2f (s + soffset, t + toffset
			  - (_fontDescent * oneOverTexHeight));
	    glVertex2i (_advance[c], _fontDescent);

	    glTexCoord2f (s + soffset, t);
	    glVertex2i (_advance[c], _fontAscent);

	    glTexCoord2f (s, t);
	    glVertex2i (0, _fontAscent);
	  glEnd ();

	  glTranslatef (_advance[c], 0.0f, 0.0f);
	  glEndList ();

	  s += (_maxAdvance + _border) * oneOverTexWidth;
	}

      s = _border * oneOverTexWidth;
      t += (_maxHeight + _border) * oneOverTexHeight;
    }
}


// --------------------------------------------------------------------------
// TTFont::test
//
// Test function.  Draw a quad with font's texture at position (x, y).
// --------------------------------------------------------------------------

void
TTFont::test (int x, int y)
{
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable (GL_TEXTURE_2D);
  glColor4f (1.0f, 0.0f, 0.0f, 0.25f);

  glBegin (GL_QUADS);
    glVertex2f (x, y);
    glVertex2f (x + _texWidth, y);
    glVertex2f (x + _texWidth, y + _texHeight);
    glVertex2f (x, y + _texHeight);
  glEnd ();

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, _texFontId);

  glColor3f (1.0f, 1.0f, 1.0f);
  glBegin (GL_QUADS);
    glTexCoord2f (0.0f, 1.0f); glVertex2f (x, y);
    glTexCoord2f (1.0f, 1.0f); glVertex2f (x + _texWidth, y);
    glTexCoord2f (1.0f, 0.0f); glVertex2f (x + _texWidth, y + _texHeight);
    glTexCoord2f (0.0f, 0.0f); glVertex2f (x, y + _texHeight);
  glEnd ();

  glDisable (GL_TEXTURE_2D);
  glDisable (GL_BLEND);
}
