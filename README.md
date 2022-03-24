# reinforcement
Generic c++20 reinforcement learning library.  Major WIP (work in progress).  As of this writing c++20 modules are still
too buggy so resorting to header files!
```
cmake .
make
```
and then run
```
./reinforce
```
run the tests
```
ctest
```
I'll make a docker container for this at some point, but for now
gonna need boost for testing
```
sudo apt-get install libboost-all-dev
```
install ncurses
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```