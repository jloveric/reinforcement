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

  // Just check that the correct keys are returned for the exact values
  /*
  auto ans = apply->apply(test);
  BOOST_CHECK_EQUAL(ans[0], 6);
  BOOST_CHECK_EQUAL(ans[1], 7);
  BOOST_CHECK_EQUAL(ans[2], 8);

  Data test2({1, 2, 3});
  ans = apply->apply(test2);
  BOOST_CHECK_EQUAL(ans[0], 3);
  BOOST_CHECK_EQUAL(ans[1], 4);
  BOOST_CHECK_EQUAL(ans[2], 5);

  // Check an intermediate value
  Data test3({1, 1.5, 2.0});
  ans = apply->apply(test3);
  BOOST_CHECK_EQUAL(ans[0], 6);
  BOOST_CHECK_EQUAL(ans[1], 7);
  BOOST_CHECK_EQUAL(ans[2], 8);
  std::cout << "ans " << ans[0] << " " << ans[1] << " " << ans[2] << "\n";*/
}
