/*
 * Copyright (C) 2016-2017 Andes Technology, Inc.
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

/* Install given floating-point environment.
   Copyright (C) 2004-2013 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv.h>
#include <fpu_control.h>

int
fesetenv (const fenv_t *envp)
{
#ifdef __NDS32_ABI_2FP_PLUS__
	unsigned int temp;

	_FPU_GETCW (temp);
	temp &= _FPU_RESERVED;

	if (envp == FE_DFL_ENV)
	  temp |= _FPU_DEFAULT;
	else if (envp == FE_NOMASK_ENV)
	  temp |= _FPU_IEEE;
	else
	  temp |= envp->__fpcsr & ~_FPU_RESERVED;

	_FPU_SETCW (temp);

	/* Success.  */
	return 0;
#else

	/* Unsupported, so fail.  */
	return 1;
#endif
}
