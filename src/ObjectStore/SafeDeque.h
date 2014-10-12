#pragma once
#include <deque>

template <class T> class SafeDeque{
public:
    SafeDeque(){
        cursor = 0;
    }
    T* operator[](const int i);
    void push_back(T item);
    void deleteItem(int i);
    void deleteAll();
    T* getPointer(int i);
    void insert(int i, T &item);
    int size();
    void undo();
    void redo();
    void backup();
protected:
    std::deque <T> items;
    std::deque < std::deque<T> > undoList;
    int cursor;
    void backupTopItem();
};

template <class T> T* SafeDeque<T>::operator[] (const int i){
    return &items[i];
}

template <class T> void SafeDeque<T>::push_back(T item){
    items.push_back(item);
}

template <class T> void SafeDeque<T>::deleteItem(int i){
    items.erase(items.begin() + i);
}

template <class T> void SafeDeque<T>::deleteAll(){
    items.clear();
}

template <class T> T* SafeDeque<T>::getPointer(int i){
    return &items[i];
}

template <class T> void SafeDeque<T>::insert(int i, T &item){
    items.insert(items.begin() + i, item);
}

template <class T> int SafeDeque<T>::size(){
    return items.size();
}

template <class T> void SafeDeque<T>::undo(){
    if(cursor > 0){
        backupTopItem();
        cursor--;
        items = undoList[cursor];
    }
}

template <class T> void SafeDeque<T>::redo(){
    if(cursor < undoList.size() - 1){
        cursor++;
        items = undoList[cursor];
    }
}

template <class T> void SafeDeque<T>::backup(){
    undoList.erase(undoList.begin() + cursor, undoList.end());
    undoList.push_back(items);
    cursor = undoList.size();
}

template <class T> void SafeDeque<T>::backupTopItem(){
    if(cursor == undoList.size()){
        undoList.push_back(items);
    }
}