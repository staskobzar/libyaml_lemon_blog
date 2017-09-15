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

yaml ::= STREAM_START docs STREAM_END .
yaml ::= STREAM_START VERSION_DIRECTIVE docs STREAM_END .

docs ::= stream .
docs ::= docs doc .
docs ::= .

doc ::= DOCUMENT_START stream DOCUMENT_END .
doc ::= DOCUMENT_START stream .

stream ::= BLOCK_MAPPING_START block BLOCK_END .
stream ::= BLOCK_SEQUENCE_START block BLOCK_END .
stream ::= FLOW_SEQUENCE_START SCALAR(A) block FLOW_SEQUENCE_END . {
  printf("   === flow scalar: %s\n", A);
}
stream ::= FLOW_MAPPING_START block FLOW_MAPPING_END .

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
value(A) ::= VALUE TAG(T) SCALAR(V) . { A = V; printf("   &TAG: %s\n", T); }
value ::= VALUE ANCHOR .
value ::= VALUE ALIAS .

entry ::= BLOCK_ENTRY BLOCK_MAPPING_START block BLOCK_END .
entry ::= BLOCK_MAPPING_START block BLOCK_END .
entry(A) ::= BLOCK_ENTRY SCALAR(E) . {
  A = E;
  printf("    Entry: %s\n", E);
}
entry(A) ::= FLOW_ENTRY SCALAR(F) . {
  A = F;
  printf("    Flow Entry: %s\n", F);
}
