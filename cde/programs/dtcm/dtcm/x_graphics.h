/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: x_graphics.h /main/5 1996/06/07 13:24:06 rswiston $ */
/*
 * (c) Copyright 1996 Digital Equipment Corporation.
 * (c) Copyright 1996 Hewlett-Packard Company.
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc. 
 * (c) Copyright 1996 FUJITSU LIMITED.
 * (c) Copyright 1996 Hitachi.
 */

#ifndef _X_GRAPHICS_H
#define _X_GRAPHICS_H

#include <csa.h>
#include "calendar.h"
#include "print.h"
#include <X11/Intrinsic.h>

#define PAGE_WIDTH	8500	/*  8.5"  paper width */
#define PAGE_HEIGHT	11000	/* 11.0"  paper height */
#define XINCH		1000	/*  1 inch */

extern void	x_day_header(void *);
extern void	x_day_timeslots(void *, int, Boolean);
extern void	x_finish_printer(void *);
extern void	x_finish_std_month();
extern int	x_get_day_lines_per_page(void *);
extern int	x_get_month_lines_per_page(void *);
extern int	x_get_week_lines_per_page(void *);
extern void	x_init_day(void *, int);
extern void	x_init_list(void *);
extern void	x_init_month(void *, int);
extern void	x_init_printer(void *, short);
extern void	x_init_std_year(void *);
extern void	x_init_week(void *);
extern void	x_month_daynames(void *, int);
extern void	x_month_timeslots(void *, Tick, Boolean);
extern void *	x_open_file	(Calendar *);
extern void	x_print_file(void *, Calendar *);
extern void	x_print_header(void *, char*, int, int);
extern void	x_print_list_range(Calendar*, CSA_sint32, int,
					   Tick, Tick);
extern void	x_print_little_months(void *, Tick);
extern void	x_print_month(void *, int, int, int,
					   int, int, int, int);
extern Boolean	x_print_month_appts(void *, CSA_entry_handle*, int,
					   int, time_t, int);
extern Boolean	x_print_multi_appts(void *, CSA_entry_handle*, int,
					   int, Glance);
extern void	x_print_todo(void *, CSA_entry_handle*, int,
					   CSA_sint32, Boolean, int, time_t,
					   char *);
extern void	x_print_year(void *, int);
extern void	x_std_month_name(void *, char*);
extern void	x_std_year_name(void *, int);
extern void	x_week_appt_boxes(void *);
extern void	x_week_daynames(void *, char*, int, Boolean);
extern void	x_week_sched_boxes(void *);
extern void	x_week_sched_draw(void *, int);
extern void	x_week_sched_init(void *);

#endif
