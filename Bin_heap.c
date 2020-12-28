#include <stdio.h>
#include <stdlib.h>

struct Node {
    // Key / Value / data and Degree of CurrentNode
    int data, deg;
    // Child, Parent & Sibling of CurrentNode
    struct Node *child, *par, *sib;
};

// Function(parent, child)
void makeLink(struct Node *p, struct Node *c) {
    c -> par = p;
    c -> sib = p -> child;
    p -> child = c;
    p -> deg = p -> deg + 1;
}

struct Node* combineDegwise(struct Node *H1, struct Node *H2) {
    if (!H1) {
        return H2;
    }
    if (!H2) {
        return H1;
    }
    struct Node *currHeap = NULL;
    struct Node *first = H1, *second = H2;
    if (first -> deg < second -> deg) {
        currHeap = H1;
        first = first -> sib;
    }
    else {
        currHeap = H2;
        second = second -> sib;
    }
    struct Node *prv = currHeap;
    while (first && second) {
        if (first -> deg < second -> deg) {
            prv -> sib = first;
            prv = first;
            first = first -> sib;
        }
        else {
            prv -> sib = second;
            prv = second;
            second = second -> sib;
        }
    }
    if (first) {
        prv -> sib = first;
    }
    else  {
        prv -> sib = second;
    }
    return currHeap;
}

struct Node* Union_heap(struct Node *H1, struct Node *H2) {
    struct Node *currHeap = combineDegwise(H1, H2);
    if (!currHeap) {
        return currHeap;
    }
    struct Node *prev = NULL, *curr = currHeap, *next = curr -> sib;
    while (next) {
        struct Node *next_next = next -> sib;
        if (curr -> deg != next -> deg || (next_next && next_next -> deg == next -> deg)) {
            prev = curr;
            curr = next;
        }
        else {
            if (curr -> data < next -> data) {
                curr -> sib = next -> sib;
                makeLink(curr, next);
            }
            else {
                if (prev) 
                    prev -> sib = next;
                else
                    currHeap = next;
                makeLink(next, curr);
                curr = next;
            }
        }
        next = curr -> sib;
    }
    return currHeap;
}

struct Node *insert(struct Node *H, int x) {
    struct Node *h = (struct Node *)malloc(sizeof(struct Node));
    h -> sib = NULL;
    h -> par = NULL;
    h -> child = NULL;
    h -> deg = 0, h -> data = x;
    h = Union_heap(h, H);
    return h;
}
void displayTree(struct Node *T) {
    if (!T) return;
    printf("%d ", T -> data);
    displayTree(T -> child);
    displayTree(T -> sib);
}
void display(struct Node *H) {
    struct Node *curr = H;
    while (curr) {
        printf("%d ", curr -> data);
        displayTree(curr -> child);
        curr = curr -> sib;
        printf("\n");
    }
}

struct Node *popMin(struct Node *H) {
    struct Node *minHeap = NULL, *curr = H;
    if (!H) {
        printf("*** Heap is Empty!! ***");
        return H;
    }

    // Take the Address of the root of the Tree with minimumKey!.

    while (curr) {
        if (minHeap == NULL || minHeap -> data > curr -> data) {
            minHeap = curr;
        }
        curr = curr -> sib;
    }

    curr = H;
    struct Node *prv = NULL;
    struct Node *newHeap = curr;

    // Collect all the trees excepts the minKey_Rooted Tree.

    while (curr) {
        if (curr == minHeap) {
            if (prv) prv -> sib = curr -> sib;
            else newHeap = curr -> sib;
        }
        prv = curr;
        curr = curr -> sib;
    }

    // Now Union minKey_Rooted Tree's Child with already collected trees.
    // It is my NewHeap with Removed minimumKey.

    struct Node *minChilds = minHeap -> child;
    while (minChilds != NULL) {
        struct Node *my_sib = minChilds -> sib;
        minChilds -> sib = NULL;
        newHeap = Union_heap(newHeap, minChilds);
        minChilds = my_sib;
    }
    return newHeap;
}

int main() {
    struct Node *H = NULL;
    int n;
    printf("Enter the # of Nodes : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        H = insert(H, x);
    }
    display(H);
    printf("\n");
    printf("MinKey is Extracted ...\n");
    H = popMin(H);
    display(H);
}
