// Copyright (c) 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cassert>
#include <cstring>

#include "spirv_validator_options.h"

bool spvParseUniversalLimitsOptions(const char* s, spv_validator_limit* type) {
  auto match = [s](const char* b) {
    return s && (0 == strncmp(s, b, strlen(b)));
  };
  if (match("--max-struct-members")) {
    *type = spv_validator_limit_max_struct_members;
  } else if (match("--max-struct_depth")) {
    *type = spv_validator_limit_max_struct_depth;
  } else if (match("--max-local-variables")) {
    *type = spv_validator_limit_max_local_variables;
  } else if (match("--max-global-variables")) {
    *type = spv_validator_limit_max_global_variables;
  } else if (match("--max-switch-branches")) {
    *type = spv_validator_limit_max_global_variables;
  } else if (match("--max-function-args")) {
    *type = spv_validator_limit_max_function_args;
  } else if (match("--max-control-flow-nesting-depth")) {
    *type = spv_validator_limit_max_control_flow_nesting_depth;
  } else if (match("--max-access-chain-indexes")) {
    *type = spv_validator_limit_max_access_chain_indexes;
  } else {
    // The command line option for this validator limit has not been added.
    // Therefore we return false.
    return false;
  }

  return true;
}

spv_validator_options spvValidatorOptionsCreate() {
  return new spv_validator_options_t;
}

void spvValidatorOptionsDestroy(spv_validator_options options) {
  delete options;
}

void spvValidatorOptionsSetUniversalLimit(spv_validator_options options,
                                          spv_validator_limit limit_type,
                                          uint32_t limit) {
  assert(options && "Validator options object may not be Null");
  switch(limit_type) {
#define LIMIT(TYPE, FIELD)                    \
    case TYPE:                                \
      options->universal_limits_.FIELD = limit; \
      break;
  LIMIT(spv_validator_limit_max_struct_members, max_struct_members)
  LIMIT(spv_validator_limit_max_struct_depth, max_struct_depth)
  LIMIT(spv_validator_limit_max_local_variables, max_local_variables)
  LIMIT(spv_validator_limit_max_global_variables, max_global_variables)
  LIMIT(spv_validator_limit_max_switch_branches, max_switch_branches)
  LIMIT(spv_validator_limit_max_function_args, max_function_args)
  LIMIT(spv_validator_limit_max_control_flow_nesting_depth,
        max_control_flow_nesting_depth)
  LIMIT(spv_validator_limit_max_access_chain_indexes, max_access_chain_indexes)
#undef LIMIT
  }
}