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
/*	Copyright (c) 1995 FUJITSU LIMITED	*/
/*	All Rights Reserved			*/

/*
 * $XConsortium: Pointer.C /main/4 1996/09/27 19:02:17 drk $
 *
 * Copyright (c) 1993 HAL Computer Systems International, Ltd.
 * All rights reserved.  Unpublished -- rights reserved under
 * the Copyright Laws of the United States.  USE OF A COPYRIGHT
 * NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE
 * SECRETS OF HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.  USE,
 * DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT THE
 * PRIOR EXPRESS WRITTEN PERMISSION OF HAL COMPUTER SYSTEMS
 * INTERNATIONAL, LTD.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject
 * to the restrictions as set forth in subparagraph (c)(l)(ii)
 * of the Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013.
 *
 *          HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.
 *                  1315 Dell Avenue
 *                  Campbell, CA  95008
 * 
 */

template <class T> 
Pointer<T>::Pointer (const Pointer<T> &pointer)
: f_pointer (pointer.f_pointer)
{
  ON_DEBUG (printf ("Pointer& (0x%p) @ 0x%p\n", f_pointer, this));
  if (f_pointer) f_pointer->reference();
}

template <class T> 
Pointer<T>::Pointer (T *pointer)
: f_pointer (pointer)
{
  ON_DEBUG (printf ("Pointer* (0x%p) @ 0x%p\n", f_pointer, this));
  if (f_pointer) f_pointer->reference();
}

#if 0
template <class T> 
Pointer<T>::Pointer (T &object)
: f_pointer (&object)
{
  if (f_pointer) f_pointer->reference();
}
#endif

template <class T> 
Pointer<T>::~Pointer()
{
  ON_DEBUG (printf ("~Pointer (0x%p) @ 0x%p\n", f_pointer, this));
  if (f_pointer) f_pointer->unreference();
}

template <class T>
Pointer<T> &
Pointer<T>::operator= (T *pointer)
{
  if (f_pointer) f_pointer->unreference();
  f_pointer = pointer;
  ON_DEBUG (printf ("Pointer = 0x%p @ 0x%p\n", f_pointer, this));
  if (f_pointer) f_pointer->reference();
  return (*this);
}

template <class T>
Pointer<T> &
Pointer<T>::operator= (const Pointer<T> &pointer)
{
  if (f_pointer) f_pointer->unreference();
  f_pointer = pointer.f_pointer;
  ON_DEBUG (printf ("Pointer<T> = 0x%p @ 0x%p\n", f_pointer, this));
  if (f_pointer) f_pointer->reference();
  return (*this);
}

template <class T>
 bool
Pointer<T>::operator== (const Pointer<T> &pointer) const
{
  ON_DEBUG (printf ("Pointer== this = 0x%p, ", this));
  ON_DEBUG (printf ("Pointer== this->f_pointer = 0x%p, ", f_pointer));
  ON_DEBUG (printf ("arg = 0x%p, ", &pointer));
  ON_DEBUG (printf ("arg->f_pointer = 0x%p\n", pointer.f_pointer));
  if ((f_pointer == NULL && pointer.f_pointer != NULL) ||
      (f_pointer != NULL && pointer.f_pointer == NULL))
    {
      ON_DEBUG (puts ("1 Done Pointer =="));
      return (0);
    }
  else if (f_pointer == pointer.f_pointer)
    {
      ON_DEBUG (puts ("2 Done Pointer =="));
      return (1);
    }
  else
    {
      ON_DEBUG (puts ("3 Done Pointer =="));
      return (*f_pointer == *pointer.f_pointer);
    }
}


template <class T>
 bool
Pointer<T>::operator!= (const Pointer<T> &pointer) const
{
  if ((f_pointer == NULL && pointer.f_pointer != NULL) ||
      (f_pointer != NULL && pointer.f_pointer == NULL))
    return (1);
  else if (f_pointer == NULL && pointer.f_pointer == NULL)
    return (0);
  else
    return (!(*f_pointer == *pointer.f_pointer));
}


template <class T>
bool
Pointer<T>::operator==(const int) const
{
  return f_pointer == NULL ;
}

template <class T>
bool
Pointer<T>::operator!=(const int) const
{
  return f_pointer != NULL ;
}
