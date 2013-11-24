#ifndef _LIST_H_
#define _LIST_H_

#include "notify.h"
#include "mips.h"

list initList();
list addToList(list source, uint value);
list rmFromList(list source, uint value);
uint minOver(const list source, const uint value);
void printList(const list source);

#endif
