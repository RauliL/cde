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
/* $XConsortium: getconf.c /main/3 1995/11/01 16:28:05 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*        THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF        *
*                    AT&T BELL LABORATORIES                    *
*         AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN         *
*            ACCORDANCE WITH APPLICABLE AGREEMENTS             *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*              Unpublished & Not for Publication               *
*                     All Rights Reserved                      *
*                                                              *
*       The copyright notice above does not evidence any       *
*      actual or intended publication of such source code      *
*                                                              *
*               This software was created by the               *
*           Advanced Software Technology Department            *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                    {research,attmail}!dgk                    *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
#include	<shell.h>
#include	<ast.h>
#include	<stak.h>
#include	<error.h>
#include	"shtable.h"
#include	"builtins.h"
#include	"FEATURE/externs"

#define next_config(p)	((Shtable_t*)((char*)(p) + sizeof(*shtab_config)))
#define MIN_LEN	20

int	b_getconf __PARAM__((int argc, char *argv[]), (argc, argv)) __OTORP__(int argc; char *argv[];){
	int m,n;
	long val;
	const char *name, *path="";
	int offset = staktell();
	const Shtable_t *tp = shtab_config;
	error_info.id = argv[0];
	while (n = optget(argv, sh_optgetconf)) switch (n)
	{
	    case ':':
		error(2, opt_arg);
		break;
	    case '?':
		error(ERROR_usage(2), opt_arg);
		break;
	}
	argv += opt_index;
	argc -= opt_index;
	if(argc >2)
		error(ERROR_usage(2),optusage((char*)0));
	while(1)
	{
		if(argc)
		{
			name = *argv;
			n = sh_lookup(name,shtab_config);
		}
		else
		{
			name = tp->sh_name;
			n = tp->sh_number;
			if(*name==0)
				break;
		}
		m = n>>2;
		errno = 0;
		val = -1;
		switch(n&03)
		{
		    case 0:
			if(m==0)
				errno = EINVAL;
			break;
		    case 1:
#ifdef _lib_confstr
			stakseek(offset+MIN_LEN);
			if((n=confstr(m,stakptr(offset),MIN_LEN)) > MIN_LEN)
			{
				stakseek(offset+n);
				confstr(m,stakptr(offset),n);
			}
#else
			if(strcmp(name,"PATH"))
				errno = EINVAL;
			else
				stakputs(e_defpath);
#endif /* _lib_confstr */
			val = 0;
			break;
	 	    case 2:
			val = sysconf(m);
			break;
		    case 3:
			if(argc==0)
				path = "/";
			else if(argc!=2)
				error(ERROR_exit(1),e_needspath,name);
			else
				path=argv[1];
			val = pathconf(path,m);
			break;
		}
		if(errno)
			error(ERROR_system(0),e_badconf,name,path);
		path= "";
		if(argc==0)
			sfputr(sfstdout,name,'=');
		if(val==-1)
			sfputr(sfstdout,"undefined",'\n');
		else if((n&03)==1)
			sfputr(sfstdout,stakptr(offset),'\n');
		else
			sfprintf(sfstdout,"%ld\n",val);
		if(argc)
			break;
		tp= next_config(tp);
		val = -1;
	}
	stakseek(offset);
	return(error_info.errors);
}
