#pragma once

#include <cstdint>
#include <string>
#include <sstream>

// Singleton
class GasStation 
{
    public:
        static GasStation* get() {
            static GasStation instance;

            return &instance;
        };

        // delete methods we don't want to accidentally use
        GasStation(GasStation const&)     = delete;
        void operator=(GasStation const&) = delete;

        // return which pump is available, 0 when none
        int available_pump();
        bool is_open() const { return _open; }

        void open() { _open = true; }
        void close() { _open = false; }

        std::string str();

        bool busy();

        void use_pump(int8_t number);
        void leave_pump(int8_t number);

    private:
        GasStation() {};

        // flag for closing gas station
        bool _open = true;
        bool _busy[2] = {false, false};

        uint32_t _fill_ups[2] = {0,0};
};