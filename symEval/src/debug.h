/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _SYMEVAL_DEBUG_H_
#define _SYMEVAL_DEBUG_H_

#include <string>

extern int sym_debug_slicing;
extern int sym_debug_stackanalysis;
extern int sym_debug_convert;
extern int sym_debug_expand;

#define slicing_cerr       if (sym_debug_slicing) cerr
#define stackanalysis_cerr if (sym_debug_stackanalysis) cerr
#define convert_cerr       if (sym_debug_convert) cerr
#define expand_cerr        if (sym_debug_expand) cerr

extern int slicing_printf_int(const char *format, ...);
extern int sym_stackanalysis_printf_int(const char *format, ...);
extern int convert_printf_int(const char *format, ...);
extern int expand_printf_int(const char *format, ...);

#if defined(__GNUC__)
#define slicing_printf(format, args...) do {if (sym_debug_slicing) slicing_printf_int(format, ## args); } while(0)
#define sym_stackanalysis_printf(format, args...) do {if (sym_debug_stackanalysis) sym_stackanalysis_printf_int(format, ## args); } while(0)
#define convert_printf(format, args...) do {if (sym_debug_convert) convert_printf_int(format, ## args); } while(0)
#define expand_printf(format, args...) do {if (sym_debug_expand) expand_printf_int(format, ## args); } while(0)

#else
// Non-GCC doesn't have the ## macro
#define slicing_printf slicing_printf_int
#define sym_stackanalysis_printf sym_stackanalysis_printf_int
#define convert_printf convert_printf_int
#define expand_printf expand_printf_int


#endif

// And initialization
extern bool symeval_init_debug();

#endif /* SHOWERROR_H */
