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

#ifndef LO_SERVER_H
#define LO_SERVER_H

#include <lo/lo_types.h>

#include "image.h"

namespace oscdraw {

class lo_server_t
{
protected:
	lo_server srv;
private:
	void handle_events(); // TODO: unused?
public:
	lo_server_t();
	~lo_server_t();
	void listen();
};

class image_server_t : public lo_server_t
{
	bool _exit = false;
	image_t* img;
public:
	void apply_msg(const char* buffer);
	image_server_t(image_t* img);
	bool exit() const { return _exit; }
};

}

#endif // LO_SERVER_H
