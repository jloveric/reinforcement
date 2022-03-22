#include "grid_world.hh"
#include <iostream>
#include <string>

using namespace std;

int main() {
  cout << "are we even in here?\n";
  string filename("inputs/grid_world0.txt");
  auto world_map = readWorldFile(filename);

  auto world = World(20, 20);
  world.randomWorld(0.2, WALL);
  world.randomWorld(0.1, GOLD);
  world.print();

  auto action = GridWorldAction(world);
  auto state = GridWorldState(world);
  state.setCurrentIndex(0);

  // Start from the upper corner
  bool finished = false;
  int count = 0;
  while (!finished) {
    // choose a random direction
    auto a = static_cast<GridAction>(rand() % 4);
    action.setAction(a);
    action.apply(state);
    auto ci = state.getCurrentIndex();

    cout << ci << std::endl;
    count++;
    if (count > 100)
      finished = true;
  }

  return 0;
}