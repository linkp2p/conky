/* -*- mode: c; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*-
 * vim: ts=4 sw=4 noet ai cindent syntax=c
 *
 * Conky, a system monitor, based on torsmo
 *
 * Any original torsmo code is licensed under the BSD license
 *
 * All code written since the fork of torsmo is licensed under the GPL
 *
 * Please see COPYING for details
 *
 * Copyright (c) 2004, Hannu Saransaari and Lauri Hakkarainen
 * Copyright (c) 2005-2010 Brenden Matthews, Philip Kovacs, et. al.
 *	(see AUTHORS)
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "config.h"
#include "conky.h"
#include "text_object.h"

/* check for OS and include appropriate headers */
#if defined(__linux__)
#include "linux.h"
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#include "freebsd.h"
#elif defined(__OpenBSD__)
#include "openbsd.h"
#endif

static struct {
	unsigned int avail;
	unsigned int poolsize;
} entropy = {
	.avail = 0,
	.poolsize = 0,
};

void update_entropy(void)
{
	get_entropy_avail(&entropy.avail);
	get_entropy_poolsize(&entropy.poolsize);
}

void print_entropy_avail(struct text_object *obj, char *p, int p_max_size)
{
	(void)obj;
	snprintf(p, p_max_size, "%u", entropy.avail);
}

void print_entropy_perc(struct text_object *obj, char *p, int p_max_size)
{
	(void)obj;
	percent_print(p, p_max_size, entropy.avail *
			100 / entropy.poolsize);
}

void print_entropy_poolsize(struct text_object *obj, char *p, int p_max_size)
{
	(void)obj;
	snprintf(p, p_max_size, "%u", entropy.poolsize);
}

void print_entropy_bar(struct text_object *obj, char *p, int p_max_size)
{
	double ratio;

	(void)obj;

	ratio = (double) entropy.avail /
		(double) entropy.poolsize;
	new_bar(obj, p, p_max_size, (int) (ratio * 255.0f));
}
