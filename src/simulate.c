#ifdef SOSLIB

#include "rsbml.h"
#include <sbmlsolver/odeSolver.h>

SEXP rsbml_timeCourseArray_R(timeCourseArray_t *timeCourseArray, int numSens,
                             int numTimes)
{
  SEXP sens, result;
  int num = timeCourseArray->num_val, i, j, k;
  PROTECT(result = allocMatrix(REALSXP, num, numTimes));
  PROTECT(sens = allocMatrix(REALSXP, num*numSens, numTimes));
  for (i = 0; i < num; i++) {
    timeCourse_t *timeCourse = timeCourseArray->tc[i];
    for (j = 0; j < numTimes; j++) {
      REAL(result)[j*num+i] = TimeCourse_getValue(timeCourse, j);
      for (k = 0; k < numSens; k++)
        REAL(sens)[i*numSens+j*numSens*num+k] =
          TimeCourse_getSensitivity(timeCourse, k, j);
    }
  }
  setAttrib(result, install("sens"), sens);
  UNPROTECT(2);
  return result;
}

SEXP rsbml_SBMLResults_R(SBMLResults_t *sbmlResults) {
  SEXP rResults, rSensNames, rResult;
  int i, numSens = SBMLResults_getNumSens(sbmlResults),
    numTimes = SBMLResults_getNout(sbmlResults);
  PROTECT(rResults = allocVector(VECSXP, 4));
  rResult = rsbml_timeCourseArray_R(sbmlResults->species, numSens, numTimes);
  SET_VECTOR_ELT(rResults, 0, rResult);
  rResult = rsbml_timeCourseArray_R(sbmlResults->compartments, numSens, numTimes);
  SET_VECTOR_ELT(rResults, 1, rResult);
  rResult = rsbml_timeCourseArray_R(sbmlResults->parameters, numSens, numTimes);
  SET_VECTOR_ELT(rResults, 2, rResult);
  rResult = rsbml_timeCourseArray_R(sbmlResults->fluxes, numSens, numTimes);
  SET_VECTOR_ELT(rResults, 3, rResult);
  PROTECT(rSensNames = allocVector(STRSXP, numSens));
  for (i = 0; i < numSens; i++) {
    SET_STRING_ELT(rSensNames, i,
                   mkChar(SBMLResults_getSensParam(sbmlResults, i)));
  }
  setAttrib(rResults, install("sensNames"), rSensNames);
  UNPROTECT(2);
  return rResults;
}

SEXP rsbml_R_SBML_odeSolver(SEXP doc, SEXP times, SEXP atol, SEXP rtol,
                            SEXP timeStep, SEXP indefinite, SEXP maxStep,
                            SEXP odeMethod, SEXP maxOrder, SEXP iterMethod,
                            SEXP sensMethod, SEXP sensitivity, SEXP useJacobian,
                            SEXP haltOnEvent, SEXP haltOnSteadyState,
                            SEXP storeResults, SEXP ids, SEXP rids, SEXP params)
{
  SEXP rResult;
  cvodeSettings_t *cvode = CvodeSettings_create();
  /* configure ODE solver settings */
  if (asInteger(indefinite)) {
    CvodeSettings_setTime(cvode, asReal(timeStep), 0);
    CvodeSettings_setIndefinitely(cvode, TRUE);
  } else {
    CvodeSettings_setTimeSeries(cvode, REAL(times), LENGTH(times));
  }
  CvodeSettings_setErrors(cvode, asReal(atol), asReal(rtol), asInteger(maxStep));
  CvodeSettings_setMethod(cvode, asInteger(odeMethod), asInteger(maxOrder));
  CvodeSettings_setIterMethod(cvode, asInteger(iterMethod));
  if (asInteger(sensitivity)) {
    CvodeSettings_setSensitivity(cvode, TRUE);
    CvodeSettings_setSensMethod(cvode, asInteger(sensMethod));
  }
  CvodeSettings_setJacobian(cvode, asInteger(useJacobian));
  CvodeSettings_setHaltOnEvent(cvode, asInteger(haltOnEvent));
  CvodeSettings_setHaltOnSteadyState(cvode, asInteger(haltOnSteadyState));
  CvodeSettings_setStoreResults(cvode, asInteger(storeResults));
  /* run experiment */
  if (LENGTH(ids)) { /* setup experimental design */
    SBMLResultsArray_t *results;
    varySettings_t *vary = VarySettings_allocate(nrows(params), ncols(params));
    int i;
    for (i = 0; i < nrows(params); i++) {
      const char *rid = CHAR(STRING_ELT(rids, i));
      VarySettings_addParameter(vary, (char *)CHAR(STRING_ELT(ids, i)),
                                strlen(rid) ? (char *)rid : NULL);
    }
    for (i = 0; i < ncols(params); i++)
      VarySettings_addDesignPoint(vary, REAL(params)+i*nrows(params));
    results = SBML_odeSolverBatch(R_ExternalPtrAddr(doc), cvode, vary);
    if (!results)
      error("Simulations failed");
    PROTECT(rResult = allocVector(VECSXP, LENGTH(params)));
    for (i = 0; i < ncols(params); i++) {
      SEXP r = rsbml_SBMLResults_R(SBMLResultsArray_getResults(results, i));
      SET_VECTOR_ELT(rResult, i, r);
    }
    VarySettings_free(vary);
    UNPROTECT(1);
  } else {
    SBMLResults_t *result = SBML_odeSolver(R_ExternalPtrAddr(doc), cvode);
    if (!result)
      error("Simulation failed");
    rResult = rsbml_SBMLResults_R(result);
  }
  CvodeSettings_free(cvode);
  return rResult;
}
#endif
