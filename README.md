CodeMap.c
==========================

LightSpeedWorks {光速工房}

Character code mapping virtual array library for C <br/>
{文字コードマッピング仮想配列ライブラリ(C向け)}

[LightSpeedWorks/CodeMap.c#readme] (https://github.com/LightSpeedWorks/CodeMap.c#readme)

## usage: {使用方法:}

### CodeMap map = CodeMap_create();
### CodeMap_delete(CodeMap map);
### int value = CodeMap_get(CodeMap map, int index);
### CodeMap_set(CodeMap map, int index, int value);

```c
#include "codemap.h"

main()
{
  CodeMap map;
  int index, value;

  /* first, create/allocate */
  map = CodeMap_create();

  index = 0x3000;

  value = CodeMap_get(map, index);    /* get --> (-1) means NOT_FOUND */
  CodeMap_set(map, index, 0x25A0);    /* set new value --> map[index] = value */
  value = CodeMap_get(map, index);    /* get the value --> map[index] */

  /* last, delete/free */
  CodeMap_delete(map);
}
```

See also: https://github.com/LightSpeedWorks/CodeMap.c/blob/master/doc/codemap.xls

That's all.
