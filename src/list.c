#include "list.h"

list initList()
{
    return NULL;
}

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

    if(!pElement->next || pElement->next->value != value)
    {
	pNewElement->next = pElement->next;
	pElement->next = pNewElement;
    }
    else
	free(pNewElement);

    return source;
}

list rmFromList(list source, uint value)
{
    list pElement, pRmElement;

    if(!source)
    {
	WARNING_MSG("Nothing to remove");
	return NULL;
    }
    if(source->value == value)
    {
	pElement = source->next;
	free(source);
	return pElement;
    }
    pElement = source;
    while(pElement->next && pElement->next->value != value)
	pElement = pElement->next;
    if(!pElement->next)
	WARNING_MSG("No element with 0x%x value", value);
    else
    {
	pRmElement = pElement->next;
	pElement->next = pRmElement->next;
	free(pRmElement);
    }

    return source;
}

// look for the minimum over value
uint minOver(const list source, const uint value)
{
    list pElement;

    if(!source)
	return 0;

    pElement = source;
    while(pElement->value <= value && pElement->next)
	pElement = pElement->next;

    if(pElement->value > value)
	return pElement->value;

    return 0;
}

void printList(const list source)
{
    list pElement;

    if(!source)
	printf("Empty list\n");
    else
    {
	pElement = source;
	while(pElement)
	{
	    printf("0x%x\n", pElement->value);
	    pElement = pElement->next;
	}
    }
}
