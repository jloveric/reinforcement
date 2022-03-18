
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
  // For a specific Q, we actually want to copy the current state
  Q(ACTION a, STATE s, REWARD r)
      : action(std::move(a)), state(std::move(s)), reward(std::move(r)) {}

private:
  ACTION action;
  STATE state;
  REWARD reward;
  std::string hash;
};

template <class ACTION, class STATE>
std::string compute_default_hash(ACTION &a, STATE &s) {
  std::stringstream out;
  out << a.getHash() << s.getHash();
  return out.str();
}