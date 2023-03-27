//
// Created by Mateusz on 13.03.2022.
//

#ifndef UNTITLED6_DICTIONARY_H
#define UNTITLED6_DICTIONARY_H

#include <initializer_list>
#include <utility>
#include <string>
#include "MyVector.h"
#include <stdexcept>

using std::initializer_list, std::pair, std::string;

template <typename K, typename V>
class Dictionary
{
public:
    //konstruktory
    Dictionary() = default;
    Dictionary(initializer_list<pair<K,V>> list);

    //zarzadzaniee zawartoscia
    bool remove_by_key(const K& key);
    bool remove_by_index(int pos);
    void add(const pair<K,V>& p);
    void clear(){pairs.clear();}
    MyVector<K> keys();
    MyVector<V> values();
    V operator[](K key);

    //iteratory
    auto begin(){return pairs.begin();}
    auto end(){return pairs.end();}
    auto last(){return pairs.last();}
    auto at(int position){return pairs.at(position);}

    //inne
    bool empty(){return pairs.empty();}
    int get_size(){return pairs.get_size();}
    void print();


private:
    int find_key(const K& key);
    MyVector<pair<K,V>> pairs;
};

template<typename K, typename V>
Dictionary<K, V>::Dictionary(initializer_list<pair<K, V>> list) {
    for(const auto& p: list)
        add(p);
}

template<typename K, typename V>
bool Dictionary<K, V>::remove_by_key(const K &key) {
    for(int i = 0; i != get_size(); i++){
        if(pairs[i]->first==key) {
            pairs.remove(i);
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool Dictionary<K, V>::remove_by_index(int pos) {
    if(pos<0||pos>pairs.get_size()) return false;
    pairs.remove(pos);
}

template<typename K, typename V>
void Dictionary<K, V>::add(const pair<K, V> &p) {
    int index = find_key(p.first);
    if(index==-1)
        pairs.push_back(p);
    else {
        auto iter = begin();
        (iter + index)->second = p.second;
    }
}

template<typename K, typename V>
void Dictionary<K, V>::print() {
    for(const auto& p: pairs)
        std::cout<<'"'<<p.first<<'"'<<':'<<p.second<<" ";
    std::cout<<"\n";
}

template<typename K, typename V>
MyVector<K> Dictionary<K, V>::keys() {
    MyVector<K> result;
    for(const auto& p: pairs)
        result.push_back(p.first);
    return result;
}

template<typename K, typename V>
MyVector<V> Dictionary<K, V>::values() {
    MyVector<V> result;
    for(const auto& p: pairs)
        result.push_back(p.second);
    return result;
}

template<typename K, typename V>
int Dictionary<K, V>::find_key(const K &key) {
    if(!pairs.empty()) {
        auto i = begin();
        while (i != end()) {
            if (i->first == key)
                return i - begin();
            i.next();
        }
    }
    return -1;
}

template<typename K, typename V>
V Dictionary<K, V>::operator[](K key) {
    for(const auto& i: pairs)
        if(i.first==key)
            return i.second;
    throw std::invalid_argument("No such key");
}

#endif //UNTITLED6_DICTIONARY_H
