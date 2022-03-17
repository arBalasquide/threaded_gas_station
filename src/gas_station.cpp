#include "gas_station.h"

int GasStation::available_pump() {
    if (!_busy[0]) {
        return 1;
    }
    else if (!_busy[1]) {
        return 2;
    }

    return 0;
}

void GasStation::use_pump(int8_t number) {
    if (number) {
        _busy[number-1] = true;
    }
}
void GasStation::leave_pump(int8_t number) {
    if (number) {
        _busy[number-1] = false; 
        _fill_ups[number-1]++;
    }
}

bool GasStation::busy() {
    return (_busy[0] || _busy[1]);
}

std::string GasStation::str() {
    std::stringstream msg;
    msg << "Pump #1 fillups: " << _fill_ups[0] << "\n";
    msg << "Pump #2 fillups: " << _fill_ups[1] << "\n";

    return msg.str();
}