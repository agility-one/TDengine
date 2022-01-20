/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TD_TDB_MPOOL_H_
#define _TD_TDB_MPOOL_H_

#include "tdb_inc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Exposed handle
typedef struct TDB_MPOOL  TDB_MPOOL;
typedef struct TDB_MPFILE TDB_MPFILE;

typedef TD_DLIST_NODE(pg_t) pg_free_list_node_t, pg_hash_list_node_t;
typedef struct pg_t {
  SRWLatch            rwLatch;
  frame_id_t          frameid;
  pgid_t              pgid;
  uint8_t             dirty;
  int32_t             pinRef;
  pg_free_list_node_t free;
  pg_hash_list_node_t hash;
  uint8_t             data[];
} pg_t;

#define MP_PAGE_SIZE(pgsize) (sizeof(pg_t) + (pgsize))

typedef TD_DLIST(pg_t) pg_list_t;
struct TDB_MPOOL {
  int64_t   cachesize;
  pgsize_t  pgsize;
  int32_t   npages;
  pg_t **   pages;
  pg_list_t freeList;
  struct {
    int32_t    nbucket;
    pg_list_t *hashtab;
  } pgtab;  // page table, hash<pgid_t, pg_t>
};

#define MP_PAGE_AT(mp, idx) (mp)->pages[idx]

struct TDB_MPFILE {
  char *     fname;                    // file name
  int        fd;                       // fd
  uint8_t    fileid[TDB_FILE_ID_LEN];  // file ID
  TDB_MPOOL *mp;                       // underlying memory pool
};

/*=================================================== Exposed apis ==================================================*/
// TDB_MPOOL
int tdbMPoolOpen(TDB_MPOOL **mpp, uint64_t cachesize, pgsize_t pgsize);
int tdbMPoolClose(TDB_MPOOL *mp);

// TDB_MPFILE
int tdbMPoolFileOpen(TDB_MPFILE **mpfp, const char *fname, TDB_MPOOL *mp);
int tdbMPoolFileClose(TDB_MPFILE *mpf);
int tdbMPoolFileGet(TDB_MPFILE *mpf, pgno_t pgid, void *addr);
int tdbMPoolFilePut(TDB_MPOOL *mpf, pgno_t pgid, void *addr);

#ifdef __cplusplus
}
#endif

#endif /*_TD_TDB_MPOOL_H_*/