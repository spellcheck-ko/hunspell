/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * Copyright (C) 2002-2017 Németh László
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Hunspell is based on MySpell which is Copyright (C) 2002 Kevin Hendricks.
 *
 * Contributor(s): David Einstein, Davide Prina, Giuseppe Modugno,
 * Gianluca Turconi, Simon Brouwer, Noll János, Bíró Árpád,
 * Goldman Eleonóra, Sarlós Tamás, Bencsáth Boldizsár, Halácsy Péter,
 * Dvornik László, Gefferth András, Nagy Viktor, Varga Dániel, Chris Halls,
 * Rene Engelhard, Bram Moolenaar, Dafydd Jones, Harri Pitkänen
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
/*
 * Copyright 2002 Kevin B. Hendricks, Stratford, Ontario, Canada
 * And Contributors.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All modifications to the source code must be clearly marked as
 *    such.  Binary redistributions based on modified source code
 *    must be clearly marked as modified versions in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY KEVIN B. HENDRICKS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * KEVIN B. HENDRICKS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "conv-ko.hxx"
#include <string.h>
#include "csutil.hxx"

class ConverterKoreanImpl {
 public:
  ConverterKoreanImpl(const Converter::ParameterList& params);
  bool input_conv(const std::string& src, std::string& dest) const;
  bool output_conv(const std::string& src, std::string& dest) const;

 private:
  w_char code_reset;
};

ConverterKorean::ConverterKorean(const ParameterList& params)
{
  impl = new ConverterKoreanImpl(params);

  for (std::string param : params) {
    // FIXME
  }
}

ConverterKorean::~ConverterKorean()
{
  delete impl;
}

bool ConverterKorean::input_conv(const std::string& src, std::string& dest)
{
  return  impl->input_conv(src, dest);
}

bool ConverterKorean::output_conv(const std::string& src, std::string& dest)
{
  return impl->output_conv(src, dest);
}

ConverterKoreanImpl::ConverterKoreanImpl(const Converter::ParameterList& params)
{
  code_reset.h = 0x31;
  code_reset.l = 0x30;
}

bool ConverterKoreanImpl::input_conv(const std::string& src, std::string& dest) const
{
  static const int ljamos[] = {
    0x3131, // ㄱ
    0x3132, // ㄲ
    0x3134, // ㄴ
    0x3137, // ㄷ
    0x3138, // ㄸ
    0x3139, // ㄹ
    0x3141, // ㅁ
    0x3142, // ㅂ
    0x3143, // ㅃ
    0x3145, // ㅅ
    0x3146, // ㅆ
    0x3147, // ㅇ
    0x3148, // ㅈ
    0x3149, // ㅉ
    0x314A, // ㅊ
    0x314B, // ㅋ
    0x314C, // ㅌ
    0x314D, // ㅍ
    0x314E, // ㅎ
  };
  static const int vjamos[] = {
    0x314F, // ㅏ
    0x3150, // ㅐ
    0x3151, // ㅑ
    0x3152, // ㅒ
    0x3153, // ㅓ
    0x3154, // ㅔ
    0x3155, // ㅕ
    0x3156, // ㅖ
    0x3157, // ㅗ
    0x8000 + 0, // ㅘ
    0x8000 + 1, // ㅙ
    0x8000 + 2, // ㅚ
    0x315B, // ㅛ
    0x315C, // ㅜ
    0x8000 + 3, // ㅝ
    0x8000 + 4, // ㅞ
    0x8000 + 5, // ㅟ
    0x3160, // ㅠ
    0x3161, // ㅡ
    0x8000 + 6, // ㅢ
    0x3163, // ㅣ
  };
  static const int vjamos_comp[16][2] = {
    { 0x3157, 0x314F }, // ㅘ
    { 0x3157, 0x3150 }, // ㅙ
    { 0x3157, 0x3163 }, // ㅚ
    { 0x315C, 0x3153 }, // ㅝ
    { 0x315C, 0x3154 }, // ㅞ
    { 0x315C, 0x3163 }, // ㅟ
    { 0x3161, 0x3163 }, // ㅢ
  };
  static const int tjamos[] = {
    0xFFFF, // none
    0x3131, // ㄱ
    0x3132, // ㄲ
    0x8000 + 0, // ㄱㅅ
    0x3134, // ㄴ
    0x8000 + 1, // ㄴㅈ
    0x8000 + 2, // ㄴㅎ
    0x3137, // ㄷ
    0x3139, // ㄹ
    0x8000 + 3, // ㄹㄱ
    0x8000 + 4, // ㄹㅁ
    0x8000 + 5, // ㄹㅂ
    0x8000 + 6, // ㄹㅅ
    0x8000 + 7, // ㄹㅌ
    0x8000 + 8, // ㄹㅍ
    0x8000 + 9, // ㄹㅎ
    0x3141, // ㅁ
    0x3142, // ㅂ
    0x8000 + 10, // ㅂㅅ
    0x3145, // ㅅ
    0x3146, // ㅆ
    0x3147, // ㅇ
    0x3148, // ㅈ
    0x314A, // ㅊ
    0x314B, // ㅋ
    0x314C, // ㅌ
    0x314D, // ㅍ
    0x314E, // ㅎ
  };
  static const int tjamos_comp[16][2] = {
    { 0x3131, 0x3145 }, // ㄱㅅ
    { 0x3134, 0x3148 }, // ㄴㅈ
    { 0x3134, 0x314E }, // ㄴㅎ
    { 0x3139, 0x3131 }, // ㄹㄱ
    { 0x3139, 0x3141 }, // ㄹㅁ
    { 0x3139, 0x3142 }, // ㄹㅂ
    { 0x3139, 0x3145 }, // ㄹㅅ
    { 0x3139, 0x314C }, // ㄹㅌ
    { 0x3139, 0x314D }, // ㄹㅍ
    { 0x3139, 0x314E }, // ㄹㅎ
    { 0x3142, 0x3145 }, // ㅂㅅ
  };
  std::vector<w_char> u16;
  int nchar;

  nchar = u8_u16(u16, src);
  std::vector<w_char> u16_dest;
  enum {
    INITIAL,
    LAST_IS_C,
    LAST_IS_V,
  } state = INITIAL;

  for (int idx = 0; idx < nchar; ++idx) {
    int chord = u16[idx].h << 8 | u16[idx].l;
    if ((chord >= 0xAC00) && (chord <= 0xD7A3)) {
      // syllables
      int idx = chord - 0xAC00;
      int l = idx / (21 * 28);
      int v = (idx / 28) % 21;
      int t = idx % 28;

      int lj = ljamos[l];
      {
	w_char ch;
	ch.h = lj >> 8;
	ch.l = lj & 0xFF;
	u16_dest.push_back(ch);
      }

      int vj = vjamos[v];
      if (vj & 0x8000) {
	  const int* vjs = vjamos_comp[vj & 0xF];
	  w_char chs[2];
	  chs[0].h = vjs[0] >> 8;
	  chs[0].l = vjs[0] & 0xFF;
	  chs[1].h = vjs[1] >> 8;
	  chs[1].l = vjs[1] & 0xFF;
	  u16_dest.push_back(chs[0]);
	  u16_dest.push_back(chs[1]);
      } else {
	w_char ch;
	ch.h = vj >> 8;
	ch.l = vj & 0xFF;
	u16_dest.push_back(ch);
      }

      if (t != 0) {
	int tj = tjamos[t];

	if (tj & 0x8000) {
	  const int* tjs = tjamos_comp[tj & 0xF];
	  w_char chs[2];
	  chs[0].h = tjs[0] >> 8;
	  chs[0].l = tjs[0] & 0xFF;
	  chs[1].h = tjs[1] >> 8;
	  chs[1].l = tjs[1] & 0xFF;
	  u16_dest.push_back(chs[0]);
	  u16_dest.push_back(chs[1]);
	} else {
	  w_char ch;
	  ch.h = tj >> 8;
	  ch.l = tj & 0xFF;
	  u16_dest.push_back(ch);
	}
	state = LAST_IS_C;
      } else {
	state = LAST_IS_V;
      }
    } else if ((chord >= 0x3131) && (chord <= 0x3163)) {
      // compatibility jamos
      bool is_c = (chord <= 0x314E);
      if ((state == LAST_IS_V) && is_c) {
	u16_dest.push_back(code_reset);
      } else if ((state == LAST_IS_C) && (! is_c)) {
	u16_dest.push_back(code_reset);
      }

      w_char ch;
      ch.h = chord >> 8;
      ch.l = chord & 0xFF;
      u16_dest.push_back(ch);
    } else {
      state = INITIAL;

      w_char ch;
      ch.h = chord >> 8;
      ch.l = chord & 0xFF;
      u16_dest.push_back(ch);
    }
  }

  u16_u8(dest, u16_dest);
  return true;
}

bool ConverterKoreanImpl::output_conv(const std::string& src,
					    std::string& dest) const
{
  std::vector<w_char> u16;
  std::vector<w_char> u16_dest;
  int nchar;

  nchar = u8_u16(u16, src);

  for (int idx = 0; idx < nchar; ++idx) {
    w_char ch = u16[idx];
#if 0
    if (ch == code_reset) {

    }
    else if (ch >= 0xAC00 && ch <= 0xD7A3) {
      // Hangul syllable
      //u16_dest.append();

      int l;
      int v;
      int t;

    }
#endif
    u16_dest.push_back(ch);
  }

  u16_u8(dest, u16_dest);
  return true;
}
