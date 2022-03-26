
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * @brief State class which describes the state of the system.
 *
 */
class State {
private:
  std::string hash;

public:
  State() {}
  virtual std::string getHash() { return hash; };
  virtual void setHash(std::string s) { hash = s; }
};

/**
 * @brief Action base class (pseudo interface!)
 *
 * @tparam STATE
 */
template <class STATE> class Action {
private:
  std::string hash;

public:
  Action() {}
  virtual std::string getHash() { return hash; };
  virtual void apply(STATE &s) = 0;
  virtual void setHash(std::string s) { hash = s; }
};

/**
 * @brief Generic reinforcement learning Q
 *
 * @tparam ACTION the action class
 * @tparam STATE the state class
 * @tparam REWARD the reward type (typically double or int)
 */
template <class ACTION, class STATE, class REWARD> class Q {
public:
  // For a specific Q, we actually want to copy the current state
  // Q(S,A) = r + gamma*max_{a'}Q(s', a')
  Q(ACTION a, STATE s, REWARD r, std::string h)
      : action(std::move(a)), state(std::move(s)), reward(std::move(r)),
        hash(std::move(h)) {}

  void setAction(ACTION &a) { action = a; }
  void setState(STATE &s) { state = s; }
  void setReward(REWARD &r) { reward = r; }
  void setQ(REWARD &q) { q_value = q; }

  REWARD operator()() const { return q_value; }
  REWARD getReward() const { return reward; }
  STATE getState() const { return state; }
  ACTION getAction() const { return action; }

  std::string getHash() const { return hash; }

private:
  ACTION action;
  STATE state;
  REWARD reward;
  REWARD q_value;
  std::string hash;
};

/**
 * @brief Just compute a hash by combining that action and state hashes.
 *
 * @tparam ACTION action class
 * @tparam STATE state class
 * @param a instances of ACTION action.
 * @param s instance of STATE state.
 * @return std::string
 */
template <class ACTION, class STATE>
std::string compute_default_hash(ACTION &a, STATE &s) {
  std::stringstream out;
  out << a.getHash() << s.getHash();
  return out.str();
}

/**
 * @brief Copy all the samples from the paths to the map of graph nodes.  Since
 * we are only sampling the graph nodes we don't ever have the capacity to
 * traverse the entire graph.
 *
 * @tparam QVALUE Reinforcement learning Q (i.e. graph node)
 * @param qmap map containing hash to Q pairs.
 * @param paths vector of paths where each path is a sequence of Q values.
 */
template <class QVALUE>
void updateGraphSamples(std::unordered_map<std::string, QVALUE> &qmap,
                        std::vector<std::vector<QVALUE>> &paths) {

  for (auto &element : paths) {
    for (auto &q : element) {

      if (!qmap.contains(q.getHash())) {
        qmap[q.getHash()] = q;
      }
    }
  }
}

/**
 * @brief Iterate over the new paths and update the Q values that have been
 * sampled in the set of paths.
 *
 * @tparam QVALUE
 * @param qmap map containing hash to Q pairs
 * @param paths vector of paths where each path is a sequence of Q values.
 */
template <class QVALUE>
void valueIteration(std::unordered_map<std::string, QVALUE> &qmap,
                    std::vector<std::vector<QVALUE>> &paths) {

  // Add any there.
  for (auto element : paths) {
  }
}