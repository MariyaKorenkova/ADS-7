// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    if (first->next == first) {
      delete first;
      first = nullptr;
      return;
    }
    Car* current = first->next;
    while (current != first) {
      Car* temp = current;
      current = current->next;
      delete temp;
    }
    delete first;
    first = nullptr;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};

    if (!first) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* lastCar = first->prev;
        newCar->next = first;
        first->prev = newCar;
        newCar->prev = lastCar;
        lastCar->next = newCar;
        first = newCar;
    }
}
int Train::getOpCount() {
        return countOp;
}

int Train::getLength() {
    if (!first) return 0;
    if (first->next == first) return 1;
    countOp = 0;
    Car* current = first;
    int carAmount = 1;
    if (!current->light) {
        current->light = true;
    }
    current = current->next;
    countOp += 2;
    while (!current->light) {
        current = current->next;
        countOp += 2;
        carAmount++;
    }
    current->light = false;
    if (!first->light) {
        return carAmount;
    }

    while (true) {
        current = first;
        carAmount = 1;
        if (!current->light) {
            current->light = true;
        }
        current = current->next;
        countOp += 2;
        while (!current->light) {
            current = current->next;
            countOp += 2;
            carAmount++;
        }
        current->light = false;
        if (!first->light) return carAmount;
    }
}
