#include <thread>
#include <chrono>
#include <random>

#include "car.h"

#define SLEEP_MS 30
#define RANDOM_SLEEP false

Car::Car(GasStation* station, SafeQueue<Car*>* cars, uint32_t id) {
    _id = id;
    _cars = cars;
    _station = station;
    
    _sleep_ms = SLEEP_MS;

#if RANDOM_SLEEP
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 50); // define the range

    _sleep_ms = distr(gen);
#endif

    std::thread _thread(&Car::run, this);
    _thread.detach();
}

void Car::run() {
    while(_station->is_open()) {
        // check if we're next in line
        if (_id == _cars->front()->id()) {
            if (_station->available_pump()) {
                start();
            }
        }
    }
}

void Car::start() {
    int8_t pump_number = _station->available_pump(); 

    _station->use_pump(pump_number);
    
    // leave queue to go into pump
    _cars->dequeue();

    // fill up
    std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_ms));

    _fill_ups++;

    _cars->enqueue(this);

    _station->leave_pump(pump_number);
}