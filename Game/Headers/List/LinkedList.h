#ifndef INFO2_2020_LINKEDLIST_H
#define INFO2_2020_LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList {
private:
    Node<T> *head;              // Puntero al primer nodo de la lista.
    unsigned int list_size;     // Tamaño actual de la lista

    Node<T> *loopActual;        // Puntero para iterar la lista

    Node<T> *getNode(int pos);

public:
    LinkedList();

    LinkedList(const LinkedList<T> &org);

    ~LinkedList();

    void insert(int pos, T data);

    T get(int pos);

    void replace(int pos, T data);

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

    /* Métodos para utilizar con el For y poder recorrer la lista
     * de manera mas eficiente
     *
     *  for (lista.loopStart(); !lista.loopEnd(); lista.loopNext()) {
            lista.loopGet(); // Dato actual
        }
     */
    void loopStart() { loopActual = head; }

    void loopNext() { loopActual = loopActual->getNext(); }

    T loopGet() { return loopActual->getData(); }

    bool loopEnd() { return loopActual == nullptr; }
};

/**
 *  Método privado para obtener un nodo en una posición
 * @param pos Posición del nodo a obtener.
 * @return Puntero al nodo encontrado
 * @throw 404
 */
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


/**
 * Constructor de la Lista
 * @tparam T
 */
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    list_size = 0;
}

/**
 * Método para insertar en la lista
 * @param pos Posición en la lista a insertar
 * @param data Dato que se desea insertar
 */
template<typename T>
void LinkedList<T>::insert(int pos, T data) {
    Node<T> *aux;

    if (pos == 0) { // caso especial para pos = 0
        aux = new Node<T>;
        aux->setNext(head);
        aux->setData(data);
        head = aux;
        list_size++;
        return;
    }

    aux = getNode(pos - 1);

    auto newNode = new Node<T>;
    newNode->setNext(aux->getNext());
    aux->setNext(newNode);
    newNode->setData(data);
    list_size++;
}

/**
 * Método para obtener el valor en el nodo 'pos'
 * @param pos Posición de la cual obtener el nodo
 * @return El valor encontrado
 */
template<typename T>
T LinkedList<T>::get(int pos) {
    auto aux = getNode(pos);
    return aux->getData();
}

/**
 * Remplaza el valor en la posición pos por el dato pasado
 * @param pos Posición del dato a remplazar
 * @param data Nuevo dato a colocar.
 */
template<typename T>
void LinkedList<T>::replace(int pos, T data) {
    auto aux = getNode(pos);
    aux->setData(data);
}

/**
 *  Saber si la lista está vacía
  * @return True si está vacía, False si tiene datos guardados
 */
template<typename T>
bool LinkedList<T>::empty() {
    return head == nullptr;
}

/**
 * Elimina el nodo y dato en determinada posición
 * @param pos Lugar de la lista a eliminar
 */
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

/**
 * Encuentra un valor dentro de la lista.
 * @param dato Valor a ser encontrado
 * @return El valor encontrado
 */
template<typename T>
T LinkedList<T>::find(T dato) {
    auto aux = head;

    while (aux != nullptr && aux->getData() != dato) {
        aux = aux->getNext();
    }

    if (aux == nullptr)
        throw 404;

    return aux->getData();
}

/**
 * Destructor que se asegura de eliminar todos los nodos que se les hizo new
 * dentro de la lista.
 */
template<typename T>
LinkedList<T>::~LinkedList() {
    while (!empty()) {
        erase(0);
    }
}



#endif //INFO2_2020_LINKEDLIST_H
