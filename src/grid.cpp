/*************************************************************************/
/* oscdraw - an OSC draw utility                                         */
/* Copyright (C) 2014-2015                                               */
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

#include <iostream>
#include <fstream>

#include <Magick++.h>
#include <magick/methods.h>

#include "grid.h"

namespace oscdraw {

void grid_t::save_png(const char *filename)
{
	try {
		const std::string format = "ARGB";
		std::ofstream ofs(filename);

		Magick::Blob blob2;
		Magick::Image img2(w, h, format,
			Magick::CharPixel, values.data());
		// needed, otherwise we write "format-less":
		img2.magick("PNG");
		img2.write(&blob2);

		ofs.write(reinterpret_cast<const char*>(blob2.data()), blob2.length());
	}
	catch ( Magick::Exception & error) {
		std::cerr << "Caught Magick++ exception: "
			<< error.what() << std::endl;
	}
}

}

