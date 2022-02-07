#include <Rcpp.h>
#include "header.h"

using namespace Rcpp;

double univariateBinomialNetworkLerouxSigmaSquaredUpdate(NumericVector randomEffects,
                                                          double a2,
                                                          double b2)
{
  
  double randomEffectsMultiplication = vectorTransposeVectorMultiplicationRcpp(randomEffects, randomEffects);
  int numberOfRandomEffects = randomEffects.size();
  
  double sigmaSquared = 1 / rgamma(1, (a2 + 0.5 * numberOfRandomEffects), 1 / (b2 + 0.5 * randomEffectsMultiplication))[0];
  
  return sigmaSquared;
  
}
