
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

class State {
private:
  std::string hash;

public:
  State() {}
  virtual std::string getHash() { return hash; };
  virtual void setHash(std::string s) { hash = s; }
};

template <class STATE> class Action {
private:
  std::string hash;

public:
  Action() {}
  virtual std::string getHash() { return hash; };
  virtual void apply(STATE &s) = 0;
  virtual void setHash(std::string s) { hash = s; }
};

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
  REWARD getReward() { return reward; }
  STATE getState() { return state; }
  ACTION getAction() { return action; }

private:
  ACTION action;
  STATE state;
  REWARD reward;
  REWARD q_value;
  std::string hash;
};

template <class ACTION, class STATE>
std::string compute_default_hash(ACTION &a, STATE &s) {
  std::stringstream out;
  out << a.getHash() << s.getHash();
  return out.str();
}