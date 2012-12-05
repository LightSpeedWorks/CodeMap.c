Character code mapping virtual array library
====

https://github.com/LightSpeedC/c-codemap-lib#readme


Usage:

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

See also: https://github.com/LightSpeedC/c-codemap-lib/blob/master/doc/codemap.xls

That's all.

