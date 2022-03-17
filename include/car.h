#pragma once

#include <cstdint>

#include "gas_station.h"
#include "safe_queue.h"

class Car
{
    public:
        Car(GasStation* station, SafeQueue<Car*>* cars, uint32_t id);

        void run(); // car thread function

        void start();

        // return how many times car was filledup
        uint64_t fillups() const { return _fill_ups; }
        uint32_t id() const { return _id; }

    private:
        uint64_t _fill_ups = 0;

        GasStation* _station = nullptr;
        SafeQueue<Car*>* _cars;

        uint32_t _id;

        uint16_t _sleep_ms;
};