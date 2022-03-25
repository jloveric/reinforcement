#include "grid_world.hh"
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>

using namespace std;

int main() {
  // Using ncurses api here which is in c.

  cout << "Starting" << endl;
  string filename("inputs/grid_world0.txt");
  auto world_map = readWorldFile(filename);

  auto world = World(20, 20);
  world.randomWorld(0.2, WALL);
  world.randomWorld(0.1, GOLD);
  world.setValue(19, 19, 'e');
  world.print();

  auto action = GridWorldAction(world);
  auto state = GridWorldState(world);
  state.setCurrentIndex(0);

  vector<GridWorldQ> q;

  // Start from the upper corner
  bool finished = false;
  int count = 0;
  while (!finished) {
    // choose a random direction
    auto a = static_cast<GridAction>(rand() % 4);

    // TODO - Seems like this should be automatic. Hash is different
    // for every action and state (should also be different for outcome but
    // right now that is deterministic.)
    action.setHash(string{a});
    state.setHash(string{state.getCurrentIndex()});

    action.setAction(a);
    action.apply(state);

    auto ci = state.getCurrentIndex();
    auto val = world.getValue(ci);

    double reward = -1.0;
    switch (val) {
    case EXIT:
      val = 10;
      break;
    case GOLD:
      val = 1;
      break;
    }

    // This is a overkill for gridworld, but might be better for much more
    // complex systems like conversational agents.
    q.push_back(GridWorldQ(
        action, state, reward,
        compute_default_hash<GridWorldAction, GridWorldState>(action, state)));

    cout << ci << "\n";

    count++;
    if (count > 100)
      finished = true;
  }

  return 0;
}