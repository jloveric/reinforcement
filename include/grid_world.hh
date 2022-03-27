#pragma once
#include "reinforce.hh"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Bad, I know.  When modules are working that won't be an issue.
using namespace std;

class GridWorldState;
class GridWorldAction;

enum GridAction { UP, DOWN, LEFT, RIGHT };

/**
 * @brief Define the value of the different characters in the world.
 */
enum WorldType : char {
  WALL = 'w',
  EMPTY = '0',
  COIN = 'c',
  GOLD = 'g',
  EXIT = 'e',
  PLAYER = 'x'
};

/**
 * @brief Return a random double between 0 and 1.
 *
 * @return double
 */
double randomFraction();

/**
 * @brief Grid world description.  MxN map containing characters
 * to depict obstacles etc...
 */
class World {
public:
  World(int width, int height);

  int getValue(int x, int y) const;
  int getValue(int index) const;
  void setValue(int x, int y, int val);
  void setValue(int index, int val);
  void worldFromVector(vector<char> other_grid);
  bool validMove(int x, int y) const;
  int getIndex(int x, int y) const;
  int gridX(int index) const;
  int gridY(int index) const;
  void print();

  // fraction of points that are walls
  void randomWorld(const double fraction, const char value);
  void randomValue(char c);

private:
  vector<char> grid;
  int width;
  int height;
};

/**
 * @brief State of the world, this is generally a subset of
 * the world which includes the persons location.  Could potentially
 * be a copy of the entire world we want that to be visible to the
 * observer.
 */
class GridWorldState : public State {
public:
  GridWorldState() {}
  GridWorldState(World &_world);
  void move(int x, int y);
  void bump(int dx, int dy);
  void setCurrentIndex(int index);
  int getCurrentIndex() const;
  int gridX() const;
  int gridY() const;

  // GridWorldState(const GridWorldState &other);
  // GridWorldState(GridWorldState &&other);

private:
  // I'd like this to be const.  I only need the index function anyway.
  World *world;

  // map from linear index to map value
  unordered_map<int, char> world_diff;
  int current_index;
  std::vector<int> path;
};

/**
 * @brief Actions in the grid world.  In this case they are stacked
 * into one class.
 *
 */
class GridWorldAction : public Action<GridWorldState> {
public:
  GridWorldAction() {}
  GridWorldAction(World &_world);

  // This needs to be called before valid move
  void setAction(GridAction a);
  bool validAction(GridWorldState &s) const;
  void apply(GridWorldState &s) override;

private:
  GridAction action;

  // We want the pointer copied
  World *world;
};

// Using a typedef for now since it uses default Q.
typedef Q<GridWorldAction, GridWorldState, double> GridWorldQ;

vector<char> readWorldFile(const string filename);