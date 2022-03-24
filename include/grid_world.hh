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
enum WorldType : char {
  WALL = 'w',
  EMPTY = '0',
  COIN = 'c',
  GOLD = 'g',
  EXIT = 'e',
  PLAYER = 'x'
};

double random_fraction();

// This is the static world
class World {
public:
  World(int width, int height);

  int getValue(int x, int y) const;
  void setValue(int x, int y, int val);
  void worldFromVector(vector<char> other_grid);
  bool validMove(int x, int y) const;
  int index(int x, int y) const;
  int gridX(int index) const;
  int gridY(int index) const;
  void print();

  // fraction of points that are walls
  void randomWorld(const double fraction, const char value);
  void randomValue(char c);

  World(const World &other) = delete;
  World(World &&other) = delete;

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
  int getCurrentIndex() const;
  int gridX() const;
  int gridY() const;

  GridWorldState(const GridWorldState &other) = delete;
  GridWorldState(GridWorldState &&other) = delete;

private:
  // I'd like this to be const.  I only need the index function anyway.
  World *world;

  // map from linear index to map value
  unordered_map<int, char> world_diff;
  int current_index;
  std::vector<int> path;
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

  GridWorldAction(const GridWorldAction &world) = delete;
  GridWorldAction(GridWorldAction &&world) = delete;

private:
  GridAction action;
  World *world;
};

// This could just be a typedef
class GridWorldQ : public Q<GridWorldAction, GridWorldState, double> {
public:
};

vector<char> readWorldFile(const string filename);