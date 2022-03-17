
#include <assert.h>
#include <unordered_map>
#include <vector>
import reinforce;

using namespace std;

// State is meant to be only the difference between the base world
// and the current state...  Though it could just as well be the entire
// world. Ideally this reduces the memory footprint.
class GridWorldState : public State {
public:
  GridWorldState() {}

private:
  // map from linear index to
  unordered_map<int, char> world;
};

class Up : public Action<GridWorldState> {
public:
  Up() { setHash("up"); }
  void apply(GridWorldState &s) override{};

private:
};

class Down : public Action<GridWorldState> {
public:
  Down() { setHash("down"); }
  void apply(GridWorldState &s) override{};

private:
};

class Left : public Action<GridWorldState> {
public:
  Left() { setHash("left"); }
  void apply(GridWorldState &s) override{};

private:
};

class Right : public Action<GridWorldState> {
public:
  Right() { setHash("right"); }
  void apply(GridWorldState &s) override{};

private:
};

class World {
public:
  World(int width, int height) : width(width), height(height) {}

  int get_value(int x, int y) { return grid[index(x, y)]; }

  void set_value(int x, int y, int val) { grid[index(x, y)] = val; }

  void world_from_vector(vector<char> other_grid) { grid = other_grid; }

private:
  int index(int x, int y) {
    assert(x < width && x >= 0);
    assert(y < height && y >= 0);
    return y * width + x;
  }

  vector<char> grid;
  int width;
  int height;
};

void learn() {
  // Initialize world state
  int height = 10, width = 10;
  vector<char> base(100, '0');
  auto world = World(10, 10);

  // Update rules

  //
}