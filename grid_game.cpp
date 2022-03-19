#include "grid_world.hh"
#include <iostream>
#include <string>

using namespace std;

int main() {
  cout << "are we even in here?\n";
  string filename("inputs/grid_world0.txt");
  auto world_map = readWorldFile(filename);

  auto world = World(20, 20);
  world.random_world(0.2, 'w');
  world.random_world(0.1, 'g');
  world.print();

  // Start from the upper corner
  bool finished = false;
  while (!finished) {
    // choose a random direction
    auto a = rand() % 4;
  }

  return 0;
}