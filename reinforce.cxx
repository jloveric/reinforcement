module;

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

export module reinforce;
// seems like this is safe inside a module!
using namespace std;
export void func();

export template <class STATE> class Action;
export class State;
export template <class ACTION, class STATE, class REWARD> class Q;
export template <class ACTION, class STATE>
string compute_default_hash(ACTION &a, STATE &s);

void func() { cout << "hello, world!\n"; }

template <class STATE> class Action {
public:
  Action() {}
  virtual string get_hash() = 0;
  virtual void apply(STATE &s) = 0;

private:
  string hash;
};

class State {
public:
  State() {}
  virtual string gethash() = 0;
  virtual void set_hash(string s) { hash = s; }

private:
  string hash;
};

template <class ACTION, class STATE, class REWARD> class Q {
  // For a specific Q, we actually want to copy the current state
  Q(ACTION a, STATE s, REWARD r)
      : action(std::move(a)), state(std::move(s)), reward(std::move(r)) {}

private:
  ACTION action;
  STATE state;
  REWARD reward;
  string hash;
};

template <class ACTION, class STATE>
string compute_default_hash(ACTION &a, STATE &s) {
  stringstream out;
  out << a.get_hash() << s.get_hash();
  return out.str();
}