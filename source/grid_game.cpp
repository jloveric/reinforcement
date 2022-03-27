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

  int size = 10;
  auto world = World(10, 10);
  world.randomWorld(0.2, WALL);
  // world.randomWorld(0.1, GOLD);
  world.setValue(size * size - 1, 'e');
  world.print();

  auto action = GridWorldAction(world);
  auto state = GridWorldState(world);

  vector<vector<GridWorldQ>> q;
  unordered_map<string, GridWorldQ> qmap;

  int trials = 50;
  int max_count = 1000;

  for (auto i = 0; i < trials; ++i) {
    state.setCurrentIndex(0);
    vector<GridWorldQ> sample;
    bool finished = false;

    // Start from the upper corner
    int count = 0;
    while (!finished) {
      // choose a random direction
      auto a = static_cast<GridAction>(rand() % 4);

      // TODO - Seems like this should be automatic. Hash is different
      // for every action and state (should also be different for outcome but
      // right now that is deterministic.)
      action.setHash(string{a});
      state.setHash(to_string(state.getCurrentIndex()));

      action.setAction(a);
      action.apply(state);

      auto ci = state.getCurrentIndex();
      auto val = world.getValue(ci);

      double reward = -1.0;
      switch (val) {
      case EXIT:
        reward = 10;
        finished = true;
        break;
      case GOLD:
        reward = 1;
        break;
      }

      // This is a overkill for gridworld, but might be better for much more
      // complex systems like conversational agents.
      sample.push_back(
          GridWorldQ(action, state, reward,
                     compute_default_hash<GridWorldAction, GridWorldState>(
                         action, state)));

      count++;
      if (count > max_count)
        finished = true;
    }

    q.push_back(sample);
  }

  //
  for (auto i = 0; i < 100; ++i) {
    valueIteration<GridWorldQ>(qmap, q, 1.0);
  }

  for (auto &[key, val] : qmap) {
    cout << val.getQ() << "\n";
  }

  // Now that we have the samples lets perform the

  return 0;
}