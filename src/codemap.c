
#include "codemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**** Mem_allocCount ****/
static int Mem_allocCount = 0;
static int Mem_allocBytes = 0;

/**** Mem_alloc ****/
static void *Mem_alloc(int size)
{
  ++Mem_allocCount;
  Mem_allocBytes += size;
  return malloc(size);
}

/**** Mem_free ****/
static void Mem_free(void *mem)
{
  free(mem);
  --Mem_allocCount;
}

/**** Mem_showCount ****/
static void Mem_showCount()
{
  printf("CodeMap Mem_allocCount: %5d  CumulatedBytes:%8d (%d KiB)\n", 
    Mem_allocCount, Mem_allocBytes, (Mem_allocBytes + 1023)/1024);
}

#define malloc(x) Mem_alloc(x)
#define free(x) Mem_free(x)


#define IDX0 (3)
#define IDX1 (2)
#define IDX2 (1)
#define IDX3 (0)

/**** CodeMapIndex ****/
typedef union {
  int idx;
  unsigned char idxs[4];
} CodeMapIndex;

/*
******************************************************************************************
CodeMap_create
文字コードマッピングテーブル作成
******************************************************************************************
*/
CodeMap CodeMap_create()
{
  CodeMap cmap = malloc(sizeof(CodeMapStruct));
  cmap->map = 0;
  return cmap;
}

/*
******************************************************************************************
CodeMap_delete
文字コードマッピングテーブル削除
******************************************************************************************
*/
void CodeMap_delete(CodeMap cmap)
{
  int ****map0 = cmap->map;
  if (map0) {
    int i0, i1, i2;

    for (i0 = 0; i0 < CODEMAP_MAXINDEX; ++i0) {
      int ***map1 = map0[i0];
      if (! map1) continue;

      for (i1 = 0; i1 < CODEMAP_MAXINDEX; ++i1) {
        int **map2 = map1[i1];
        if (! map2) continue;

        for (i2 = 0; i2 < CODEMAP_MAXINDEX; ++i2) {
          int *map3 = map2[i2];
          if (! map3) continue;

          memset(map3, 0, CODEMAP_MAXINDEX * sizeof (*map3));
          free(map3);
          map2[i2] = map3 = 0;
        }
        memset(map2, 0, CODEMAP_MAXINDEX * sizeof (*map2));
        free(map2);
        map1[i1] = map2 = 0;
      }
      memset(map1, 0, CODEMAP_MAXINDEX * sizeof (*map1));
      free(map1);
      map0[i0] = map1 = 0;
    }
    memset(map0, 0, CODEMAP_MAXINDEX * sizeof (*map0));
    free(map0);
    cmap->map = map0 = 0;
  }

  free(cmap);
  return;
}

/*
******************************************************************************************
CodeMap_set
文字コードマッピングに値を設定
******************************************************************************************
*/
void CodeMap_set(CodeMap cmap, int idx, int val)
{
  CodeMapIndex mapidx;
  int ****map0;
  int ***map1;
  int **map2;
  int *map3;

  mapidx.idx = idx;

#if CODEMAP_DEBUG
  printf("CodeMap set[%02x %02x %02x %02x]= %04x\n",
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3], val);
#endif

  map0 = cmap->map;
  if (! map0) {
    cmap->map = map0 = malloc(CODEMAP_MAXINDEX * sizeof (*map0));
#if CODEMAP_DEBUG
    printf("CodeMap set 0 %d\n", sizeof (*map0));
#endif
    memset(map0, 0, CODEMAP_MAXINDEX * sizeof (*map0));
  }

  map1 = map0[mapidx.idxs[IDX0]];
  if (! map1) {
    map0[mapidx.idxs[IDX0]] = map1 = malloc(CODEMAP_MAXINDEX * sizeof (*map1));
#if CODEMAP_DEBUG
    printf("CodeMap set 1 %d\n", sizeof (*map1));
#endif
    memset(map1, 0, CODEMAP_MAXINDEX * sizeof (*map1));
  }

  map2 = map1[mapidx.idxs[IDX1]];
  if (! map2) {
    map1[mapidx.idxs[IDX1]] = map2 = malloc(CODEMAP_MAXINDEX * sizeof (*map2));
#if CODEMAP_DEBUG
    printf("CodeMap set 2 %d\n", sizeof (*map2));
#endif
    memset(map2, 0, CODEMAP_MAXINDEX * sizeof (*map2));
  }

  map3 = map2[mapidx.idxs[IDX2]];
  if (! map3) {
    map2[mapidx.idxs[IDX2]] = map3 = malloc(CODEMAP_MAXINDEX * sizeof (*map3));
#if CODEMAP_DEBUG
    printf("CodeMap set 3 %d\n", sizeof (*map3));
#endif
    memset(map3, 0, CODEMAP_MAXINDEX * sizeof (*map3));
  }

  map3[mapidx.idxs[IDX3]] = val;
}

/*
******************************************************************************************
CodeMap_get
文字コードマッピングの値を取得
******************************************************************************************
*/
int CodeMap_get(CodeMap cmap, int idx)
{
  CodeMapIndex mapidx;
  int ****map0;
  int ***map1;
  int **map2;
  int *map3;

  mapidx.idx = idx;
#if CODEMAP_DEBUG
  printf("CodeMap get[%02x %02x %02x %02x]\n",
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3]);
#endif

  map0 = cmap->map;
  if (! map0) return CODEMAP_NOTFOUND;

  map1 = map0[mapidx.idxs[IDX0]];
  if (! map1) return CODEMAP_NOTFOUND;

  map2 = map1[mapidx.idxs[IDX1]];
  if (! map2) return CODEMAP_NOTFOUND;

  map3 = map2[mapidx.idxs[IDX2]];
  if (! map3) return CODEMAP_NOTFOUND;

#if CODEMAP_DEBUG
  printf("CodeMap get[%02x %02x %02x %02x]-> %04x\n", 
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3],
    map3[mapidx.idxs[IDX3]]);
#endif
  return map3[mapidx.idxs[IDX3]];
}

/*
******************************************************************************************
CodeMap_showCount
文字コードマッピングのカウント値を表示する
******************************************************************************************
*/
int CodeMap_showCount()
{
  Mem_showCount();
}

