#include <stdio.h>
#include <yaml.h>

#include "main.h"
#include "parser.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void* Parse(void*, int, const char*);
void* ParseFree(void*, void(*freeProc)(void*));

int main(int argc, const char *argv[])
{
  FILE *file;
  yaml_parser_t parser;
  yaml_token_t  token;
  int space = 0;
  void *scanner = ParseAlloc (malloc);
  char *val;

  if (argc < 2) {
    printf("Usage: %s file.yml\n", argv[0]);
    return 1;
  }

  if (yaml_parser_initialize(&parser) == 0) {
    printf("ERROR: Failed to initialize yaml parser\n");
    return 2;
  }

  file = fopen(argv[1], "rb");
  if (file == NULL) {
    printf("ERROR: Failed to open file %s\n", argv[1]);
    return 3;
  }

  yaml_parser_set_input_file (&parser, file);

  // scanning
  do {
    yaml_token_delete(&token);
    yaml_parser_scan(&parser, &token);
    if(token.type == YAML_NO_TOKEN) break;

    if (token.type == YAML_BLOCK_END_TOKEN ||
        token.type == YAML_FLOW_SEQUENCE_END_TOKEN ||
        token.type == YAML_FLOW_MAPPING_END_TOKEN) space >= 4 ? space -= 4 : 0;

    printf("%*s%s(%d)\n", space, "", token_type( token.type ), token.type);

    if (token.type == YAML_BLOCK_MAPPING_START_TOKEN ||
        token.type == YAML_BLOCK_SEQUENCE_START_TOKEN ||
        token.type == YAML_FLOW_SEQUENCE_START_TOKEN ||
        token.type == YAML_FLOW_MAPPING_START_TOKEN) space += 4;

    if ( token.type == YAML_SCALAR_TOKEN ) {
      val = (char *)strndup((char *)token.data.scalar.value, token.data.scalar.length);
    } else if ( token.type == YAML_TAG_TOKEN ) {
      val = (char *)strdup((char *)token.data.tag.suffix);
    } else { val = NULL; }
    Parse(scanner, yaml_tokenize(token.type), val);

  } while(token.type != YAML_STREAM_END_TOKEN);

/*
YAML_STREAM_START_TOKEN(1)
YAML_BLOCK_MAPPING_START_TOKEN(8)
    YAML_KEY_TOKEN(16)
    YAML_SCALAR_TOKEN(21)
    YAML_VALUE_TOKEN(17)
    YAML_SCALAR_TOKEN(21)
YAML_BLOCK_END_TOKEN(9)
YAML_STREAM_END_TOKEN(2)
*/
/*
    Parse(scanner, STREAM_START, NULL);
      Parse(scanner, BLOCK_MAPPING_START, NULL);

        Parse(scanner, KEY, NULL);
        Parse(scanner, SCALAR, NULL);
        Parse(scanner, VALUE, NULL);
        Parse(scanner, SCALAR, NULL);
      Parse(scanner, BLOCK_END, NULL);
    Parse(scanner, STREAM_END, NULL);
*/

  yaml_token_delete(&token);
  Parse (scanner, 0, 0);

  ParseFree (scanner, free);
  yaml_parser_delete(&parser);
  fclose(file);
  return 0;
}
