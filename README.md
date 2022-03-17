# threaded_gas_station

Multithreaded program to simulate a gas station where each car, represented as individual threads, communicate with the station to fill up gas.

## Usage

```
g++ -o main src/*.cpp -I include/
./main
```

You can play with `EXECUTION_TIME_S` define in `main.cpp` to change the execution time of the main program.

The define `RANDOM_SLEEP` in `car.cpp` determines whether or not to assign random sleep ms to the car fill up action. If set to false, it uses the value defined by `SLEEP_MS`.
