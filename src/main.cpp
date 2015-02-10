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

#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include "lo_server.h"

#include "image.h"

constexpr float sleep_time_us = 1000000.0f / 60.0f; // 60 fps

int main()
{
	oscdraw::image_t img;
	oscdraw::image_server_t srv(&img);

	auto start = std::chrono::system_clock::now();

	for(int counter = 1; ! srv.exit(); ++counter)
	{
		srv.listen();

		auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(
			std::chrono::system_clock::now() - start);

		usleep(sleep_time_us * counter - duration.count());
	}

	img.grid.save_png("result.png");

	return EXIT_SUCCESS;
}
