#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *newNode(int x) {
    Node *node = new Node;
    node -> next = NULL;
    node -> data = x;
    return node;
}

void build(Node **head, Node **tail, int x) {
    Node *node = newNode(x);
    if (*head == NULL) {
        *head = node;
        *tail = node;
    }
    else {
        (*tail) -> next = node;
        (*tail) = node;
    }
}

Node *solve(Node **newHead, Node *head, int k) {
    Node *prv = NULL, *curr = head;
    int done = 0;
    Node *first = head;
    if (!head) {
        return head;
    }
    while (curr && done < k) {
        Node *nxt = curr -> next;
        curr -> next = prv;
        prv = curr;
        curr = nxt;
        done++;
    }
    if (*newHead == NULL) {
        *newHead = prv;
    }
    first -> next = solve(newHead, curr, k);
    return prv;
}

void display(Node *head) {
    Node *curr = head;
    while (curr) {
        cout << curr -> data << ' ';
        curr = curr -> next;
    }
    cout << '\n';
}

int main() {
    int n, k;
    cin >> n >> k;
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        build(&head, &tail, x);
    }
    display(head);
    Node *newHead = NULL;
    solve(&newHead, head, k);
    display(newHead);
}
