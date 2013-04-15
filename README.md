CodeMap.c
==========================

LightSpeedWorks pages {光速工房}

Character code mapping virtual array library for C
{文字コードマッピング仮想配列ライブラリ(C向け)}

[LightSpeedWorks/CodeMap.c#readme] (https://github.com/LightSpeedWorks/CodeMap.c#readme "LightSpeedWorks/CodeMap.c#readme")

## usage: {使用方法:}

## CodeMap_create(), CodeMap_delete(CodeMap map)
## CodeMap_get(CodeMap map, int index)
## CodeMap_set(CodeMap map, int index, int value)

```c
#include "codemap.h"

main()
{
  CodeMap cmap;
  int idx, code;

  /* first, create/allocate */
  cmap = CodeMap_create();

  idx = 0x3000;

  code = CodeMap_get(cmap, idx);    /* get --> (-1) */
  CodeMap_set(cmap, idx, 0x25A0);   /* set new value --> cmap[idx] = val */
  code = CodeMap_get(cmap, idx);    /* get the value --> cmap[idx] */

  /* last, delete/free */
  CodeMap_delete(cmap);
}
```

See also: https://github.com/LightSpeedWorks/CodeMap.c/blob/master/doc/codemap.xls

That's all.
