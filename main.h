#ifndef __MAIN_H
#define __MAIN_H

#include <yaml.h>

const char *token_type(yaml_token_type_t type);
unsigned int yaml_tokenize(yaml_token_type_t token);

#endif
