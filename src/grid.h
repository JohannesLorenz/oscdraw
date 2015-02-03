/*************************************************************************/
/* oscdraw - an OSC draw utility                                         */
/* Copyright (C) 2014-2014                                               */
/* Johannes Lorenz (jlsf2013 @ sourceforge)                              */
/*                                                                       */
/* This program is free software; you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation; either version 3 of the License, or (at */
/* your option) any later version.                                       */
/* This program is distributed in the hope that it will be useful, but   */
/* WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      */
/* General Public License for more details.                              */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program; if not, write to the Free Software           */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  */
/*************************************************************************/

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstdint>

namespace oscdraw {

struct point_t
{
	int x, y;
	point_t(int x, int y) : x(x), y(y) {}
};

using color_t = uint8_t;
using raw_t = uint32_t;

union argb_t
{
	color_t _array[4];
	raw_t _raw;

	constexpr argb_t(color_t a, color_t r, color_t g, color_t b) :
		_array { a, r, g, b} {}
	constexpr argb_t(color_t r, color_t g, color_t b) :
		argb_t(255, r, g, b) {}

	constexpr static argb_t white() { return argb_t(255, 255, 255); }

	raw_t raw() const { return _raw; }
};

struct grid_t
{
	int w, h;
	std::vector<raw_t> values;
public:
	grid_t(int w, int h) : w(w), h(h), values(w * h, argb_t::white().raw()) {}
	raw_t& operator[](const point_t& p) { return values[p.y * w + p.x]; }
	void flood(argb_t argb) {
		std::fill(values.begin(), values.end(), argb.raw());
	}

	void save_png(const char* filename);
};

}

#endif // GRID_H
