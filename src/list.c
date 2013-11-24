#include "list.h"

list addToList(list source, uint value)
{
    list pElement, pNewElement = calloc(1, sizeof(*pNewElement));

    pNewElement->value = value;

    if(!source)
	return pNewElement;
    else if(value < source->value)
    {
	pNewElement->next = source;
	return pNewElement;
    }

    pElement = source;
    while(pElement->next && pElement->next->value < value)
	pElement = pElement->next;

    if(pElement->value != value)
    {
	pNewElement->next = pElement->next;
	pElement->next = pNewElement;
    }

    return source;
}

list rmToList(list source, uint value)
{
    list pElement, pRmElement;

    if(!source)
    {
	WARNING_MSG("Nothing to remove\n");
	return NULL;
    }
    if(source->value == value)
    {
	pElement = source->next;
	free(source);
	return pElement;
    }
    while(pElement->next && pElement->next->value != value)
	pElement = pElement->next;
    if(!pElement->next)
	WARNING_MSG("No element with 0x%x value\n");
    else
    {
	pRmElement = pElement->next;
	pElement->next = pRmElement->next;
	free(pRmElement);
    }

    return source;
}

int lookFor(const list source, const uint value)
{
    list pElement;

    if(!source)
	return 0;

    pElement = source;
    while(pElement->value != value && pElement->next)
	pElement = pElement->next;

    if(pElement->value == value)
	return 1;

    return 0;
}

