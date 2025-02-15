// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stumpless/entry.h>
#include "private/error.h"
#include "private/validate.h"
#include "private/config/locale/wrapper.h"

/**
 * Validates that a provide string is less than or equal to the maximum length
 * provided. An error is raised if the validation fails.
 *
 * @param str The string to check the length of.
 *
 * @param max_length The maximum length allowed for the string. Must not be
 * NULL.
 *
 * @param length A pointer to a variable that will be set to the computed length
 * of the string, in bytes.
 */
static
bool
validate_string_length( const char *str, size_t max_length, size_t *length ) {
  *length = strlen( str );
  if( *length > max_length ) {
    raise_argument_too_big( L10N_STRING_TOO_LONG_ERROR_MESSAGE,
                            *length,
                            L10N_STRING_LENGTH_ERROR_CODE_TYPE );
    return false;
  } else {
    return true;
  }
}

bool
validate_app_name( const char *str, size_t *length ) {
  return validate_app_name_length( str, length ) &&
         validate_printable_ascii( str, *length );
}

bool
validate_app_name_length( const char *app_name, size_t *length ) {
  return validate_string_length( app_name,
                                 STUMPLESS_MAX_APP_NAME_LENGTH,
                                 length );
}

bool
validate_element_name( const char *str, size_t *length ) {
  return validate_element_name_length( str, length ) &&
         validate_name_chars( str, *length );
}

bool
validate_element_name_length( const char *name, size_t *length ) {
  return validate_string_length( name,
                                 STUMPLESS_MAX_ELEMENT_NAME_LENGTH,
                                 length );
}

bool
validate_hostname( const char *hostname, size_t *length ) {
  return validate_hostname_length( hostname, length ) &&
         validate_printable_ascii( hostname, *length );
}

bool
validate_hostname_length( const char *hostname, size_t *length ) {
  return validate_string_length( hostname,
                                 STUMPLESS_MAX_HOSTNAME_LENGTH,
                                 length );
}

bool
validate_msgid( const char *str, size_t *length ) {
  return validate_msgid_length( str, length ) &&
         validate_printable_ascii( str, *length );
}

bool
validate_msgid_length( const char *msgid, size_t *length ) {
  return validate_string_length( msgid,
                                 STUMPLESS_MAX_MSGID_LENGTH,
                                 length );
}

bool
validate_name_chars( const char *str, size_t length ) {
  size_t i;

  for( i = 0; i < length; i++ ) {
    if( str[i] < 33 ||
        str[i] > 126 ||
        str[i] == '=' ||
        str[i] == ']' ||
        str[i] == '"' ) {
      raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "identifier" ) );
      return false;
    }
  }

  return true;
}

bool
validate_param_name( const char *str, size_t *length ) {
  return validate_param_name_length( str, length ) &&
         validate_name_chars( str, *length );
}

bool
validate_param_name_length( const char *name, size_t *length ) {
  return validate_string_length( name,
                                 STUMPLESS_MAX_PARAM_NAME_LENGTH,
                                 length );
}

bool
validate_printable_ascii( const char *str, size_t length ) {
  size_t i;

  for( i = 0; i < length; i++ ) {
    if( str[i] < 33 || str[i] > 126 ) {
      raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "printable ascii" ) );
      return false;
    }
  }

  return true;
}

bool
validate_procid( const char *procid, size_t *length ) {
  return validate_procid_length( procid, length ) &&
         validate_printable_ascii( procid, *length );
}

bool
validate_procid_length( const char *procid, size_t *length ) {
  return validate_string_length( procid,
                                 STUMPLESS_MAX_PROCID_LENGTH,
                                 length );
}
