#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "AssociativeArray.h"

#include <iostream>
#include <queue>
#include <stdexcept>

template <typename Key, typename Value>
class BST : public AssociativeArray<Key, Value> {
public:
    BST() {};
    BST(const BST& copy);
    BST& operator=(const BST& copy);

    BST(BST&& other) noexcept;
    BST& operator=(BST&& other) noexcept;

    void add(const Key& key, const Value& value) override;
    Value& find(const Key& key) override;
    const Value& find(const Key& key) const override;
    void remove(const Key& key) override;

    ~BST();

    /*
    Для дебага
    void print(std::ostream& stream = std::cout) const;
    template <typename KeyType, typename ValueType>
    friend std::ostream& operator<<(std::ostream& stream, const BST<KeyType, ValueType>& tree);
    */
private:
    class Node {
        public:
            Node(const Key& key, const Value& value);
            ~Node();
            Node* _left = nullptr;
            Node* _right = nullptr;
            Key _key;
            Value _value;
    };

    Node* _head = nullptr;
};

template <typename Key, typename Value>
BST<Key, Value>::BST(const BST& copy) {
    if (copy._head) {
        std::queue<Node*> q;
        q.push(copy._head);
        while (!q.empty()) {
            Node* toAdd = q.front();
            q.pop();
            add(toAdd->_key, toAdd->_value);
            if (toAdd->_left) {
                q.push(toAdd->_left);
            }
            if (toAdd->_right) {
                q.push(toAdd->_right);
            }
        }
    }
}

template <typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(const BST& copy) {
    delete _head;
    if (copy._head) {
        std::queue<Node*> q;
        q.push(copy._head);
        while (!q.empty()) {
            Node* toAdd = q.front();
            q.pop();
            add(toAdd->_key, toAdd->_value);
            if (toAdd->_left) {
                q.push(toAdd->_left);
            }
            if (toAdd->_right) {
                q.push(toAdd->_right);
            }
        }
    }
}

template <typename Key, typename Value>
BST<Key, Value>::BST(BST&& other) noexcept {
    std::swap(_head, other._head);
}

template <typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(BST&& other) noexcept {
    delete _head;
    _head = nullptr;
    std::swap(_head, other._head);
}

template <typename Key, typename Value>
void BST<Key, Value>::add(const Key& key, const Value& value) {
    if (_head) {
        Node* toAddParent = _head;
        while (((toAddParent->_key >= key) && toAddParent->_left)
            || ((toAddParent->_key <  key) && toAddParent->_right)) {
            if (toAddParent->_key >= key) {
                toAddParent = toAddParent->_left;
            }
            else {
                toAddParent = toAddParent->_right;
            }
        }
        if (toAddParent->_key >= key) {
            toAddParent->_left = new Node(key, value);
        }
        else {
            toAddParent->_right = new Node(key, value);
        }
    }
    else {
        _head = new Node(key, value);
    }
}

template <typename Key, typename Value>
Value& BST<Key, Value>::find(const Key& key) {
    Node* current = _head;
    if (current) {
        while (((current->_key > key) && current->_left)
            || ((current->_key <  key) && current->_right)) {
            if (current->_key > key) {
                current = current->_left;
            }
            else {
                current = current->_right;
            }
        }
        if (current->_key != key) {
            throw std::invalid_argument("Called find() - There is no such key in BST");
        }
    }
    else {
        throw std::invalid_argument("Called find() - There is no such key in BST");
    }
    return current->_value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::find(const Key& key) const {
    Node* current = _head;
    if (current) {
        while (((current->_key > key) && current->_left)
            || ((current->_key <  key) && current->_right)) {
            if (current->_key > key) {
                current = current->_left;
            }
            else {
                current = current->_right;
            }
        }
        if (current->_key != key) {
            throw std::invalid_argument("Called find() - There is no such key in BST");
        }
    }
    else {
        throw std::invalid_argument("Called find() - There is no such key in BST");
    }
    return current->_value;
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(const Key& key) {
    if (_head) {
        Node* toRemove = _head;
        Node* toRemoveParent = nullptr;
        while (((toRemove->_key > key) && toRemove->_left)
            || ((toRemove->_key <  key) && toRemove->_right)) {
            toRemoveParent = toRemove;
            if (toRemove->_key >= key) {
                toRemove = toRemove->_left;
            }
            else {
                toRemove = toRemove->_right;
            }
        }
        if (!toRemoveParent && toRemove->_key == key) {
            if (!(toRemove->_left || toRemove->_right)) {
                _head = nullptr;
            }
            else if (toRemove->_left && toRemove->_right) {
                Node* mostRight = toRemove->_left;
                _head = toRemove->_left;
                while (mostRight->_right) {
                    mostRight = mostRight->_right;
                }
                mostRight->_right = toRemove->_right;
                toRemove->_left = nullptr;
                toRemove->_right = nullptr;
            }
            else {
                if (toRemove->_left) {
                    _head = toRemove->_left;
                    toRemove->_left = nullptr;
                }
                else {
                    _head = toRemove->_right;
                    toRemove->_right = nullptr;
                }
            }
            delete toRemove;
        }
        else if (toRemove->_key == key) {
            if (!(toRemove->_left || toRemove->_right)) {
                if (toRemoveParent->_key >= key) {
                    toRemoveParent->_left = nullptr;
                }
                else {
                    toRemoveParent->_right = nullptr;
                }
            }
            else if (toRemove->_left && toRemove->_right) {
                if (toRemoveParent->_key >= key) {
                    toRemoveParent->_left = toRemove->_left;
                }
                else {
                    toRemoveParent->_right = toRemove->_left;
                }
                Node* mostRight = toRemove->_left;
                while (mostRight->_right) {
                    mostRight = mostRight->_right;
                }
                mostRight->_right = toRemove->_right;
                toRemove->_left = nullptr;
                toRemove->_right = nullptr;
            }
            else {
                if (toRemove->_left) {
                    if (toRemoveParent->_key >= key) {
                        toRemoveParent->_left = toRemove->_left;
                    }
                    else {
                        toRemoveParent->_right = toRemove->_left;
                    }
                    toRemove->_left = nullptr;
                }
                else {
                    if (toRemoveParent->_key >= key) {
                        toRemoveParent->_left = toRemove->_right;
                    }
                    else {
                        toRemoveParent->_right = toRemove->_right;
                    }
                    toRemove->_right = nullptr;
                }
            }
            delete toRemove;
        }
        else {
            throw std::invalid_argument("Called remove() - There is no such key in BST");
        }
    }
    else {
        throw std::invalid_argument("Called remove() - There is no such key in BST");
    }
}

template <typename Key, typename Value>
BST<Key, Value>::~BST() {
    delete _head;
}

template <typename Key, typename Value>
BST<Key, Value>::Node::Node(const Key& key, const Value& value) {
    _key = key;
    _value = value;
}

template <typename Key, typename Value>
BST<Key, Value>::Node::~Node() {
    delete _right;
    delete _left;
}

/*
Для дебага: Выводит дерево до третьего потомка. Если потомков не хватает - ставит nulptr.
template <typename Key, typename Value>
void BST<Key, Value>::print(std::ostream& stream) const {
    Node* firstChild = nullptr;
    Node* secondChild = nullptr;
    stream << "                  ";
    if (_head) {
        stream << "(" << _head->_key << "; " << _head->_value << ")\n";
        firstChild = _head->_left;
        secondChild = _head->_right;
    }
    else {
        stream << "nulptr\n";
    }
    stream << "      ";
    if (firstChild) {
        stream << "(" << firstChild->_key << "; " << firstChild->_value << ")";
    }
    else {
        stream << "nulptr";
    }
    stream << "                  ";
    if (secondChild) {
        stream << "(" << secondChild->_key << "; " << secondChild->_value << ")\n";
    }
    else {
        stream << "nulptr\n";
    }
    if (firstChild) {
        if (firstChild->_left) {
            stream << "(" << firstChild->_left->_key << "; " << firstChild->_left->_value << ")";
        }
        else {
            stream << "nulptr";
        }
        stream << "      ";
        if (firstChild->_right) {
            stream << "(" << firstChild->_right->_key << "; " << firstChild->_right->_value << ")";
        }
        else {
            stream << "nulptr";
        }
    }
    else {
        stream << "nulptr      nulptr";
    }
    stream << "      ";
    if (secondChild) {
        if (secondChild->_left) {
            stream << "(" << secondChild->_left->_key << "; " << secondChild->_left->_value << ")";
        }
        else {
            stream << "nulptr";
        }
        stream << "      ";
        if (secondChild->_right) {
            stream << "(" << secondChild->_right->_key << "; " << secondChild->_right->_value << ")";
        }
        else {
            stream << "nulptr";
        }
    }
    else {
        stream << "nulptr      nulptr";
    }
    stream << "\n";
}

template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream& stream, const BST<KeyType, ValueType>& tree) {
    tree.print(stream);
    return stream;
}
*/
#endif // BINARYSEARCHTREE_H_INCLUDED
