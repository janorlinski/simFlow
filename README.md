# simFlow
Simple ROOT macros for extracting anisotropic flow from transport model calculations.

First, obtain a tree with your calculation result. See 'makeLambdaTree.C' for an example of such macro for JAM2/RQMDv. Then, 'getFlowFromTree.C' can be used to extract flow coefficients.
In reality, it is better to execute 'runFlowAnalysis.C' which extracts the flow coefficients and then runs the plotting macro ('makePlots.C').
Please note, that the flow codes come from a later version analyzing PHSD. 
