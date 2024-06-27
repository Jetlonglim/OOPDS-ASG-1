#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "robot.h"

class Robot;

// Define the Node struct
struct Node {
    Robot* robot; // The Robot object stored in the node
    Node* next;   // Pointer to the next node

    // Constructor to initialize with a Robot pointer
    Node(Robot* r) : robot(r), next(nullptr) {}

    // Getter for robot
    Robot* getData() {
        return robot;
    }

    // Getter for next node
    Node* getNext() {
        return next;
    }

    // Setter for next node
    void setNext(Node* nextNode) {
        next = nextNode;
    }
};

// A linked list data structure to store Robot objects.
 
class LinkedList {
private:
    Node* head; // Pointer to the first node in the linked list
    int size;   // To keep track of the size of the linked list

public:
    // Constructs an empty linked list.
    LinkedList() : head(nullptr), size(0) {}

    // Adds a new Robot object to the end of the linked list.
    void insert(Robot* robot) {
        Node* newNode = new Node(robot);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Gets the Robot object at the specified index in the linked list.
    Robot* getRobot(int index) const {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (count == index) {
                return current->robot;
            }
            current = current->next;
            ++count;
        }
        return nullptr; // Out of bounds
    }

    // Gets the number of Robot objects in the linked list.
    int getSize() const {
        return size;
    }

    // Gets the head of the linked list.
    Node* getHead() const {
        return head;
    }

    // Sets the head of the linked list (used in Battlefield).
    void setHead(Node* newHead) {
        head = newHead;
    }

    // Removes a specific Robot object from the linked list.
    void remove(Robot* robot) {
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->robot == robot) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current->robot; // Delete the Robot object
                delete current;        // Delete the Node
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Deallocates all memory used by the linked list and its nodes.
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete->robot;
            delete toDelete;
        }
    }
};

#endif

