#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "auxiliary.hh"

using namespace std;

// M: maximum derivative
// N: maximum accuracy
// x0: position at which value/derivative is approximated
// alpha: grid point position
vector<vector<vector<double>>> get_weights(const int M, const int N, const double x0, const vector<double> alpha){

  vector<vector<vector<double>>> delta(M+1, vector<vector<double>>(N+1, vector<double>(N+1, 0.0)));
  delta[0][0][0] = 1.0;
  double c1 = 1.0;
  for (int n=1; n<=N; n++){
    double c2 = 1.0;

    for (int nu=0; nu<n; nu++){
      double c3 = alpha[n] - alpha[nu];
      c2 *= c3;

      // if (n<=M) delta[n][n-1][nu] = 0.0;
      for (int m=0; m<=min(n,M); m++){
        // cout << "c3: " << c3 << endl;
        if(m==0) delta[m][n][nu] = ((alpha[n] - x0)*delta[m][n-1][nu]) / c3;
        else delta[m][n][nu] = ((alpha[n] - x0)*delta[m][n-1][nu] - m*delta[m-1][n-1][nu]) / c3;
        // cout << delta[n][nu][m] << endl;
        // cout << "writing " << n << ", " << nu << ", " << m << endl;
      }
    }
    for (int m=0; m<=min(n,M); m++){
      if (m==0) delta[m][n][n] = c1/c2 * ( - (alpha[n-1] - x0)*delta[m][n-1][n-1]);
      else delta[m][n][n] = c1/c2 * (m*delta[m-1][n-1][n-1] - (alpha[n-1] - x0)*delta[m][n-1][n-1]);
      // cout << "writing " << n << ", " << n << ", " << m << endl;
    }
    c1 = c2;
  }

  return delta;
}


int main(int ac, char **av) {

  const int M = 4; // max derivative
  const int N = 8; // will calculate all accuracies until n+1
  const double x0 = -3.5;
  vector<double> alpha({-4, -3, -2, -1, 0, 1, 2, 3, 4});
  assert(alpha.size() > N);
  vector<double> alpha_sorted(alpha);

  // alpha should be sorted ascendingly
  sort(&alpha[0], &alpha[0]+N+1);

  // but get_weights works on an alpha with increasing distance from x0
  for (double &d: alpha_sorted) d -= x0;
  sort(&alpha_sorted[0], &alpha_sorted[0]+N+1, abs_comp);
  for (double &d: alpha_sorted) d += x0;
  // cout << alpha_sorted << endl;

  vector<double> map(N+1);
  for (int i=0; i<N+1; i++){
    for (int j=0; j<N+1; j++){
      if(alpha[j] == alpha_sorted[i]) map[i] = j;
    }
  }
  // cout << map << endl;

  vector<vector<vector<double>>> delta;
  delta = get_weights(M, N, x0, alpha_sorted);

  cout << "x0: " << x0 << endl;
  cout << "alpha: " << alpha << endl << endl;

//   cout << delta << endl;

  // reorder according to ordered alpha
  for(int m=0; m<M+1; m++){
    for(int j=0; j<N+1; j++){
      vector<double> tmp(N+1);
      for (int k=0; k<N+1; k++){
        tmp[map[k]] = delta[m][j][k];
      }
      delta[m][j] = tmp;
    }
  }

  cout << "finite difference weights of grid points alpha (in the order of alpha):" << endl;
  for (int i=0; i<M+1; i++){
    cout << "derivative order: " << i << endl;
    for (int j=i; j<N+1; j++){
      cout << setprecision(12) << "accuracy order " << j-i+1 << ": " << delta[i][j] << endl;
    }
    cout << endl;
  }

  return 0;
}

