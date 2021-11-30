#include <iostream>
using namespace std;
class Node {
    public:
    int data;
    Node* next;
};

void print_list(Node* head) {
    cout<<"[";
    while(head) {
        cout<<head->data<<", ";
        head=head->next;
    }
    cout<<"]\n";
}

Node* partition(Node* head, int pivot_num) {
    Node* less=NULL; Node* less_head=NULL;
    Node* more=NULL; Node* more_head=NULL;
    Node* pivot=NULL; Node* pivot_head=NULL;

    Node* temp=head;
    while(temp) {
        if(temp->data < pivot_num) {
            if(less_head==NULL) {
                less_head = temp;
                less=temp;
            } else {
                less->next=temp;
                less=less->next;
            }
        } else if(temp->data > pivot_num) {
            if(more_head==NULL) {
                more_head = temp;
                more=temp;
            } else {
                more->next = temp;
                more=more->next;
            }
        } else {
            if(pivot_head==NULL) {
                pivot_head = temp;
                pivot=temp;
            } else {
                pivot->next = temp;
                pivot=pivot->next;
            }
        }
        temp=temp->next;
    }

    less->next=pivot_head;
    pivot->next=more_head;
    return less_head;
}

int main() {

    int n;
    cin>>n;

    int num;
    cin>>num;
    Node* head = new Node{num, NULL};
    Node* thead = head;

    for(int i=1; i<n; i++) {
        cin>>num;
        thead->next = new Node{num, NULL};
        thead=thead->next;
    }

    cin>>num;

    print_list(head);
    head = partition(head, num);
    print_list(head);

    return 0;
}