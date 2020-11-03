#ifndef INFO2_2020_NODE_H
#define INFO2_2020_NODE_H

//   TEMPLATES

template <typename T>
class Node {
private:
    T data;
    Node *next;
public:
    T getData() {
        return data;
    }

    void setData(T d) {
        data = d;
    }

    Node *getNext() {
        return next;
    }

    void setNext(Node *n) {
        next = n;
    }
};


#endif //INFO2_2020_NODE_H
