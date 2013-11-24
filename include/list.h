#ifndef _LIST_H_
#define _LIST_H_

#include "notify.h"
#include "mips.h"

list addToList(list source, uint value);
list rmToList(list source, uint value);
int lookFor(const list source, const uint value);

#endif
