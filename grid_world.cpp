
#include "reinforce.hh"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <grid_world.hh>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class GridWorldState;
class GridWorldAction;

enum GridAction { UP, DOWN, LEFT, RIGHT };

// This is the static world

World::World(int width, int height) : width(width), height(height) {
  grid = vector<char>(width * height, '0');
}

int World::get_value(int x, int y) const { return grid[index(x, y)]; }

void World::set_value(int x, int y, int val) { grid[index(x, y)] = val; }

void World::world_from_vector(vector<char> other_grid) { grid = other_grid; }

bool World::valid_move(int x, int y) const {
  if (x >= width || x < 0 || y >= height || y < 0) {
    return false;
  } else if (grid[index(x, y)] == 'w') {
    return false;
  }
  return true;
}

int World::index(int x, int y) const {
  assert(x < width && x >= 0);
  assert(y < height && y >= 0);
  return y * width + x;
}

int World::gridX(int index) { return index % width; }

int World::gridY(int index) { return index / width; }

void World::print() {
  int count = 0;
  for (auto j = 0; j < height; j++) {
    for (auto i = 0; i < width; i++) {
      cout << grid[count];
      count++;
    };
    cout << "\n";
  }
}

// fraction of points that are walls
void World::random_world(const double fraction) {
  transform(grid.begin(), grid.end(), grid.begin(), [fraction](char c) -> char {
    double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

    if (r < fraction) {
      return 'w';
    }
    return c;
  });
}

GridWorldState::GridWorldState(World &_world) : world(&_world) {}

void GridWorldState::move(int x, int y) {
  auto new_index = world->index(x, y);
  if (new_index != current_index) {
    world_diff.erase(current_index);
    world_diff[current_index] = 'x';
  }
}

void GridWorldState::bump(int dx, int dy) {
  auto cx = world->gridX(current_index);
  auto cy = world->gridY(current_index);
  move(cx + dx, cy + dy);
}

void GridWorldState::setCurrentIndex(int index) {
  current_index = std::move(index);
}
int GridWorldState::getCurrentIndex() { return current_index; }

int GridWorldState::gridX() { return world->gridX(current_index); }

int GridWorldState::gridY() { return world->gridY(current_index); }

// Breaking my own design!  I'm putting all actions into
// one so it's simpler for this specific case!

GridWorldAction::GridWorldAction(World &_world) : world(&_world) {}

// This needs to be called before valid move
void GridWorldAction::setAction(GridAction a) { action = a; }

bool GridWorldAction::validAction(GridWorldState &s) const {

  auto cx = s.gridX();
  auto cy = s.gridY();

  switch (action) {
  case UP:
    return world->valid_move(cx, cy + 1);
  case DOWN:
    return world->valid_move(cx, cy - 1);
  case LEFT:
    return world->valid_move(cx - 1, cy);
  case RIGHT:
    return world->valid_move(cx + 1, cy);
  }
}

void GridWorldAction::apply(GridWorldState &s) {
  if (validAction(s)) {
    switch (action) {
    case UP:
      s.bump(0, 1);
      break;
    case DOWN:
      s.bump(0, -1);
      break;
    case LEFT:
      s.bump(-1, 0);
      break;
    case RIGHT:
      s.bump(1, 0);
      break;
    }
  }
}

vector<char> readWorldFile(string filename) {
  vector<char> data;
  cout << "reading file " << filename << "\n";

  string line;
  ifstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      for (auto i : line) {
        if (i != '\n') {
          data.push_back(i);
        }
      }
    }
    file.close();
  }

  else
    cout << "Unable to open file";
  return data;
}

int main() {
  cout << "are we even in here?\n";
  string filename("inputs/grid_world0.txt");
  auto world_map = readWorldFile(filename);

  auto world = World(20, 20);
  world.random_world(0.2);
  // world.world_from_vector(world_map);
  world.print();

  return 0;
}