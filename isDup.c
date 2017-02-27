/*
 * Author: Mehul Prajapati
 * Date: 27/02/2017
 */
/*
 *  @Includes
 */
#include "isDup.h"
#include <string.h>

/*
 * @function prototypes
 */

/*
 * @Globals
 */
static fd_hash_t fd_hash[MAX_DUP_DEPTH];
static int dup_window = DEFAULT_DUP_DEPTH;
static int cur_dup_entry = 0;
static uint64_t count = 0;


/*
 *  @function definitions
 */
#if 0
bool is_dup_init(dedup_t *pDedup, int window_size)
{
	int idx;

	if (NULL == pDedup)
		return false;

	pDedup->dup_window = window_size;

	pDedup->cur_dup_entry = 0;

	for (idx = 0; idx < window_size; idx++)
	{
		memset(&pDedup->fd_hash[idx].digest, 0, 16);
		pDedup->fd_hash[idx].len = 0;
	}

	return true;
}
#endif

bool is_duplicate(uint32_t window_size, uint8_t *packetBuf, uint32_t packetLen)
{
  int i;
  md5_state_t ms;

  if ((NULL == packetBuf) || (0 == window_size))
		return false;

  if (window_size < 0 || window_size > MAX_DUP_DEPTH)
  {
	  fprintf(stdout, "isDup: \"%d\" duplicate window value must be between 0 and %d inclusive.\n", window_size, MAX_DUP_DEPTH);
	  return false;
  }

  /* Set the window size */
  dup_window = window_size;

  /* Next index to store md5hash value */
  cur_dup_entry++;

  if (cur_dup_entry >= dup_window)
	  cur_dup_entry = 0;

  /* Calculate our digest */
  md5_init(&ms);
  md5_append(&ms, packetBuf, packetLen);
  md5_finish(&ms, fd_hash[cur_dup_entry].digest);	// filling up md5 hash

  fd_hash[cur_dup_entry].len = packetLen;

  /* Look for duplicates */
  for (i = 0; i < dup_window; i++)
  {
    if (i == cur_dup_entry)
      continue;

    /* Duplicate packet detected */
    if (fd_hash[i].len == fd_hash[cur_dup_entry].len &&
        memcmp(fd_hash[i].digest, fd_hash[cur_dup_entry].digest, 16) == 0)
    {
        fprintf(stdout, "\nDuplicate packet: Skipped: Len: %u, MD5 Hash: ", packetLen);

        for (i = 0; i < 16; i++)
        {
          fprintf(stdout, "%02x", (unsigned char)fd_hash[cur_dup_entry].digest[i]);
        }

        fprintf(stdout, "\n\n");
        //count++;
    	return true;
    }
  }

  /* New packet */
  fprintf(stdout, "Packet:%llu Len: %u, MD5 Hash: ", count, packetLen);

  for (i = 0; i < 16; i++)
  {
    fprintf(stdout, "%02x", (unsigned char)fd_hash[cur_dup_entry].digest[i]);
  }

  count++;
  fprintf(stdout, "\n");

  return false;
}
