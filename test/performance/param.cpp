// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <benchmark/benchmark.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( copy_param )
NEW_MEMORY_COUNTER( new_param )
NEW_MEMORY_COUNTER( set_param_name )

static void CopyParam(benchmark::State& state){
  struct stumpless_param *param;
  const struct stumpless_param *result;

  INIT_MEMORY_COUNTER( copy_param );

  param = stumpless_new_param( "copy-param-perf", "value" );

  for(auto _ : state){
    result = stumpless_copy_param( param );
    if( !result ) {
      state.SkipWithError( "the param copy failed" );
    } else {
      stumpless_destroy_param( result );
    }
  }

  stumpless_destroy_param( param );
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, copy_param );
}

static void NewParam(benchmark::State& state){
  const struct stumpless_param *result;

  INIT_MEMORY_COUNTER( new_param );

  for(auto _ : state){
    result = stumpless_new_param( "new-param-name", "new-param-value" );
    if( !result ) {
      state.SkipWithError( "the param creation failed" );
    } else {
      stumpless_destroy_param( result );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, new_param );
}

static void SetParamName(benchmark::State& state){
  struct stumpless_param *param;
  const char *name = "new-param-name";
  const struct stumpless_param *result;

  INIT_MEMORY_COUNTER( set_param_name );

  param = stumpless_new_param( "original-name", "original-value" );

  for(auto _ : state){
    result = stumpless_set_param_name( param, name );
    if( !result ) {
      state.SkipWithError( "could not set the param name" );
    }
  }

  stumpless_destroy_param( param );
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, set_param_name );
}

BENCHMARK(CopyParam);
BENCHMARK(NewParam);
BENCHMARK(SetParamName);
