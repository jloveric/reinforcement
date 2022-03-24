#define BOOST_TEST_MODULE testGridWorld
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <memory>

#include "grid_world.hh"

using namespace std;

BOOST_AUTO_TEST_CASE(TestGridWorld) {

  string filename = "inputs/grid_world0.txt";
  auto world_map = readWorldFile(filename);

  auto world = World(20, 20);
  world.randomWorld(0.2, WALL);
  world.randomWorld(0.1, GOLD);
  world.print();

  auto action = GridWorldAction(world);
  auto state = GridWorldState(world);
  state.setCurrentIndex(0);

  // Do nothing, just verifying things arent crashing.
  BOOST_CHECK_EQUAL(0, 0);
}
