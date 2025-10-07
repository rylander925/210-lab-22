/*
COMSC-210 | Lab 22 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int STREAM_IGNORE_CHARS = 128;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    /**
     * Deletes node at specified position, starting with head = position 0
     * @param position Position of node to delete. Must be >=0.
     */
    void delete_pos(int position) {
        if (position < 0) { 
            cout << "ERROR in delete_pos(): Position must be >= 0" << endl;
            return;
        }

        Node* current = head;
        Node* nextNode = nullptr;
        Node* prevNode = nullptr;
        // will execute position times or until current is a nullptr
        for(int i = 0; i < position && current; i++) { 
            current = current->next;
        }

        if (!current) {
            cout << "ERROR in delete_pos(): Given position exceeds list length" << endl;
            return;
        }

        nextNode = current->next;
        prevNode = current->prev;

        if(nextNode) {
            nextNode->prev = prevNode;
        } else {
            tail = prevNode;
        }

        if(prevNode) {
            prevNode->next = nextNode;
        } else {
            head = nextNode;
        }

        delete current;
    }

    /**
     * Deletes head node
     */
    void pop_front() {
        if (!head) {
            return; //If empty, return
        }

        Node* current = head;
        if (current->next) {
            current->next->prev = nullptr;
            head = head->next;
        } else { // if only node
            head = nullptr;
            tail = nullptr;
        }

        delete current;
    }

    /**
     * Deletes tail node
     */
    void pop_back() {
        if (!tail) {
            return; //If empty, return
        }

        Node* current = tail;
        if (current->prev) {
            current->prev->next = nullptr;
            tail = tail->prev;
        } else { //if only node
            head = nullptr;
            tail = nullptr;
        }

        delete current;
    }

    /**
     * Deletes first node with the specified value
     * @param value Value of node to delete
     */
    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
    
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0)); // seed random number for list values & delete position

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    cout << endl;

    // test delete_pos()
    int random_position = 1 + (rand() % size);
    cout << "After deleting element at position " << random_position << " (head is position 0):" << endl;
    list.delete_pos(random_position);
    list.print();
    cout << endl;

    // test pop_front()
    cout << "After deleting first two elements:" << endl;
    list.pop_front();
    list.pop_front();
    list.print();
    cout << endl;

    //test pop_back()
    cout << "After deleting last two elements:" << endl;
    list.pop_back();
    list.pop_back();
    list.print();
    cout << endl;

    //test delete_value()
    int delete_value = 0;
    do { // validate input is an integer. does not check for valid number
        if (cin.fail()) {
            cout << "Input must be an integer. Trying again." << endl;
            cin.clear();
            cin.ignore(STREAM_IGNORE_CHARS, '\n');
        }
        cout << "Enter a value to attempt to delete: ";
    } while(!(cin >> delete_value));
    cout << "After attempting to delete element with value " << delete_value << ":" << endl;
    list.delete_val(delete_value);
    list.print();
    cout << endl;

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
