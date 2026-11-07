#ifndef LAB2_SINGULARLINKEDLIST_HPP
#define LAB2_SINGULARLINKEDLIST_HPP
#include <iostream>
//Generalized Linked List
//Based on GeeksforGeeks circular list, changed to non-circular
//https://www.geeksforgeeks.org/cpp/circular-linked-list-in-cpp/

// Template class for a Node in the singular linked list
template<typename T>
class Node {
    //Each node in the list
public:
    T data;
    Node<T> *next;

    Node(const T &data) : data(data), next(nullptr) {
    }
};

// Template class for the singular linked list
template<typename T>
class singularLinkedList {
    //Each list
private:
    int count;
    Node<T> *head;

public:
    //Default constructor
    singularLinkedList(Node<T> *head = nullptr) : head(nullptr), count(0) {
    }

    //Destructor
    ~singularLinkedList() { clear(); }

    //Delete any shallow copies made
    singularLinkedList(const singularLinkedList &) = delete;

    singularLinkedList &operator=(const singularLinkedList &) = delete;

    //Returns the head
    Node<T> *getHead() const { return head; }

    int getCount() const { return count; }

    //Checks if the list is empty
    bool isEmpty() const { return head == nullptr; }

    //Inserts <T> data at head
    void insertAtHead(const T &data) {
        count++;
        Node<T> *newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
    }

    //Inserts <T> data at tail
    void insertAtTail(const T &value) {
        count++;
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node<T> *temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }

    //Checks list for a value in the list
    bool isValueInList(T value) {
        Node<T> *temp = head;
        while (temp != nullptr) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    //Return the the Node in that position of the list (first is 0)
    Node<T> *nodeAtPos(int pos) {
        Node<T> *temp = head;
        for (int i = 0; i < pos && temp != nullptr; i++) temp = temp->next;
        return temp;
    }

    //Prints the list
    void display() const {
        for (Node<T> *temp = head; temp != nullptr; temp = temp->next)
            std::cout << temp->data << "\n";
    }

    //Delete the first item in the list
    void deleteFromHead() {
        count--;
        if (head == nullptr) return;
        Node<T> *old = head;
        head = head->next;
        delete old;
    }

    //Clears the list (used in the destructor)
    void clear() { while (head != nullptr) deleteFromHead(); }
};

#endif
