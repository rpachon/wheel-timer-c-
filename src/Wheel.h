//
// Created by stan on 09/11/16.
//

#ifndef WHEEL_TIMER_WHEEL_H
#define WHEEL_TIMER_WHEEL_H

#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class Wheel {
private:
    vector<vector<T>> wheel;
    unsigned int index;
    bool cascade = false;

public:
    Wheel(unsigned int size);
    void add(T item, unsigned int bucket);

    vector<T> get(unsigned int index);

    vector<T> nextBucket();

    bool hasCascade();

    const unsigned int lenght;

    unsigned int remainingTick();

};

template<class T>
Wheel<T>::Wheel(unsigned int size) : lenght(size), wheel(size, vector<T>()) {
    if (size == 0) throw runtime_error("Can not create a wheel with size 0");
    index = 0;
}

template<class T>
void Wheel<T>::add(T item, unsigned int bucket) {
    wheel[(bucket+index)%lenght].push_back(item);
}

template <class T>
vector<T> Wheel<T>::get(unsigned int index) {
    return wheel[index];
}

template <class T>
vector<T> Wheel<T>::nextBucket() {
    cascade = false;
    if (++index==wheel.size()) {
        index = 0;
        cascade = true;
    }
    auto result = wheel[index];
    wheel[index].clear();
    return result;
}

template <class T>
bool Wheel<T>::hasCascade() {
    return cascade;
}

template <class T>
unsigned int Wheel<T>::remainingTick() {
    return lenght - index;
}

#endif //WHEEL_TIMER_WHEEL_H