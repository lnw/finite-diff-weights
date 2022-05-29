#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "auxiliary.hh"


// M: maximum derivative
// N: maximum accuracy
// x0: position at which value/derivative is approximated
// alpha: grid point position
template <typename T>
auto get_weights(const int M, const int N, const T x0, const std::vector<T>& alpha){
  std::vector<std::vector<std::vector<T>>> delta(M+1, std::vector<std::vector<T>>(N+1, std::vector<T>(N+1, 0.0)));
  delta[0][0][0] = 1.0;
  T c1 = 1.0;
  for (int n=1; n<=N; n++){
    T c2 = 1.0;

    for (int nu=0; nu<n; nu++){
      T c3 = alpha[n] - alpha[nu];
      c2 *= c3;

      // if (n<=M) delta[n][n-1][nu] = 0.0;
      for (int m=0; m <= std::min(n,M); m++){
        if(m==0) delta[m][n][nu] = ((alpha[n] - x0)*delta[m][n-1][nu]) / c3;
        else delta[m][n][nu] = ((alpha[n] - x0)*delta[m][n-1][nu] - m*delta[m-1][n-1][nu]) / c3;
        // cout << "writing " << n << ", " << nu << ", " << m << endl;
      }
    }
    for (int m=0; m <= std::min(n,M); m++){
      if (m==0) delta[m][n][n] = c1/c2 * ( - (alpha[n-1] - x0)*delta[m][n-1][n-1]);
      else delta[m][n][n] = c1/c2 * (m*delta[m-1][n-1][n-1] - (alpha[n-1] - x0)*delta[m][n-1][n-1]);
      // cout << "writing " << n << ", " << n << ", " << m << endl;
    }
    c1 = c2;
  }

  return delta;
}


int main(int ac, char **av) {

  const double eps = 1.e-10;
  const int M = 3; // max derivative
  const int N = 12; // max accuracy
  // const double x0 = 0;
  // vector<double> alpha({ -3, -2, -1, 0, 1, 2, 3});
  // vector<double> alpha({-1,-0.830223896279,-0.468848793471,0,0.468848793471,0.830223896279,1}); // gauss lobatto
  std::vector<double> alpha({-3,-2.4906716888357,-1.40654638041214,0,1.40654638041214,2.4906716888357,3, 6-2.4906716888357,6-1.40654638041214,6,7.40654638041214,8.4906716888357,9}); // gauss lobatto
  const int n_pt = alpha.size();
  assert(n_pt > N);
  if(N+1 != n_pt) std::cerr << " !!! Normally, one would want an accuracy of one lower than the number of points. !!!" << std::endl;

  for (int foo=0; foo<alpha.size(); foo++){
    double x0 = alpha[foo];

    std::vector<double> alpha_sorted(alpha);
  
    // alpha should be sorted ascendingly
    std::sort(alpha.begin(), alpha.end());
    // cout << alpha << endl;
  
    // but get_weights works on an alpha with increasing distance from x0
    for (double &d: alpha_sorted) d -= x0;
    auto abs_comp = [](auto i, auto j) { return std::abs(i) <= std::abs(j); };
    std::sort(alpha_sorted.begin(), alpha_sorted.begin(), abs_comp);
    for (double &d: alpha_sorted) d += x0;
    // cout << "alpha sorted: " << alpha_sorted << endl;
  
    std::vector<double> map(alpha.size());
    for (int i=0; i<alpha.size(); i++){
      for (int j=0; j<alpha.size(); j++){
        if( (alpha[j] - alpha_sorted[i]) < eps) map[i] = j;
      }
    }
    // cout << "map: " << map << endl;
  
    std::vector<std::vector<std::vector<double>>> delta = get_weights<double>(M, N, x0, alpha_sorted);
  
    std::cout << "x0: " << x0 << std::endl;
    std::cout << "alpha: " << alpha << std::endl << std::endl;
  
    // reorder according to ordered alpha
    for(int m=0; m<M+1; m++){
      for(int j=0; j<N+1; j++){
        std::vector<double> tmp(N+1);
        for (int k=0; k<N+1; k++){
          tmp[map[k]] = delta[m][j][k];
        }
        delta[m][j] = tmp;
      }
    }
  
    std::cout << "finite difference weights of grid points alpha (in the order of alpha):" << std::endl;
    for (int i=0; i<M+1; i++){
      std::cout << "derivative order " << i << ": " << std::endl;
      for (int j=i; j<N+1; j++){
        std::cout << std::setprecision(14) << "accuracy order " << j-i+1 << ": " << delta[i][j] << std::endl;
      }
      std::cout << std::endl;
    }
  } 

  return 0;
}

