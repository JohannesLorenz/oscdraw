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
#include <algorithm>
#include <cstring>
#include <lo/lo.h>
#include "lo_server.h"

namespace oscdraw {

int on_receive(const char *path, const char* /* types */, lo_arg** /* argv */,
	int /* argc*/, lo_message msg, void* user_data)
//int on_receive(const char *path, const char *, lo_arg **, int, lo_message msg, void *)
{

	char buffer[2048];
	std::fill_n(buffer, sizeof(buffer), 0);
	size_t size = 2048;
	lo_message_serialise(msg, path, buffer, &size);

	image_server_t& img_srv = *(reinterpret_cast<image_server_t*>(user_data));

	img_srv.apply_msg(buffer);

	/*if(!strcmp("/flood", buffer))
	{
		std::cerr << "/flood" << std::endl;
		img.grid.flood(argb_t(255, 0, 0));
	}
	else
	 std::cerr << buffer << std::endl;

*/

#if 0
	static char buffer[1024*20];
	memset(buffer, 0, sizeof(buffer));
	size_t size = sizeof(buffer);
	lo_message_serialise(msg, path, buffer, &size);
	if(!strcmp("/paths", buffer)) // /paths:sbsbsbsbsb...
	update_paths(buffer, NULL);
	else if(!strcmp("/exit", buffer))
	die_nicely(buffer, NULL);
	else if(status_url == path)
	update_status_info(buffer);
	else if(!strcmp("undo_change", buffer))
	;//ignore undo messages
	else
	display(buffer, NULL);

	return 0;
#else
	(void)path;
	(void)msg;
	return 0;
#endif
}

void error_cb(int i, const char *m, const char *loc)
{
	fprintf(stderr, "liblo :-( %d-%s@%s\n",i,m,loc);
}

lo_server_t::lo_server_t()
	: srv(lo_server_new_with_proto(nullptr, LO_UDP, error_cb))
{
	fprintf(stderr, "lo server running on %d\n", lo_server_get_port(srv));
}

lo_server_t::~lo_server_t()
{
	lo_server_free(srv);
}

void lo_server_t::listen()
{
	lo_server_recv_noblock(srv, 0);
	/*while(bToU->hasNext()) {
		const char *rtmsg = bToU->read();
		bToUhandle(rtmsg);
	}*/
}

void image_server_t::apply_msg(const char *buffer)
{
	if(!strcmp("/flood", buffer))
	{
		std::cerr << "/flood" << std::endl;
		img->grid.flood(argb_t(255, 0, 0));
	}
	else if(!strcmp("/exit", buffer))
	{
		_exit = true;
	}
	else
	 std::cerr << "unknown cmd: " << buffer << std::endl;
}

image_server_t::image_server_t(image_t *img) : img(img) {
	lo_server_add_method(srv, nullptr, nullptr, on_receive, this);
}


}


