//
// Created by camelboat on 18-12-3.
//

#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct linked_list list_t;
typedef struct linked_node node_t;

struct linked_node
{
    char *name;
    dlistValue value;
    node_t *next;
    node_t *before;
};

struct linked_list
{
    dlistValueType value_type;
    node_t *first;
    size_t num;
};

static node_t *createNode(const list_t *list, const char *name, dlistValue value)
{
    node_t *newnode = malloc(sizeof(node_t));
    char *newkey = malloc(strlen(name) + 1);
    strcpy(newkey, name);
    newnode->name = newkey;
    newnode->next = NULL;
    newnode->before = NULL;
    if (list->value_type == DLIST_STR)
    {
        char *newvalue = malloc(strlen(value.strValue) + 1);
        strcpy(newvalue, value.strValue);
        newnode->value.strValue = newvalue;
    }
    else
    {
        newnode->value = value;
    }
    return newnode;
}

void swap_node(list_t *list, node_t *node_1, node_t *node_2)
{
    if (node_1->before == NULL)
    {
        list->first = node_2;
        node_t *tmp = node_2->next;
        node_2->next = node_1;
        node_2->before = NULL;
        node_1->before = node_2;
        if (tmp != NULL)
        {
            tmp->before = node_1;
            node_1->next = tmp;
        }
        else
        {
            node_1->next = NULL;
        }
    }
    else
    {
        node_t *tmp = node_2->next;
        node_t *tmp_2 = node_1->before;
        node_2->before = node_1->before;
        node_1->before = node_2;
        node_2->next = node_1;
        tmp_2->next = node_2;
        if (tmp != NULL)
        {
            tmp->before = node_1;
            node_1->next = tmp;
        }
        else
        {
            node_1->next = NULL;
        }
    }
}

void sort_list_rand(const list_t *src_list, list_t *dst_list)
{
    node_t *tmp = src_list->first;
    for (int i = 0; i < src_list->num; ++i)
    {
        dlistAppend(dst_list, tmp->name, tmp->value);
        tmp = tmp->next;
    }
    for (int i = 0; i < dst_list->num * dst_list->num; ++i)
    {
        node_t *tmp = dst_list->first;
        node_t *tmp_2 = tmp;
        for (int j = 0; j < dst_list->num-1; ++j)
        {
            tmp_2 = tmp->next;
            if (rand() % 2 == 1)
            {
                swap_node(dst_list, tmp, tmp->next);
            }
            tmp = tmp_2;
        }
    }
}

void sort_list_inc(const list_t *src_list, list_t *dst_list)
{
    node_t *tmp = src_list->first;
    for (int i = 0; i < src_list->num; ++i)
    {
        dlistAppend(dst_list, tmp->name, tmp->value);
        tmp = tmp->next;
    }
    for (int i = 0; i < dst_list->num; ++i)
    {
        node_t *tmp = dst_list->first;
        for (int j = 0; j < dst_list->num-1; ++j)
        {
            if (src_list->value_type == DLIST_INT)
            {
                if (tmp->value.intValue > tmp->next->value.intValue)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
            else if (src_list->value_type == DLIST_DOUBLE)
            {
                if (tmp->value.doubleValue > tmp->next->value.doubleValue)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
            else if (src_list->value_type == DLIST_STR)
            {
                if (strcmp(tmp->value.strValue, tmp->next->value.strValue) > 0)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
        }
    }
}

void sort_list_dec(const list_t *src_list, list_t *dst_list)
{
    node_t *tmp = src_list->first;
    for (int i = 0; i < src_list->num; ++i)
    {
        dlistAppend(dst_list, tmp->name, tmp->value);
        tmp = tmp->next;
    }
    for (int i = 0; i < dst_list->num; ++i)
    {
        node_t *tmp = dst_list->first;
        for (int j = 0; j < dst_list->num-1; ++j)
        {
            if (src_list->value_type == DLIST_INT)
            {
                if (tmp->value.intValue < tmp->next->value.intValue)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
            else if (src_list->value_type == DLIST_DOUBLE)
            {
                if (tmp->value.doubleValue < tmp->next->value.doubleValue)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
            else if (src_list->value_type == DLIST_STR)
            {
                if (strcmp(tmp->value.strValue, tmp->next->value.strValue) < 0)
                {
                    swap_node(dst_list, tmp, tmp->next);
                }
                else
                {
                    tmp = tmp->next;
                }
            }
        }
    }
}

dlist createDlist(dlistValueType type)
{
    if (type == DLIST_SORT_RAND || type == DLIST_SORT_INC
    || type == DLIST_SORT_DEC)
    {
        list_t *newlist = malloc(sizeof(list_t));
        newlist->first = NULL;
        newlist->num = 0;
        newlist->value_type = type;
        return newlist;
    }
    else
    {
        perror("type error, failed to create new list\n");
        return NULL;
    }
}

int dlistIsEmpty(dlist_const this)
{
    if (((const list_t*) this)->num == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void dlistAppend(dlist this, const char* key, dlistValue value)
{
    node_t *newnode = createNode(this, key, value);
    list_t *current_list = this;
    if (current_list->num == 0)
    {
        current_list->first = newnode;
        current_list->first->before = NULL;
        current_list->num = 1;
    }
    else
    {
        node_t *tmp = current_list->first;
        // for (int i = 0; i < current_list; ++i)
        for (int i = 0; i < current_list->num-1; ++i)
        {
            tmp = tmp->next;
        }
        tmp->next = newnode;
        newnode->before = tmp;
        current_list->num++;
    }
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method)
{
    const list_t *src_list = this;
    list_t *dst_list = listDst;
    if (dst_list->num != 0)
    {
        node_t *tmp = dst_list->first;
        node_t *tmp_2;
        size_t num = dst_list->num;
        for (int i = 0; i < num; ++i)
        {

            tmp_2 = tmp->next;

            free(tmp->name);
            if (dst_list->value_type == DLIST_STR) {
                free(tmp->value.strValue);
            }
            free(tmp);
            tmp = tmp_2;
        }
        dst_list->num = 0;
    }
    dlistValueType type = src_list->value_type;
    if (type == DLIST_STR || type == DLIST_INT || type == DLIST_DOUBLE)
    {
        if (method == DLIST_SORT_INC)
        {
            sort_list_inc(src_list, dst_list);
        }
        else if (method == DLIST_SORT_DEC)
        {
            sort_list_dec(src_list, dst_list);
        }
        else if (method == DLIST_SORT_RAND)
        {
            sort_list_rand(src_list, dst_list);
        }
        else
        {
            perror("wrong method\n");
        }
    }
    else
    {
        perror("wrong type\n");
    }
}

void dlistPrint(dlist_const this)
{
    const list_t *current_list = this;
    node_t *tmp = current_list->first;
    for (int i = 0; i < current_list->num; ++i)
    {
        printf("%s=", tmp->name);
        if (current_list->value_type == DLIST_INT)
        {
            printf("%d\n", tmp->value.intValue);
        }
        else if (current_list->value_type == DLIST_DOUBLE)
        {
            printf("%lf\n", tmp->value.doubleValue);
        }
        else if (current_list->value_type == DLIST_STR)
        {
            printf("%s\n", tmp->value.strValue);
        }
        tmp = tmp->next;
    }
}

void dlistFree(dlist this)
{
    list_t *dst_list = this;
    node_t *tmp = dst_list->first;
    node_t *tmp_2;
    size_t num = dst_list->num;
    for (int i = 0; i < num; ++i)
    {

        tmp_2 = tmp->next;

        free(tmp->name);
        if (dst_list->value_type == DLIST_STR) {
            free(tmp->value.strValue);
        }
        free(tmp);
        tmp = tmp_2;
    }
    free(dst_list);
}
