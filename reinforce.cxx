module;

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

export module reinforce;
// seems like this is safe inside a module!
using namespace std;
export void func();

/*
export template <class STATE> class Action;
export class State;
export template <class ACTION, class STATE, class REWARD> class Q;
export template <class ACTION, class STATE>*/

// string compute_default_hash(ACTION &a, STATE &s);

void func() { cout << "hello, world!\n"; }

export class State {
public:
  State() {}
  virtual string getHash() { return hash; };
  virtual void setHash(string s) { hash = s; }

private:
  string hash;
};

export template <class STATE> class Action {
public:
  Action() {}
  virtual string getHash() { return hash; };
  virtual void apply(STATE &s) = 0;
  virtual void setHash(string s) { hash = s; }

private:
  string hash;
};

export template <class ACTION, class STATE, class REWARD> class Q {
  // For a specific Q, we actually want to copy the current state
  Q(ACTION a, STATE s, REWARD r)
      : action(std::move(a)), state(std::move(s)), reward(std::move(r)) {}

private:
  ACTION action;
  STATE state;
  REWARD reward;
  string hash;
};

export template <class ACTION, class STATE>
string compute_default_hash(ACTION &a, STATE &s) {
  stringstream out;
  out << a.getHash() << s.getHash();
  return out.str();
}