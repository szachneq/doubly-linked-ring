#pragma once
#include <iostream>

// template <typename Key, typename Info>
// class Ring {
//     public:
//     Ring();
// };

template <typename Key, typename Info>
class Ring {
    class Node {
        public:

        std::pair<Key, Info> data;
        Node *next = nullptr;
        Node *prev = nullptr;

        Node(Key k = Key(), Info i = Info(), Node *p = nullptr, Node *n = nullptr) {
            data = {k, i};
            prev = p;
            next = n;
        }
    };

    Node *head = nullptr; // Sentinel Node

    void copy_all(const Ring& src);

    public:

    // Contructor
    Ring();

    // Copy constructor
    Ring(const Ring& src);

    // Assignment operator
    Ring& operator=(const Ring& src);

    // Move contructor
    Ring(const Ring&& src);

    // Move assignment
    Ring& operator=(const Ring&& src);

    ~Ring();

    class iterator {
        friend class Ring;
        Ring<Key, Info> *owner = nullptr;
        Node *current = nullptr;

        iterator(Node *c, Ring<Key, Info> *o) {
            current = c;
            owner = o;
        }

        public:

        iterator& operator++() { // Prefix increment
            current = current->next;
            return *this;
        }

        iterator operator++(int) { // Postfix increment
            iterator to_return = *this;
            current = current->next;
            return to_return;
        }

        iterator& operator--() { // Prefix decrement
            current = current->prev;
            return *this;
        }

        iterator operator--(int) { // Postfix decrement
            iterator to_return = *this;
            current = current->prev;
            return to_return;
        }

        bool operator==(const iterator &rhs) const{
            return (owner == rhs.owner) && (current == rhs.current);
        }

        bool operator!=(const iterator &rhs) const{
            return !operator==(rhs);
        }

        std::pair<Key, Info>& operator*() {
            if (current == owner->head) throw std::runtime_error(std::string("Inaccessible memory"));
            return current->data;
        }

        std::pair<Key, Info>* operator->() {
            if (current == owner->head) throw std::runtime_error(std::string("Inaccessible memory"));
            return &current->data; 
        }
    };

    class const_iterator {
        friend class Ring;
        const Ring<Key, Info> *owner = nullptr;
        Node *current = nullptr;

        const_iterator(Node *c, const Ring<Key, Info> *o) {
            current = c;
            owner = o;
        }

        public:

        const_iterator& operator++() { // Prefix increment
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) { // Postfix increment
            const_iterator to_return = *this;
            current = current->next;
            return to_return;
        }

        const_iterator& operator--() { // Prefix decrement
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int) { // Postfix decrement
            iterator to_return = *this;
            current = current->prev;
            return to_return;
        }

        bool operator==(const const_iterator &rhs) const {
            return (owner == rhs.owner) && (current == rhs.current);
        }

        bool operator!=(const const_iterator &rhs) const {
            return !operator==(rhs);
        }

        const std::pair<Key, Info>& operator*() const {
            if (current == owner->head) throw "Inaccessible memory";
            return current->data;
        }

        const std::pair<Key, Info>* operator->() const {
            if (current == owner->head) throw "Inaccessible memory";
            return &current->data;
        }
    };

    iterator push_front(const Key& key, const Info& info);

    iterator pop_front();

    iterator insert(iterator position, const Key& key, const Info& info);

    iterator erase(iterator position);

    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    bool empty() const;

    void remove_all();

    void print();

    void print_reverse();

};

template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& out, const Ring<Key, Info>& ring);

template<typename Key, typename Info>
Ring<Key, Info> shuffle(const Ring<Key, Info>& first, unsigned int fcnt, 
    const Ring<Key, Info>& second, unsigned int scnt, unsigned int reps);

#include "ring.tpp"
