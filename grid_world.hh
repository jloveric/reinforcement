#pragma once
#include "reinforce.hh"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GridWorldState;
class GridWorldAction;

enum GridAction { UP, DOWN, LEFT, RIGHT };

double random_fraction();

// This is the static world
class World {
public:
  World(int width, int height);

  int get_value(int x, int y) const;
  void set_value(int x, int y, int val);
  void world_from_vector(vector<char> other_grid);
  bool valid_move(int x, int y) const;
  int index(int x, int y) const;
  int gridX(int index);
  int gridY(int index);
  void print();

  // fraction of points that are walls
  void random_world(const double fraction, const char value);
  void random_value(char c);

private:
  vector<char> grid;
  int width;
  int height;
};

// This is the diff from the static world.  I could just use the static
// world, but then the memory consumed by the state would be much larger
// I can define it here by only the dynamic objects
class GridWorldState : public State {
public:
  GridWorldState(World &_world);
  void move(int x, int y);
  void bump(int dx, int dy);
  void setCurrentIndex(int index);
  int getCurrentIndex();
  int gridX();
  int gridY();

private:
  // I'd like this to be const.  I only need the index function anyway.
  World *world;

  // map from linear index to map value
  unordered_map<int, char> world_diff;
  int current_index;
};

// Breaking my own design!  I'm putting all actions into
// one so it's simpler for this specific case!
class GridWorldAction : public Action<GridWorldState> {
public:
  GridWorldAction(World &_world);

  // This needs to be called before valid move
  void setAction(GridAction a);
  bool validAction(GridWorldState &s) const;

  void apply(GridWorldState &s) override;

private:
  GridAction action;
  World *world;
};

// This could just be a typedef
class GridWorldQ : public Q<GridWorldAction, GridWorldState, double> {
public:
};

vector<char> readWorldFile(const string filename);