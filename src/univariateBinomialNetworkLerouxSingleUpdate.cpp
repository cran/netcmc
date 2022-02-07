#include <Rcpp.h>
#include "header.h"

using namespace Rcpp;

List univariateBinomialNetworkLerouxSingleUpdate(NumericMatrix standardizedX,
                                                  NumericVector trials,
                                                   NumericVector y,
                                                   NumericMatrix squareSpatialNeighbourhoodMatrix,
                                                   NumericMatrix spatialAssignment,
                                                   NumericMatrix W,
                                                   const int numberOfSpatialAreas,
                                                   NumericMatrix squareSpatialNeighbourhoodMatrixInTripletForm,
                                                   NumericMatrix spatialAssignmentMatrixInTripletForm,
                                                   NumericMatrix WInTripletForm,
                                                   NumericVector beta,
                                                   NumericVector spatialRandomEffects,
                                                   NumericVector uRandomEffects,
                                                   double spatialTauSquared,
                                                   double spatialRho,
                                                   double sigmaSquaredU,
                                                   double covarianceBetaPrior,
                                                   const int numberOfBetaBlocks,
                                                   const int maxBetaBlockSize,
                                                   NumericVector betaTuningParameter,
                                                   NumericVector betaAcceptanceRate,
                                                   NumericVector numberOfAcceptedBetaDraws,
                                                   NumericVector numberOfAllAcceptedBetaDraws,
                                                   NumericVector spatialRandomEffectsTuningParameters,
                                                   NumericVector spatialRandomEffectsAcceptanceRate,
                                                   NumericVector numberOfAcceptedSpatialRandomEffectsDraws,
                                                   NumericVector numberOfAllAcceptedSpatialRandomEffectsDraws,
                                                   NumericVector uRandomEffectsTuningParameters,
                                                   NumericVector uRandomEffectsAcceptanceRate,
                                                   NumericVector numberOfAcceptedUREDraws,
                                                   NumericVector numberOfAllAcceptedUREDraws,
                                                   double spatialRhoTuningParameters,
                                                   double spatialRhoAcceptanceRate,
                                                   int numberOfAcceptedSpatialRhoDraws,
                                                   int numberOfAllAcceptedSpatialRhoDraws,
                                                   NumericMatrix QSpatialMatrixComponent1,
                                                   NumericVector QSpatialMatrixComponent1EigenValues,
                                                   double a1,
                                                   double b1,
                                                   double a2,
                                                   double b2,
                                                   int currentNumberOfIterations,
                                                   bool betaFixed,
                                                   bool spatialRandomEffectsFixed,
                                                   bool uRandomEffectsFixed,
                                                   bool spatialTauSquaredFixed,
                                                   bool spatialRhoFixed,
                                                   bool sigmaSquaredUFixed,
                                                   NumericVector trueBetaValues,
                                                   NumericVector trueSpatialRandomEffectsValues,
                                                   NumericVector trueURandomEffectsValues,
                                                   double trueSpatialTauSquaredValues,
                                                   double trueSpatialRhoValues,
                                                   double trueSigmaSquaredUValues,
                                                   bool centerSpatialRandomEffects,
                                                   bool centerURandomEffects)
  
{
  
  int numberOfRowsInX = standardizedX.rows();
  int numberOfColumnsInX = standardizedX.cols();
  int numberOfRowsInSquareSpatialNeighbourhoodMatrix = squareSpatialNeighbourhoodMatrixInTripletForm.rows();
  int numberOfRowsInSpatialAssignmentMatrixTripletForm = spatialAssignmentMatrixInTripletForm.rows();
  int numberOfRowsInWTripletForm = WInTripletForm.rows();
  
  if(betaFixed){
    
    beta = trueBetaValues;
    
  } else {
    
    List output = univariateBinomialNetworkLerouxBetaUpdate(standardizedX,
                                                            trials,
                                                             y,
                                                             numberOfRowsInX,
                                                             numberOfColumnsInX,
                                                             spatialAssignmentMatrixInTripletForm,
                                                             WInTripletForm,
                                                             numberOfRowsInSpatialAssignmentMatrixTripletForm,
                                                             numberOfRowsInWTripletForm,
                                                             beta,
                                                             spatialRandomEffects,
                                                             uRandomEffects,
                                                             covarianceBetaPrior,
                                                             numberOfBetaBlocks,
                                                             maxBetaBlockSize,
                                                             betaTuningParameter,
                                                             betaAcceptanceRate,
                                                             numberOfAcceptedBetaDraws,
                                                             numberOfAllAcceptedBetaDraws,
                                                             currentNumberOfIterations);
    
    beta = output[0];
    betaTuningParameter = output[1];
    betaAcceptanceRate = output[2];
    numberOfAcceptedBetaDraws = output[3];
    numberOfAllAcceptedBetaDraws = output[4];
    
  }
  
  if(spatialRandomEffectsFixed){
    
    spatialRandomEffects = trueSpatialRandomEffectsValues;
    
  } else {
    
    List output = univariateBinomialNetworkLerouxSpatialRandomEffectsUpdate(standardizedX,
                                                                             spatialAssignment,
                                                                             squareSpatialNeighbourhoodMatrix,
                                                                             trials,
                                                                             y,
                                                                             numberOfRowsInX,
                                                                             numberOfColumnsInX,
                                                                             numberOfSpatialAreas,
                                                                             squareSpatialNeighbourhoodMatrixInTripletForm,
                                                                             WInTripletForm,
                                                                             numberOfRowsInSquareSpatialNeighbourhoodMatrix,
                                                                             numberOfRowsInWTripletForm,
                                                                             beta,
                                                                             spatialRandomEffects,
                                                                             uRandomEffects,
                                                                             spatialTauSquared,
                                                                             spatialRho,
                                                                             spatialRandomEffectsTuningParameters,
                                                                             spatialRandomEffectsAcceptanceRate,
                                                                             numberOfAcceptedSpatialRandomEffectsDraws,
                                                                             numberOfAllAcceptedSpatialRandomEffectsDraws,
                                                                             currentNumberOfIterations,
                                                                             centerSpatialRandomEffects);
    
    spatialRandomEffects = output[0];
    spatialRandomEffectsTuningParameters = output[1];
    spatialRandomEffectsAcceptanceRate = output[2];
    numberOfAcceptedSpatialRandomEffectsDraws = output[3];
    numberOfAllAcceptedSpatialRandomEffectsDraws = output[4];
    
  }
  
  if(uRandomEffectsFixed){
    
    uRandomEffects = trueURandomEffectsValues;
    
  } else {
    
    List output = univariateBinomialNetworkLerouxURandomEffectsUpdate(standardizedX,
                                                                       W,
                                                                       trials,
                                                                       y,
                                                                       numberOfRowsInX,
                                                                       numberOfColumnsInX,
                                                                       spatialAssignmentMatrixInTripletForm,
                                                                       WInTripletForm,
                                                                       numberOfRowsInSpatialAssignmentMatrixTripletForm,
                                                                       numberOfRowsInWTripletForm,
                                                                       beta,
                                                                       spatialRandomEffects,
                                                                       uRandomEffects,
                                                                       sigmaSquaredU,
                                                                       uRandomEffectsTuningParameters,
                                                                       uRandomEffectsAcceptanceRate,
                                                                       numberOfAcceptedUREDraws,
                                                                       numberOfAllAcceptedUREDraws,
                                                                       currentNumberOfIterations, 
                                                                       centerURandomEffects);
    
    uRandomEffects = output[0];
    uRandomEffectsTuningParameters = output[1];
    uRandomEffectsAcceptanceRate = output[2];
    numberOfAcceptedUREDraws = output[3];
    numberOfAllAcceptedUREDraws = output[4];
    
    
  }
  
  if(spatialTauSquaredFixed){
    
    spatialTauSquared = trueSpatialTauSquaredValues;
    
  } else {
    
    double output = univariateBinomialNetworkLerouxTauSquaredUpdate(squareSpatialNeighbourhoodMatrix,
                                                                     spatialRandomEffects,
                                                                     spatialTauSquared,
                                                                     spatialRho,
                                                                     a1,
                                                                     b1,
                                                                     QSpatialMatrixComponent1);
    
    spatialTauSquared = output;
    
  }
  
  if(spatialRhoFixed){
    
    spatialRho = trueSpatialRhoValues;
    
  } else {
    
    List output = univariateBinomialNetworkLerouxRhoUpdate(squareSpatialNeighbourhoodMatrix,
                                                            spatialRandomEffects,
                                                            spatialTauSquared,
                                                            spatialRho,
                                                            spatialRhoTuningParameters,
                                                            spatialRhoAcceptanceRate,
                                                            numberOfAcceptedSpatialRhoDraws,
                                                            numberOfAllAcceptedSpatialRhoDraws,
                                                            QSpatialMatrixComponent1,
                                                            QSpatialMatrixComponent1EigenValues,
                                                            currentNumberOfIterations);
    
    spatialRho = output[0];
    spatialRhoTuningParameters = output[1];
    spatialRhoAcceptanceRate = output[2];
    numberOfAcceptedSpatialRhoDraws = output[3];
    numberOfAllAcceptedSpatialRhoDraws = output[4];
    
  }
  
  
  if(sigmaSquaredUFixed){
    
    sigmaSquaredU = trueSigmaSquaredUValues;
    
  } else {
    
    sigmaSquaredU = univariateBinomialNetworkLerouxSigmaSquaredUpdate(uRandomEffects,
                                                                       a2,
                                                                       b2);
  }
  
  List fittedValuesAndLikelihood = getUnivariateBinomialNetworkLerouxFittedValuesAndLikelihoodForDICEveryIteration(standardizedX,
                                                                                                                   trials,
                                                                                                                    y,
                                                                                                                    spatialAssignment,
                                                                                                                    W,
                                                                                                                    beta,
                                                                                                                    spatialRandomEffects,
                                                                                                                    uRandomEffects);
  
  NumericVector fittedValues = fittedValuesAndLikelihood[0];
  NumericVector logLikelihoods = fittedValuesAndLikelihood[1];
  
  
  
  List output(24);
  
  output[0] = beta;
  output[1] = betaTuningParameter;
  output[2] = betaAcceptanceRate;
  output[3] = numberOfAcceptedBetaDraws;
  output[4] = numberOfAllAcceptedBetaDraws;
  
  output[5] = spatialRandomEffects;
  output[6] = spatialRandomEffectsTuningParameters;
  output[7] = spatialRandomEffectsAcceptanceRate;
  output[8] = numberOfAcceptedSpatialRandomEffectsDraws;
  output[9] = numberOfAllAcceptedSpatialRandomEffectsDraws;
  
  output[10] = uRandomEffects;
  output[11] = uRandomEffectsTuningParameters;
  output[12] = uRandomEffectsAcceptanceRate;
  output[13] = numberOfAcceptedUREDraws;
  output[14] = numberOfAllAcceptedUREDraws;
  
  output[15] = spatialTauSquared;
  
  output[16] = spatialRho;
  output[17] = spatialRhoTuningParameters;
  output[18] = spatialRhoAcceptanceRate;
  output[19] = numberOfAcceptedSpatialRhoDraws;
  output[20] = numberOfAllAcceptedSpatialRhoDraws;
  
  output[21] = sigmaSquaredU;
  
  output[22] = fittedValues;
  output[23] = logLikelihoods;
  
  return output;
  
}
