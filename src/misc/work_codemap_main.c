
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**** Mem_allocCount ****/
static int Mem_allocCount = 0;

/**** Mem_ialloc ****/
void *Mem_alloc(int size)
{
  ++Mem_allocCount;
  return malloc(size);
}

/**** Mem_free ****/
void Mem_free(void *mem)
{
  free(mem);
  --Mem_allocCount;
}

/**** Mem_showCount ****/
void Mem_showCount()
{
  printf("Mem_allocCount: %d\n", Mem_allocCount);
}

#define malloc(x) Mem_alloc(x)
#define free(x) Mem_free(x)


#define CODEMAP_NOTFOUND (-1)
#define CODEMAP_MAXINDEX (0x100)
#define IDX0 (3)
#define IDX1 (2)
#define IDX2 (1)
#define IDX3 (0)

/**** CodeMap CodeMapStruct ****/
typedef struct {
  int ****map;
} CodeMapStruct, *CodeMap;

/**** CodeMapIndex ****/
typedef union {
  int idx;
  unsigned char idxs[4];
} CodeMapIndex;

/*
******************************************************************************************
CodeMap_create
文字マッピングテーブル作成
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
文字マッピングテーブル削除
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
文字マッピングに値を設定
******************************************************************************************
*/
void CodeMap_set(CodeMap cmap, int idx, int val)
{
  CodeMapIndex mapidx;

  mapidx.idx = idx;
  printf("cm set %02x %02x %02x %02x = %04x\n",
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3], val);

  int ****map0 = cmap->map;
  if (! map0) {
    cmap->map = map0 = malloc(CODEMAP_MAXINDEX * sizeof (*map0));
    printf("0 %d\n", sizeof (*map0));
    memset(map0, 0, CODEMAP_MAXINDEX * sizeof (*map0));
  }

  int  ***map1 = map0[mapidx.idxs[IDX0]];
  if (! map1) {
    map0[mapidx.idxs[IDX0]] = map1 = malloc(CODEMAP_MAXINDEX * sizeof (*map1));
    printf("1 %d\n", sizeof (*map1));
    memset(map1, 0, CODEMAP_MAXINDEX * sizeof (*map1));
  }

  int   **map2 = map1[mapidx.idxs[IDX1]];
  if (! map2) {
    map1[mapidx.idxs[IDX1]] = map2 = malloc(CODEMAP_MAXINDEX * sizeof (*map2));
    printf("2 %d\n", sizeof (*map2));
    memset(map2, 0, CODEMAP_MAXINDEX * sizeof (*map2));
  }

  int    *map3 = map2[mapidx.idxs[IDX2]];
  if (! map3) {
    map2[mapidx.idxs[IDX2]] = map3 = malloc(CODEMAP_MAXINDEX * sizeof (*map3));
    printf("3 %d\n", sizeof (*map3));
    memset(map3, 0, CODEMAP_MAXINDEX * sizeof (*map3));
  }

  map3[mapidx.idxs[IDX3]] = val;
}

/*
******************************************************************************************
CodeMap_get
文字マッピングの値を取得
******************************************************************************************
*/
int CodeMap_get(CodeMap cmap, int idx)
{
  CodeMapIndex mapidx;

  mapidx.idx = idx;
  printf("cm get %02x %02x %02x %02x\n",
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3]);

  int ****map0 = cmap->map;
  if (! map0) return CODEMAP_NOTFOUND;

  int  ***map1 = map0[mapidx.idxs[IDX0]];
  if (! map1) return CODEMAP_NOTFOUND;

  int   **map2 = map1[mapidx.idxs[IDX1]];
  if (! map2) return CODEMAP_NOTFOUND;

  int    *map3 = map2[mapidx.idxs[IDX2]];
  if (! map3) return CODEMAP_NOTFOUND;

  printf("cm get %02x %02x %02x %02x = %04x\n", 
    mapidx.idxs[IDX0], mapidx.idxs[IDX1], mapidx.idxs[IDX2], mapidx.idxs[IDX3],
    map3[mapidx.idxs[IDX3]]);
  return map3[mapidx.idxs[IDX3]];
}


/*
******************************************************************************************
main
メイン
******************************************************************************************
*/
int main (int argc, char**argv, char **envp)
{
  printf("char   %d\n", sizeof(char));
  printf("short  %d\n", sizeof(short));
  printf("int    %d\n", sizeof(int));
  printf("long   %d\n", sizeof(long));
  printf("float  %d\n", sizeof(float));
  printf("double %d\n", sizeof(double));

  Mem_showCount();

  CodeMap cmap;

  cmap = CodeMap_create();
  Mem_showCount();

  printf("main cm 0 = %d\n", CodeMap_get(cmap, 0));
  CodeMap_set(cmap, 0, 0);
  Mem_showCount();
  printf("main cm 0 = %d\n", CodeMap_get(cmap, 0));

  printf("main cm 1 = %d\n", CodeMap_get(cmap, 1));
  CodeMap_set(cmap, 1, 0);
  Mem_showCount();
  printf("main cm 1 = %d\n", CodeMap_get(cmap, 1));

  printf("main cm 100 = %d\n", CodeMap_get(cmap, 0x100));
  CodeMap_set(cmap, 0x100, 0);
  Mem_showCount();
  printf("main cm 100 = %d\n", CodeMap_get(cmap, 0x100));

  CodeMap_delete(cmap);
  Mem_showCount();
}

