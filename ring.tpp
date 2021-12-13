#pragma once
#include <iostream>
#include "ring.h"

template <typename Key, typename Info>
void Ring<Key, Info>::copy_all(const Ring& src) {
    // Copying should only be possible for an empty ring
    if (!empty()) return;
    if (src.empty()) return;

    for (auto it = src.cbegin(); it != src.cend(); it++) {
        push_end(it->first, it->second);
    }
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring() {
    head = new Node();
    head->prev = head;
    head->next = head;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring& src) {
    head = new Node();
    head->prev = head;
    head->next = head;
    copy_all(src);
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring& src) {
    if (this == &src) return *this;
    remove_all();
    copy_all(src);
    return *this;
}

/*
template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring&& src) {
    // TODO
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring&& src) {
    // TODO
}
*/

template <typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    remove_all();
    delete head;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::push_front(const Key& key, const Info& info) {
    Node *n = new Node(key, info, head, head->next);
    head->next->prev = n;
    head->next = n;
    auto it = iterator(n, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::push_end(const Key& key, const Info& info) {
    auto last_elem = --iterator(end().current, this);
    auto it = insert(last_elem, key, info);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::pop_front() {
    if (empty()) return begin();
    Node *current = head->next;
    head->next = current->next;
    current->next->prev = head;
    auto it = iterator(current->next, this);
    delete current;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(iterator position, const Key& key, const Info& info) {
    if (position.owner != this) throw std::invalid_argument("Trying to insert item with invalid owner");
    Node *c = position.current;
    Node *n = new Node(key, info, c, c->next);
    c->next->prev = n;
    c->next = n;
    auto it = iterator(n, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::erase(iterator position) {
    if (position.owner != this) throw std::invalid_argument("Trying to delete item with invalid owner");
    auto to_return = position;
    to_return++;
    position.current->prev->next = position.current->next;
    position.current->next->prev = position.current->prev;
    delete position.current;
    return to_return;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin() {
    auto it = iterator(head->next, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end() {
    auto it = iterator(head, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cbegin() const{
    auto it = const_iterator(head->next, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cend() const {
    auto it = const_iterator(head, this);
    return it;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::empty() const {
    // std::cout << "is empty?" << std::endl;
    bool result = head->next == head;
    // std::cout << "checked if empty: " << result << std::endl;
    return result;
}

template <typename Key, typename Info>
void Ring<Key, Info>::remove_all() {
    Node *n = head->next;
    while(n != head) {
        Node *to_del = n;
        n = n->next;
        delete to_del;
    }
    head->next = head;
    head->prev = head;
}

template <typename Key, typename Info>
void Ring<Key, Info>::print() {
    std::cout << *this;
}

template <typename Key, typename Info>
void Ring<Key, Info>::print_reverse() {
    if (empty() == true) {
        std::cout << "Empty ring" << std::endl << std::endl;
    }
    for (auto it = --end(); it != end(); it--) {
        std::cout << " - " << it->first << " : " << it->second << std::endl;
    }
    std::cout << std::endl;
}

template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& out, const Ring<Key, Info>& ring) {
    if (ring.empty() == true) {
        out << "Empty ring" << std::endl << std::endl;
        return out;
    }

    for (auto it = ring.cbegin(); it != ring.cend(); it++) {
        out << " - " << it->first << " : " << it->second << std::endl;
    }
    out << std::endl;
    return out;
}

template<typename Key, typename Info>
Ring<Key, Info> shuffle(const Ring<Key, Info>& first, unsigned int fcnt, 
    const Ring<Key, Info>& second, unsigned int scnt, unsigned int reps) {
    if (first.empty()) return second;
    if (second.empty()) return first;
    
    Ring<Key, Info> result;

    auto it_first = first.cbegin();
    auto it_second = second.cbegin();

    for (unsigned int rep = 1; rep <= reps; rep++) {
        for (unsigned int fcount = 1; fcount <= fcnt; fcount++) {
            result.push_end(it_first->first, it_first->second);
            it_first++;
            if (it_first == first.cend()) it_first = first.cbegin();
        }
        for (unsigned int scount = 1; scount <= scnt; scount++) {
            result.push_end(it_second->first, it_second->second);
            it_second++;
            if (it_second == second.cend()) it_second = second.cbegin();
        }
    }

    return result;
}
