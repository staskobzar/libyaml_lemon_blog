#include <yaml.h>
#include "parser.h"
#include "main.h"

const char *token_type_str[] = {
    "YAML_NO_TOKEN",

    /** A STREAM-START token. */
    "YAML_STREAM_START_TOKEN",
    /** A STREAM-END token. */
    "YAML_STREAM_END_TOKEN",

    /** A VERSION-DIRECTIVE token. */
    "YAML_VERSION_DIRECTIVE_TOKEN",
    /** A TAG-DIRECTIVE token. */
    "YAML_TAG_DIRECTIVE_TOKEN",
    /** A DOCUMENT-START token. */
    "YAML_DOCUMENT_START_TOKEN",
    /** A DOCUMENT-END token. */
    "YAML_DOCUMENT_END_TOKEN",

    /** A BLOCK-SEQUENCE-START token. */
    "YAML_BLOCK_SEQUENCE_START_TOKEN",
    /** A BLOCK-SEQUENCE-END token. */
    "YAML_BLOCK_MAPPING_START_TOKEN",
    /** A BLOCK-END token. */
    "YAML_BLOCK_END_TOKEN",

    /** A FLOW-SEQUENCE-START token. */
    "YAML_FLOW_SEQUENCE_START_TOKEN",
    /** A FLOW-SEQUENCE-END token. */
    "YAML_FLOW_SEQUENCE_END_TOKEN",
    /** A FLOW-MAPPING-START token. */
    "YAML_FLOW_MAPPING_START_TOKEN",
    /** A FLOW-MAPPING-END token. */
    "YAML_FLOW_MAPPING_END_TOKEN",

    /** A BLOCK-ENTRY token. */
    "YAML_BLOCK_ENTRY_TOKEN",
    /** A FLOW-ENTRY token. */
    "YAML_FLOW_ENTRY_TOKEN",
    /** A KEY token. */
    "YAML_KEY_TOKEN",
    /** A VALUE token. */
    "YAML_VALUE_TOKEN",

    /** An ALIAS token. */
    "YAML_ALIAS_TOKEN",
    /** An ANCHOR token. */
    "YAML_ANCHOR_TOKEN",
    /** A TAG token. */
    "YAML_TAG_TOKEN",
    /** A SCALAR token. */
    "YAML_SCALAR_TOKEN"
};

const char *token_type(yaml_token_type_t type)
{
  return token_type_str[type];
}

unsigned int yaml_tokenize(yaml_token_type_t token)
{
  switch(token) {
    case YAML_NO_TOKEN                   :  return 0;
    case YAML_STREAM_START_TOKEN         :  return STREAM_START;
    case YAML_STREAM_END_TOKEN           :  return STREAM_END;

    case YAML_BLOCK_MAPPING_START_TOKEN  :  return BLOCK_MAPPING_START;
    case YAML_BLOCK_END_TOKEN            :  return BLOCK_END;

    case YAML_SCALAR_TOKEN               :  return SCALAR;
    case YAML_KEY_TOKEN                  :  return KEY;
    case YAML_VALUE_TOKEN                :  return VALUE;

    case YAML_BLOCK_SEQUENCE_START_TOKEN :  return BLOCK_SEQUENCE_START;
    case YAML_BLOCK_ENTRY_TOKEN          :  return BLOCK_ENTRY;

    case YAML_ANCHOR_TOKEN               :  return ANCHOR;
    case YAML_ALIAS_TOKEN                :  return ALIAS;
    /*
    case YAML_VERSION_DIRECTIVE_TOKEN    :  return VERSION_DIRECTIVE;
    case YAML_TAG_DIRECTIVE_TOKEN        :  return TAG_DIRECTIVE;
    case YAML_DOCUMENT_START_TOKEN       :  return DOCUMENT_START;
    case YAML_DOCUMENT_END_TOKEN         :  return DOCUMENT_END;
    case YAML_FLOW_SEQUENCE_START_TOKEN  :  return FLOW_SEQUENCE_START;
    case YAML_FLOW_SEQUENCE_END_TOKEN    :  return FLOW_SEQUENCE_END;
    case YAML_FLOW_MAPPING_START_TOKEN   :  return FLOW_MAPPING_START;
    case YAML_FLOW_MAPPING_END_TOKEN     :  return FLOW_MAPPING_END;
    case YAML_FLOW_ENTRY_TOKEN           :  return FLOW_ENTRY;
    case YAML_TAG_TOKEN                  :  return TAG;
    */
    default: return 0;
  }
}

