%include {
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "main.h"

}

%parse_failure {
  printf("ERROR: Failed to parse.\n");
}
%syntax_error {
  printf("ERROR: Syntax error.\n");
}

%token_type { const char * }

yaml ::= STREAM_START stream STREAM_END .

stream ::= BLOCK_MAPPING_START block BLOCK_END .
stream ::= BLOCK_SEQUENCE_START block BLOCK_END .

block ::= block field .
block ::= block entry .
block ::= .

field ::= key(K) VALUE stream . {
  printf("Block %s:\n", K);
}
field ::= key(K) value(V) . {
  printf("%s: %s\n", K, V);
}

key(A) ::= KEY SCALAR(K) . { A = K; }

value(A) ::= VALUE SCALAR(V) . { A = V; }
value(A) ::= VALUE BLOCK_ENTRY SCALAR(V) . { A = V; }

entry ::= BLOCK_ENTRY BLOCK_MAPPING_START block BLOCK_END .
entry(A) ::= BLOCK_ENTRY SCALAR(E) . {
  A = E;
  printf("    Entry: %s\n", E);
}

