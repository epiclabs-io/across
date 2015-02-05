/* hacked file for ACross runtime*/

// modified so that macros just return addresses 
// see ACROSS_WRITE_REG macro in ACross.h


/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.  */

/* avr/sfr_defs.h - macros for accessing AVR special function registers */

/* $Id: sfr_defs.h,v 1.18.2.1 2008/04/28 22:05:42 arcanum Exp $ */

#ifndef _AVR_SFR_DEFS_H_
#define _AVR_SFR_DEFS_H_ 1



#ifdef __ASSEMBLER__
#define _SFR_ASM_COMPAT 1
#elif !defined(_SFR_ASM_COMPAT)
#define _SFR_ASM_COMPAT 0
#endif

#ifndef __ASSEMBLER__
/* These only work in C programs.  */
#include <inttypes.h>

// JPR: Hacked this so that it just returns the address to write/read to/from

#define _MMIO_BYTE(mem_addr) (mem_addr)
#define _MMIO_WORD(mem_addr) (mem_addr)
#define _MMIO_DWORD(mem_addr) (mem_addr)

// end hack


#endif


#ifndef __SFR_OFFSET
#  if __AVR_ARCH__ >= 100
#    define __SFR_OFFSET 0x00
#  else
#    define __SFR_OFFSET 0x20
#  endif
#endif

#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define _SFR_MEM16(mem_addr) _MMIO_WORD(mem_addr)
#define _SFR_MEM32(mem_addr) _MMIO_DWORD(mem_addr)
#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define _SFR_IO16(io_addr) _MMIO_WORD((io_addr) + __SFR_OFFSET)

#define _SFR_MEM_ADDR(sfr) ((uint16_t) &(sfr))
#define _SFR_IO_ADDR(sfr) (_SFR_MEM_ADDR(sfr) - __SFR_OFFSET)
#define _SFR_IO_REG_P(sfr) (_SFR_MEM_ADDR(sfr) < 0x40 + __SFR_OFFSET)

#define _SFR_ADDR(sfr) _SFR_MEM_ADDR(sfr)


#define _SFR_BYTE(sfr) _MMIO_BYTE(_SFR_ADDR(sfr))
#define _SFR_WORD(sfr) _MMIO_WORD(_SFR_ADDR(sfr))
#define _SFR_DWORD(sfr) _MMIO_DWORD(_SFR_ADDR(sfr))

/** \name Bit manipulation */

/*@{*/
/** \def _BV
    \ingroup avr_sfr

    \code #include <avr/io.h>\endcode

    Converts a bit number into a byte value.

    \note The bit shift is performed by the compiler which then inserts the
    result into the code. Thus, there is no run-time overhead when using
    _BV(). */
    
#define _BV(bit) (1 << (bit))

/*@}*/

#ifndef _VECTOR
#define _VECTOR(N) __vector_ ## N
#endif



#endif  /* _SFR_DEFS_H_ */
