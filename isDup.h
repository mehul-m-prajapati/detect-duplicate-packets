/*
 * Author: Mehul Prajapati
 * Date: 27/02/2017
 */

#ifndef __IS_DUP_H__
#define __IS_DUP_H__

/*
 *  @Includes
 */
#include "md5.h"

/*
 * @Defines
 */
#define DEFAULT_DUP_DEPTH 				5     	  /* Used with -d in editcap */
#define MAX_DUP_DEPTH 					1000000   /* the maximum window (and actual size of fd_hash[]) for de-duplication */
#define DEDUP_FILENAME					"/tmp/dedup-window"

/*
 * @Datatypes
 */
typedef struct
{
	time_t	secs;
	int	nsecs;
} nstime_t;

/*
 * Duplicate frame detection
 */
typedef struct _fd_hash_t
{
  md5_byte_t digest[16];
  uint32_t len;
 // nstime_t time;
} fd_hash_t;

#if 0
typedef struct
{
	fd_hash_t fd_hash[MAX_DUP_DEPTH];
	uint32_t cur_dup_entry;
	uint32_t dup_window;

} dedup_t;
#endif

/*
 * @function prototypes
 */
//bool is_dup_init(dedup_t *pDedup, int window_size);
bool is_duplicate(uint32_t window_size, uint8_t *packetBuf, uint32_t packetLen);


#endif //__IS_DUP_H__
