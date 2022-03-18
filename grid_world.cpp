
#include "reinforce.hh"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GridWorldState;
class GridWorldAction;

enum GridAction { UP, DOWN, LEFT, RIGHT };

// This is the static world
class World {
public:
  World(int width, int height) : width(width), height(height) {
    grid = vector<char>(width * height, '0');
  }

  int get_value(int x, int y) const { return grid[index(x, y)]; }

  void set_value(int x, int y, int val) { grid[index(x, y)] = val; }

  void world_from_vector(vector<char> other_grid) { grid = other_grid; }

  bool valid_move(int x, int y) const {
    if (x >= width || x < 0 || y >= height || y < 0) {
      return false;
    } else if (grid[index(x, y)] == 'w') {
      return false;
    }
    return true;
  }

  int index(int x, int y) const {
    assert(x < width && x >= 0);
    assert(y < height && y >= 0);
    return y * width + x;
  }

  int gridX(int index) { return index % width; }

  int gridY(int index) { return index / width; }

  void print() {
    int count = 0;
    for (auto j = 0; j < height; j++) {
      for (auto i = 0; i < width; i++) {
        cout << grid[count];
        count++;
      };
      cout << "\n";
    }
  }

  void random_world() {}

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
  GridWorldState(World &_world) : world(&_world) {}

  void move(int x, int y) {
    auto new_index = world->index(x, y);
    if (new_index != current_index) {
      world_diff.erase(current_index);
      world_diff[current_index] = 'x';
    }
  }

  void bump(int dx, int dy) {
    auto cx = world->gridX(current_index);
    auto cy = world->gridY(current_index);
    move(cx + dx, cy + dy);
  }

  void setCurrentIndex(int index) { current_index = std::move(index); }
  int getCurrentIndex() { return current_index; }

  int gridX() { return world->gridX(current_index); }

  int gridY() { return world->gridY(current_index); }

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
  GridWorldAction(World &_world) : world(&_world) {}

  // This needs to be called before valid move
  void setAction(GridAction a) { action = a; }

  bool validAction(GridWorldState &s) const {

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

  void apply(GridWorldState &s) override {
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

private:
  GridAction action;
  World *world;
};

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

  auto world = World(10, 5);
  world.world_from_vector(world_map);
  world.print();
  //   Update rules

  //
  return 0;
}