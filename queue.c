#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

void list_element_free(list_ele_t *ele)
{
    free(ele->value);
    free(ele);
}

list_ele_t *list_element_new(char *s)
{
    size_t len = strlen(s) + 1;  // include null terminator

    list_ele_t *new = malloc(sizeof(list_ele_t));
    if (new == NULL) {
        return NULL;
    }
    new->value = malloc(sizeof(char) * len);
    if (new->value == NULL) {
        free(new);
        return NULL;
    }
    new->next = NULL;
    strncpy(new->value, s, len);

    return new;
}


/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    while (q->head) {
        list_ele_t *next;
        next = q->head->next;
        list_element_free(q->head);
        q->head = next;
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (q == NULL) {
        return false;
    }

    newh = list_element_new(s);
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0) {
        q->tail = q->head;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *new;

    if (q == NULL) {
        return false;
    }

    new = list_element_new(s);
    if (q->size == 0) {
        q->head = q->tail = new;
    } else {
        q->tail->next = new;
        q->tail = new;
    }
    q->size += 1;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    list_ele_t *removed = q->head;

    snprintf(sp, bufsize, "%s", removed->value);

    if (q->size == 1) {
        q->tail = q->head = NULL;
    } else {
        q->head = q->head->next;
    }
    list_element_free(removed);
    q->size -= 1;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    } else {
        return q->size;
    }
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *cursor = NULL;
    q->tail = q->head;
    while (q->head) {
        list_ele_t *tmp = q->head->next;
        q->head->next = cursor;
        cursor = q->head;
        q->head = tmp;
    }
    q->head = cursor;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
