# Finite difference weights for arbitrary grids

C++ implementation of the algorithm described in

Fornberg, Bengt., 1988. Generation of finite difference formulas on arbitrarily spaced grids. Mathematics of computation, 51(184), pp.699-706.

The grid points can be requested in arbitrary order.  They will internally be
reordered optimally for the original algorithm, but the output is given in the
order of ascending points.

Weights at some orders of accuracy can be computed but are arbitrary (in the
sense that a different set of weights with equal quality could be chosen) or
have higher accuracy than claimed.  This is the case in any subgrid where one
would need to arbitrarily choose one grid point over another which has the same
distance from x0 (eg odd orders of accuracy in evenly spaced grids where x0
coincides with a grid point).  These accuracies are also omitted from the
tables in the original article.  These problems can be seen in the example
below in the first derivative/order 1 and the second derivative/order 1.  Note,
that these weights are in no way wrong.



## example weights for the Gauss-Lobatto grid with seven points in the intervall [-1;1]

```
x0: 0
alpha: {-1,-0.830224,-0.468849,0,0.468849,0.830224,1}

finite difference weights of grid points alpha (in the order of alpha):
derivative order 0: 
accuracy order 1: {0,0,0,1,0,0,0}
accuracy order 2: {0,0,0,1,0,0,0}
accuracy order 3: {0,0,0,1,-0,0,0}
accuracy order 4: {0,-0,0,1,-0,0,0}
accuracy order 5: {0,-0,0,1,-0,0,0}
accuracy order 6: {0,-0,0,1,-0,0,0}
accuracy order 7: {0,-0,0,1,-0,0,-0}

derivative order 1: 
accuracy order 1: {0,0,-2.13288380801,2.13288380801,0,0,0}
accuracy order 2: {0,0,-1.06644190401,0,1.06644190401,0,0}
accuracy order 3: {0,0.563999468879,-2.45004579956,1.20449435927,0.681551971406,0,0}
accuracy order 4: {0,0.281999734439,-1.56579888548,0,1.56579888548,-0.281999734439,0}
accuracy order 5: {-0.625000000003,1.66100957826,-2.94793434757,1,1.06600413361,-0.154079364286,0}
accuracy order 6: {-0.312500000002,0.907544471271,-2.00696924059,0,2.00696924059,-0.907544471271,0.312500000002}

derivative order 2: 
accuracy order 1: {0,0,4.54919333848,-9.09838667695,4.54919333848,0,0}
accuracy order 2: {0,-0,4.54919333848,-9.09838667695,4.54919333848,0,0}
accuracy order 3: {0,-0.679334178897,6.67933417889,-12,6.67933417889,-0.679334178897,0}
accuracy order 4: {-0,-0.679334178897,6.67933417889,-12,6.67933417889,-0.679334178897,0}
accuracy order 5: {0.625000000003,-2.18626439287,8.56126439286,-14,8.56126439286,-2.18626439287,0.625000000003}

derivative order 3: 
accuracy order 1: {0,-15.3944557604,37.7656897484,-32.8768662926,10.5056323046,0,0}
accuracy order 2: {0,-7.69722788019,13.6300287219,4.27922358622e-15,-13.6300287219,7.69722788019,0}
accuracy order 3: {22.5000000001,-57.3415822575,63.3869053571,-36,4.36258234561,3.09209455466,0}
accuracy order 4: {11.25,-30.2168384061,29.5121615057,7.1054273576e-15,-29.5121615057,30.2168384061,-11.25}

derivative order 4: 
accuracy order 1: {0,37.0850702548,-116.285070255,158.4,-116.285070255,37.0850702548,0}
accuracy order 2: {9.48410375888e-15,37.0850702548,-116.285070255,158.4,-116.285070255,37.0850702548,0}
accuracy order 3: {-45.0000000002,145.584045661,-251.78404566,302.399999999,-251.78404566,145.584045661,-45.0000000002}
```

