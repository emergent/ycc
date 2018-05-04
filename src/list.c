#include <stdio.h>
#include <stdlib.h>
#include "ycc.h"

Cell* cell_new(void* data) {
    Cell *cell = (Cell*)malloc(sizeof(Cell));
    if (cell != NULL) {
        cell->data = data;
        cell->next = NULL;
    }
    return cell;
}

void cell_delete(Cell *cell) {
    free(cell->data);
    free(cell);
}

size_t list_count_elem(List* list) {
    int count = 0;
    Cell* p = list->top;
    for (; p != NULL; p = p->next) {
        count++;
    }
    return count;
}

List* list_append(List* list, void* data) {
    Cell *cell;
    if (!list) { return NULL;}

    cell = cell_new(data);
    if (!cell) {
        fprintf(stderr, "failed: create new element of list\n");
    }

    if (!list->top) {
        list->top = cell;
    } else {
        list->last->next = cell;
    }
    list->last = cell;

    return list;
}

List* list_create() {
    List *l = (List*)malloc(sizeof(List));
    if (l != 0) {
        l->top = NULL;
        l->last = NULL;
    }
    return l;
}

void list_destroy(List *l) {
    Cell *p, *q;
    if (!l) { return; }

    for (p = l->top, q = NULL ; p != NULL; ) {
        q = p;
        p = p->next;
        cell_delete(q);
    }
    free(l);
}

/*
void print_list(List *l) {
    Cell *p = l->top;
    while (p != NULL) {
        if (p->next != NULL) {
            printf(", ");
        }
        p = p->next;
    }
    printf("\n");
}

void test_list() {
    List *l = create_string_list("hello, world");
    print_string_list(l);
}

int main(int argc, char* argv[]) {
    test_list();
    return 0;
}
*/
