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
    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
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
    if (!head || list_empty(head))
        return false;

    list_head *fast, *slow;
    slow = fast = head->next;
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list_del(slow);
    element_t *str = list_entry(slow, element_t, list);
    q_release_element(str);

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
    if (!head || list_empty(head) || list_is_singular(head))
        return;

    // head(each->prev) -> each -> safe ->... -> head
    // head             -> safe -> each ->... -> head
    list_head *each, *safe;
    list_for_each_safe (each, safe, head) {
        if (safe != head) {
            list_move(safe, each->prev);
            safe = each->next;
        }
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    int turn = q_size(head) / k;
    list_head *front = head->next->next;
    list_head *last = head->next;

    for (size_t i = 0; i < turn; i++) {
        list_head *ll = last->prev;
        // Head -> A(last) -> B(front) -> C -> D -> E -> F -> Head
        // Head <- B(front) <- A(last) <- Head
        for (size_t j = 0; j < k; j++) {
            last->next = last->prev;
            last->prev = front;
            front = front->next;
            last = last->prev;
        }
        list_head *ff = last;
        last = ll->next;
        front = ff->prev;
        last->next = ff;
        ff->prev = last;
        front->prev = ll;
        ll->next = front;
        last = ff;
        front = ff->next;
    }
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
// cppcheck-suppress constParameterPointer
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    if (!head || list_empty(head))
        return 0;

    element_t *each, *safe;
    list_head *pending = q_new();
    int count = 0;

    list_for_each_entry_safe (each, safe, head, list) {
        count++;
        if (&safe->list != head && strcmp(each->value, safe->value) > 0) {
            list_move(&safe->list, pending);
            safe = each;
            count--;
        }
    }
    q_free(pending);
    return count;
}

/* Remove every node which has a node with a strictly greater value anywhere
 * to the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    if (!head || list_empty(head))
        return 0;

    int count = q_size(head);
    list_head *prev = head->prev;
    list_head *pending;
    while (prev->prev != head) {
        if (strcmp(list_entry(prev, element_t, list)->value,
                   list_entry(prev->prev, element_t, list)->value) > 0) {
            pending = prev->prev;
            list_del(pending);
            element_t *str = list_entry(pending, element_t, list);
            q_release_element(str);
            count--;
        } else {
            prev = prev->prev;
        }
    }
    return count;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
