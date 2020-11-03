#ifndef INFO2_2020_LINKEDLIST_H
#define INFO2_2020_LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList {
private:
    Node<T> *head;

    Node<T> *getNode(int pos);

    unsigned int list_size;
public:
    LinkedList();

    void insert(int pos, T dato);

    T get(int pos);

    void replace(int pos, T dato);

    bool empty();

    void erase(int pos);


    T find(T dato);

    void push_front(T dato) {
        insert(0, dato);
    }

    void push_back(T dato) {
        insert(size(), dato);
    }


    unsigned int size() {
        return list_size;
    }
};

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    list_size = 0;
}

template<typename T>
void LinkedList<T>::insert(int pos, T dato) {
    Node<T> *aux;

    if (pos == 0) { // caso especial para pos = 0
        aux = new Node<T>;
        aux->setNext(head);
        aux->setData(dato);
        head = aux;
        list_size++;
        return;
    }

    aux = getNode(pos - 1);

    auto newNode = new Node<T>;
    newNode->setNext(aux->getNext());
    aux->setNext(newNode);
    newNode->setData(dato);
    list_size++;
}

template<typename T>
T LinkedList<T>::get(int pos) {
    auto aux = getNode(pos);
    return aux->getData();
}

template<typename T>
Node<T> *LinkedList<T>::getNode(int pos) {
    auto aux = head;
    int p = 0;

    while (p != pos && aux != nullptr) {
        aux = aux->getNext();
        p++;
    }

    if (aux == nullptr) {
        throw 404;
    }

    return aux;
}

template<typename T>
void LinkedList<T>::replace(int pos, T dato) {
    auto aux = getNode(pos);
    aux->setData(dato);
}

template<typename T>
bool LinkedList<T>::empty() {
    return head == nullptr;
}

template<typename T>
void LinkedList<T>::erase(int pos) {

    if (head == nullptr)
        throw 404;

    if (pos == 0) {
        auto toDelete = head;
        head = head->getNext();
        delete toDelete;
        list_size--;
        return;
    }

    auto aux = getNode(pos - 1);
    auto toDelete = aux->getNext();

    if (toDelete == nullptr) {
        throw 404;
    }

    aux->setNext(toDelete->getNext());
    delete toDelete;
    list_size--;
}

template <typename T>
T LinkedList<T>::find(T dato) {
    auto aux = head;

    while (aux != nullptr && aux->getData() != dato) {
        aux = aux->getNext();
    }

    if (aux == nullptr)
        throw 404;

    return aux->getData();
}


#endif //INFO2_2020_LINKEDLIST_H
