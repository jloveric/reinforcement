
#include "grid_world.hh"
#include "reinforce.hh"

using namespace std;

double randomFraction() {
  double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  return r;
}

World::World(int width, int height) : width(width), height(height) {
  grid = vector<char>(width * height, EMPTY);
}

int World::getValue(int x, int y) const { return grid[index(x, y)]; }

void World::setValue(int x, int y, int val) { grid[index(x, y)] = val; }

void World::worldFromVector(vector<char> other_grid) { grid = other_grid; }

bool World::validMove(int x, int y) const {
  if (x >= width || x < 0 || y >= height || y < 0) {
    return false;
  } else if (grid[index(x, y)] == WALL) { // TODO: magic number
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
void World::randomWorld(const double fraction, const char value) {
  transform(grid.begin(), grid.end(), grid.begin(),
            [fraction, value](char c) -> char {
              auto r = randomFraction();

              if (r < fraction) {
                return value;
              }
              return c;
            });
}

void World::randomValue(char c) {
  auto r = randomFraction();
  auto random_index = r * grid.size();
  grid[random_index] = c;
}

GridWorldState::GridWorldState(World &_world) : world(&_world) {}

void GridWorldState::move(int x, int y) {
  auto new_index = world->index(x, y);
  if (new_index != current_index) {
    world_diff.erase(current_index);
    world_diff[new_index] = PLAYER;
    current_index = new_index;
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
    return world->validMove(cx, cy + 1);
  case DOWN:
    return world->validMove(cx, cy - 1);
  case LEFT:
    return world->validMove(cx - 1, cy);
  case RIGHT:
    return world->validMove(cx + 1, cy);
  }
  return false;
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
