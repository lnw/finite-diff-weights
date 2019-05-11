#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


void get_weights(const int M, const int N, const double x0, const double * alpha, double delta[][16][5]){

  delta[0][0][0] = 1.0;
  double c1 = 1.0;
  for (int n=1; n<=N; n++){
    double c2 = 1.0;
    
    for (int nu=0; nu<n; nu++){
      double c3 = alpha[n] - alpha[nu];
      c2 *= c3;
    
      if (n<=M) delta[n-1][nu][n] = 0;
      for (int m=0; m<=min(n,M); m++){
        // cout << "c3: " << c3 << endl;
        if(m==0) delta[n][nu][m] = ((alpha[n] - x0)*delta[n-1][nu][m]) / c3;
        else delta[n][nu][m] = ((alpha[n] - x0)*delta[n-1][nu][m] - m*delta[n-1][nu][m-1]) / c3;
        // cout << delta[n][nu][m] << endl;
        cout << "writing " << n << ", " << nu << ", " << m << endl;
      }
    }
    for (int m=0; m<=min(n,M); m++){
      if (m==0) delta[n][n][m] = c1/c2 * ( - (alpha[n-1] - x0)*delta[n-1][n-1][m]);
      else delta[n][n][m] = c1/c2 * (m*delta[n-1][n-1][m-1] - (alpha[n-1] - x0)*delta[n-1][n-1][m]);
        cout << "writing " << n << ", " << n << ", " << m << endl;
    }
    c1 = c2;
  }
}


int main(int ac, char **av) {

  const int M = 4; // max derivative
  const int N = 8; // number of points
  const double x0 = -4.0;
  // double alpha[9] = {0,-1,1,-2,2,-3,3,-4,4};
  double alpha[9] = {-4, -3, -2, -1,0,1,2,3,4};
  double delta[2*N][2*N][M+1];

  get_weights(M, N, x0, alpha, delta);

  cout << "out" << endl;
//  cout << delta[0][0][0] << ", " << delta[0][1][0] << ", " << delta[0][2][0] << ", " << delta[0][3][0] << ", " << delta[0][4][0] << ", " << delta[0][5][0]<< ", " << delta[0][6][0] << endl;
//  cout << delta[1][0][0] << ", " << delta[1][1][0] << ", " << delta[1][2][0] << ", " << delta[1][3][0] << ", " << delta[1][4][0] << ", " << delta[1][5][0]<< ", " << delta[1][6][0] << endl;
//  cout << delta[2][1][0] << ", " << delta[2][2][0] << ", " << delta[2][3][0] << ", " << delta[2][4][0] << ", " << delta[2][5][0]<< ", " << delta[2][6][0] << endl;
//  cout << delta[3][1][0] << ", " << delta[3][2][0] << ", " << delta[3][3][0] << ", " << delta[3][4][0] << ", " << delta[3][5][0]<< ", " << delta[3][6][0] << endl;
//  cout << delta[4][1][0] << ", " << delta[4][2][0] << ", " << delta[4][3][0] << ", " << delta[4][4][0] << ", " << delta[4][5][0]<< ", " << delta[4][6][0] << endl;
//  cout << delta[5][1][0] << ", " << delta[5][2][0] << ", " << delta[5][3][0] << ", " << delta[5][4][0] << ", " << delta[5][5][0]<< ", " << delta[5][6][0] << endl;
//  cout << delta[6][1][0] << ", " << delta[6][2][0] << ", " << delta[6][3][0] << ", " << delta[6][4][0] << ", " << delta[6][5][0]<< ", " << delta[6][6][0] << endl << endl;
                                              
  cout << delta[0][0][1] << ", " <<delta[0][1][1] << ", " << delta[0][2][1] << ", " << delta[0][3][1] << ", " << delta[0][4][1] << ", " << delta[0][5][1]<< ", " << delta[0][6][1] << endl;
  cout << delta[1][0][1] << ", " <<delta[1][1][1] << ", " << delta[1][2][1] << ", " << delta[1][3][1] << ", " << delta[1][4][1] << ", " << delta[1][5][1]<< ", " << delta[1][6][1] << endl;
  cout << delta[2][0][1] << ", " <<delta[2][1][1] << ", " << delta[2][2][1] << ", " << delta[2][3][1] << ", " << delta[2][4][1] << ", " << delta[2][5][1]<< ", " << delta[2][6][1] << endl;
  cout << delta[3][1][1] << ", " << delta[3][2][1] << ", " << delta[3][3][1] << ", " << delta[3][4][1] << ", " << delta[3][5][1]<< ", " << delta[3][6][1] << endl;
  cout << delta[4][1][1] << ", " << delta[4][2][1] << ", " << delta[4][3][1] << ", " << delta[4][4][1] << ", " << delta[4][5][1]<< ", " << delta[4][6][1] << endl;
  cout << delta[5][1][1] << ", " << delta[5][2][1] << ", " << delta[5][3][1] << ", " << delta[5][4][1] << ", " << delta[5][5][1]<< ", " << delta[5][6][1] << endl;
  cout << delta[6][1][1] << ", " << delta[6][2][1] << ", " << delta[6][3][1] << ", " << delta[6][4][1] << ", " << delta[6][5][1]<< ", " << delta[6][6][1] << endl;
  cout << delta[7][1][1] << ", " << delta[7][2][1] << ", " << delta[7][3][1] << ", " << delta[7][4][1] << ", " << delta[7][5][1]<< ", " << delta[7][6][1] << endl;
  cout << delta[8][1][1] << ", " << delta[8][2][1] << ", " << delta[8][3][1] << ", " << delta[8][4][1] << ", " << delta[8][5][1]<< ", " << delta[8][6][1] << endl << endl;
                                                                                      

  double foo = 3/4;
  double bar = 3.0/4;
  cout << foo << endl;
  cout << bar << endl;


  return 0;
}

