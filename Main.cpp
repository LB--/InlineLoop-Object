// ============================================================================
//
// This file contains the actions, conditions and expressions your object uses
// 
// ============================================================================

#include "Common.h"

// ============================================================================
//
// CONDITIONS
// 
// ============================================================================

CONDITION(
	/* ID */			0,
	/* Name */			"Loop %0 %1 times (Max %2)",
	/* Flags */			EVFLAGS_ALWAYS,
	/* Params */		(3,PARAM_STRING,"Loop Name",PARAM_NUMBER,"Run this event x times",PARAM_NUMBER,"Max Loop Iterations (only set this on the first event per Loop Name)")
) {
	string LoopName = string((char *)Param(TYPE_STRING));
	unsigned long LoopTimes = Param(TYPE_INT);
	unsigned long LoopMaxRT = Param(TYPE_INT);
	if(rdPtr->Run == "")
	{
		rdPtr->Run = LoopName;
		for(rdPtr->Iterations = 0; rdPtr->Iterations < LoopMaxRT; rdPtr->Iterations++)
		{
			rdPtr->rRd->GenerateEvent(0);
		}
		rdPtr->Iterations = LoopMaxRT;
		rdPtr->Run = "";
	}
	return(rdPtr->Run == LoopName && rdPtr->Iterations < LoopTimes);
}

// ============================================================================
//
// ACTIONS
// 
// ============================================================================

ACTION(
	/* ID */			0,
	/* Name */			"Set Loop Index to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Index (0-based)")
) {
	rdPtr->Iterations = Param(TYPE_INT);
}

// ============================================================================
//
// EXPRESSIONS
// 
// ============================================================================

EXPRESSION(
	/* ID */			0,
	/* Name */			"Loop Index(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(rdPtr->Iterations);
}