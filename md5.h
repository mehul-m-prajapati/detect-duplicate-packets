/* $Id: md5.h 47992 2013-03-01 23:53:11Z rbalint $ */
/* 
 * Copyright (C) 2003-2005 Benny Prijono <benny@prijono.org>
 * Copyright (C) 2012      C Elston, Katalix Systems Ltd <celston@katalix.com>
 *
 * MD5 code from pjlib-util http://www.pjsip.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA 
 * 
 *  2012-08-21 - C Elston - Split md5_hmac function to allow incremental usage.
 *
 */
#ifndef __MD5_H__
#define __MD5_H__

/*
 * @Includes
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @file md5.h
 * @brief MD5 Functions
 */

/* Don't define this group for Wireshark
 * @defgroup PJLIB_UTIL_MD5 MD5 Functions
 * @ingroup PJLIB_UTIL
 * @{
 */

#define md5_byte_t uint8_t

/** MD5 context. */
typedef struct md5_state_s
{
	uint32_t buf[4];
	uint32_t bits[2];
	uint32_t in[16];
} md5_state_t;

/** Initialize the algorithm. 
 *  @param pms		MD5 context.
 */
void md5_init(md5_state_t *pms);

/** Append a string to the message. 
 *  @param pms		MD5 context.
 *  @param data		Data.
 *  @param nbytes	Length of data.
 */
void md5_append( md5_state_t *pms, 
			     const uint8_t *data, size_t nbytes);

/** Finish the message and return the digest. 
 *  @param pms		MD5 context.
 *  @param digest	16 byte digest.
 */
void md5_finish(md5_state_t *pms, uint8_t digest[16]);

/*
 * @}
 */

#endif	/* __MD5_H__ */
