# reinforcement
Generic c++20 reinforcement learning library.  WIP to get some experience in both RL and c++20.
Alas, looks like cmake doesn't really support modules yet (will work on hacks this) so just using the command line to build for the moment.
```
g++ -c -std=c++20 -fmodules-ts  reinforce.cxx main.cxx grid_world.cxx
```
and
```
g++ main.o reinforce.o -o app.app
```