/*
    Copyright (C) 2012 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the BSD style license.

     This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    FMILIB_License.txt file for more details.

    You should have received a copy of the FMILIB_License.txt file
    along with this program. If not, contact Modelon AB <http://www.modelon.com>.
*/

/** \file fmi2_xml_model_structure.c
*  \brief Implementation for the model structure interface.
*/
#include <string.h>
#include <stdio.h>

#include "fmi2_xml_parser.h"
#include "fmi2_xml_model_structure_impl.h"
#include "fmi2_xml_model_description_impl.h"

static const char * module = "FMI2XML";

fmi2_xml_model_structure_t* fmi2_xml_allocate_model_structure(jm_callbacks* cb) {
	fmi2_xml_model_structure_t* ms = (fmi2_xml_model_structure_t*)(cb->calloc(1, sizeof(fmi2_xml_model_structure_t)));
	if(!ms) return 0;

/*
	jm_vector_init(jm_voidp)(&ms->inputs,0,cb);
	jm_vector_init(size_t)(&ms->inputIsDerivative,0,cb);

	jm_vector_init(jm_voidp)(&ms->derivatives,0,cb);
	jm_vector_init(jm_voidp)(&ms->states,0,cb);
	
	jm_vector_init(jm_voidp)(&ms->outputs,0,cb);
	jm_vector_init(size_t)(&ms->outputIsDerivative,0,cb);
*/

	ms->isValidFlag = 1;

/*
	if(!ms->depsStatesOnInputs || !ms->depsStatesOnStates || !ms->depsOutputsOnInputs || !ms->depsOutputsOnStates) {
		fmi2_xml_free_model_structure(ms);
		return 0;
	}
*/

	return ms;
}

void fmi2_xml_free_model_structure(fmi2_xml_model_structure_t* ms) {
	jm_callbacks* cb;
	if(!ms) return;
/*	cb = ms->inputs.callbacks;*/

/*
	jm_vector_free_data(jm_voidp)(&ms->inputs);
	jm_vector_free_data(size_t)(&ms->inputIsDerivative);

	jm_vector_free_data(jm_voidp)(&ms->derivatives);
	jm_vector_free_data(jm_voidp)(&ms->states);
	
	jm_vector_free_data(jm_voidp)(&ms->outputs);
	jm_vector_free_data(size_t)(&ms->outputIsDerivative);
*/
	
/*	cb->free(ms); TODO: free this again! */
}

/*
jm_vector(jm_voidp)* fmi2_xml_get_outputs(fmi2_xml_model_structure_t* ms) {
	return &ms->outputs;
}

jm_vector(jm_voidp)* fmi2_xml_get_inputs(fmi2_xml_model_structure_t* ms){
	return &ms->inputs;
}

jm_vector(jm_voidp)* fmi2_xml_get_states(fmi2_xml_model_structure_t* ms){
	return &ms->states;
}

jm_vector(jm_voidp)* fmi2_xml_get_derivatives(fmi2_xml_model_structure_t* ms){
	return &ms->derivatives;
}
*/

fmi2_xml_dependencies_t* fmi2_xml_allocate_dependencies(jm_callbacks* cb) {
	fmi2_xml_dependencies_t* dep = (fmi2_xml_dependencies_t*)(cb->malloc(sizeof(fmi2_xml_dependencies_t)));
	if(!dep) return 0;
	jm_vector_init(size_t)(&dep->startIndex, 0, cb);
	jm_vector_push_back(size_t)(&dep->startIndex, 0);

	jm_vector_init(size_t)(&dep->dependencyIndex, 0, cb);
	jm_vector_init(char)(&dep->dependencyFactorKind, 0, cb);

	dep->isRowMajor = 1;

	return dep;
}

void fmi2_xml_zero_empty_dependencies(fmi2_xml_dependencies_t** pdep) {
	fmi2_xml_dependencies_t* dep =*pdep;
	size_t ndep = jm_vector_get_size(size_t)(&dep->dependencyIndex);
	size_t i;
	if(!dep) return;
	for(i = 0; i<ndep;i++) {
		if(jm_vector_get_item(size_t)(&dep->dependencyIndex, i)) break;
	}
	if(i == ndep) {
		fmi2_xml_free_dependencies(dep);
		*pdep = 0;
	}
}


void fmi2_xml_free_dependencies(fmi2_xml_dependencies_t* dep) {
    jm_callbacks* cb;
	if(!dep) return;
    cb = dep->startIndex.callbacks;
	jm_vector_free_data(size_t)(&dep->startIndex);

	jm_vector_free_data(size_t)(&dep->dependencyIndex);
	jm_vector_free_data(char)(&dep->dependencyFactorKind);
    cb->free(dep);
}


int fmi2_xml_check_model_structure(fmi2_xml_model_description_t* md) {
	fmi2_xml_model_structure_t* ms = md->modelStructure;
	jm_callbacks* cb = md->callbacks;

	if(!ms || !ms->isValidFlag) return 0;

	return ms->isValidFlag;
}

int fmi2_xml_handle_ModelStructure(fmi2_xml_parser_context_t *context, const char* data) {
    fmi2_xml_model_description_t* md = context->modelDescription;
    if(!data) {
		jm_log_verbose(context->callbacks, module,"Parsing XML element ModelStructure");
		/** allocate model structure */
		md->modelStructure = fmi2_xml_allocate_model_structure(md->callbacks);
		if(!md->modelStructure) {
				fmi2_xml_parse_fatal(context, module, "Could not allocate memory");
				return -1;
		}
    }
    else {
		/** make sure model structure information is consistent */
/*
		if(!fmi2_xml_check_model_structure(md)) {
			fmi2_xml_parse_fatal(context, "Model structure is not valid due to detected errors. Cannot continue.");
			return -1;
		}
		md->numberOfContinuousStates = jm_vector_get_size(jm_voidp)(&md->modelStructure->states);
*/
    }
    return 0;
}


int fmi2_xml_handle_Outputs(fmi2_xml_parser_context_t *context, const char* data) {
		/** nothing to do */
    return 0;
}
int fmi2_xml_handle_Derivatives(fmi2_xml_parser_context_t *context, const char* data) {
		/** nothing to do */
    return 0;
}

int fmi2_xml_handle_Derivative(fmi2_xml_parser_context_t *context, const char* data) {
    if(!data) {
    }
    else {
    }
    return 0;
}

int fmi2_xml_handle_Output(fmi2_xml_parser_context_t *context, const char* data) {
    if(!data) {
    }
    else {
    }
    return 0;
}
