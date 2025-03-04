#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

typedef struct list_head list_head;

/* Create an empty queue */
struct list_head *q_new()
{
    list_head *head = malloc(sizeof(list_head));
    if (list_empty(head))
        return NULL;

    INIT_LIST_HEAD(head);

    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    // if queue is empty.
    if (!head)
        return;
    // if queue only have an element.
    if (list_empty(head)) {
        free(head);
        return;
    }

    list_head *pos, *safe;
    list_for_each_safe (pos, safe, head) {
        element_t *cur = list_entry(pos, element_t, list);
        q_release_element(cur);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;

    node->value = malloc(strlen(s) + 1);
    if (!node->value) {
        q_release_element(node);
        return false;
    }

    strlcpy(node->value, s, strlen(s) + 1);

    node->list.prev = head;
    node->list.next = (head->next);

    (head->next)->prev = &node->list;
    head->next = &node->list;

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;

    node->value = malloc(strlen(s) + 1);
    if (!node->value) {
        q_release_element(node);
        return false;
    }

    strlcpy(node->value, s, strlen(s) + 1);

    node->list.next = head;
    node->list.prev = (head->prev);

    (head->prev)->next = &node->list;
    head->prev = &node->list;

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    list_head *node = head->next;
    element_t *str = list_entry(node, element_t, list);
    bufsize = strlen(str->value) + 1;
    strlcpy(sp, str->value, bufsize);
    list_del(node);
    return str;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    list_head *node = head->prev;
    element_t *str = list_entry(node, element_t, list);
    bufsize = strlen(str->value) + 1;
    strlcpy(sp, str->value, bufsize);
    list_del(node);

    return str;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    list_head *li;
    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    list_head *cur, *safe, *temp;
    // head(next) -> A(cur) -> B(temp = cur->next) -> head(prev)
    // head <- A <- B <- head
    list_for_each_safe (cur, safe, head) {
        temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
    }
    temp = head->next;
    head->next = head->prev;
    head->prev = temp;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
