//
// Created by camelboat on 18-12-3.
//

#include "dlist.h"

int main() {
    dlist l = createDlist(DLIST_INT);
    dlistValue v;
    v.intValue = 3;
    dlistAppend(l, "c", v);
    v.intValue = 1;
    dlistAppend(l, "a", v);
    v.intValue = 2;
    v.doubleValue = 2;
    dlistAppend(l, "b", v);
    v.intValue = 5;
    dlistAppend(l, "d", v);
    v.intValue = 12;
    dlistAppend(l, "e", v);
    v.intValue = 9;
    dlistAppend(l, "q", v);
    dlistPrint(l);
    dlist l2 = createDlist(DLIST_INT);
    dlistSort(l, l2, DLIST_SORT_RAND);
    dlistSort(l, l2, DLIST_SORT_DEC);
    dlistPrint(l2);

//    dlist l = createDlist(DLIST_STR);
//    dlistValue v;
//    v.strValue = "ca";
//    dlistAppend(l, "c", v);
//    v.strValue = "aa";
//    dlistAppend(l, "a", v);
//    v.strValue = "ba";
//    dlistAppend(l, "b", v);
//    v.strValue = "da";
//    dlistAppend(l, "d", v);
//    v.strValue = "ea";
//    dlistAppend(l, "e", v);
//    v.strValue = "qa";
//    dlistAppend(l, "q", v);
//    dlistPrint(l);
//    dlist l2 = createDlist(DLIST_STR);
//    dlistSort(l, l2, DLIST_SORT_DEC);
//    dlistPrint(l2);

//dlist l = createDlist(DLIST_DOUBLE);
//dlistValue v;
//v.doubleValue = "10"
    dlistFree(l);
    dlistFree(l2);
    return 0;
}