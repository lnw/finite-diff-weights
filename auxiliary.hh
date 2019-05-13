#ifndef AUXILIARY_HH
#define AUXILIARY_HH

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename S, typename T> ostream& operator<<(ostream& s, const pair<S,T>& p) {
  s << "{" << p.first << "," << p.second << "}";
  return s;
}

#define container_output(container) \
  template <typename T> ostream& operator<<(ostream& s, const container<T>& v) \
  { \
  s << "{"; \
  for(typename container<T>::const_iterator x(v.begin());x!=v.end();){ \
    s << *x; \
    if(++x!=v.end()) s << ","; \
  } \
  s << "}"; \
  return s; \
}

container_output(vector);

// auto abs_comp=[](int i, int j) { return abs(i) < abs(j); };
auto abs_comp=[](double i, double j) { return abs(i) < abs(j); };


#endif
