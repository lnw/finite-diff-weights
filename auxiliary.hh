#ifndef AUXILIARY_HH
#define AUXILIARY_HH

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>


template <typename S, typename T> std::ostream& operator<<(std::ostream& s, const std::pair<S,T>& p) {
  s << "{" << p.first << "," << p.second << "}";
  return s;
}

#define container_output(container) \
  template <typename T> std::ostream& operator<<(std::ostream& s, const container<T>& v) \
  { \
  s << "{"; \
  for(typename container<T>::const_iterator x(v.begin());x!=v.end();){ \
    s << *x; \
    if(++x!=v.end()) s << ","; \
  } \
  s << "}"; \
  return s; \
}

container_output(std::vector);


#endif
