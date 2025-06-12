/* Minimal stub for write.c to allow compilation */
#include <stdio.h>
/* Attempt to include headers that might declare types used here */
#include "global.h"
#include "type.h" /* For ipc_type_t */
#include "routine.h" /* For routine_t */
#include "write.h"  /* If write.h exists and declares these */

/* Ensure boolean_t is defined, typically from global.h -> system headers */
/* If not, provide a fallback for the stub */
#ifndef boolean_t
typedef int boolean_t;
#define TRUE 1
#define FALSE 0
#endif

/* If routine_t or ipc_type_t are not fully defined through includes, provide minimal typedefs for stub */
#ifndef MIG_ROUTINE_T_DECLARED
#define MIG_ROUTINE_T_DECLARED
struct routine; typedef struct routine routine_t;
#endif
#ifndef MIG_IPC_TYPE_T_DECLARED
#define MIG_IPC_TYPE_T_DECLARED
struct ipc_type; typedef struct ipc_type ipc_type_t;
#endif


void WriteHeader(FILE *file, routine_t *rt) { /* Stub */ }
void WriteUser(FILE *file, routine_t *rt) { /* Stub */ }
void WriteServer(FILE *file, routine_t *rt) { /* Stub */ }
void WriteInternal(FILE *file, routine_t *rt) { /* Stub */ }
void WriteTrailer(FILE *file, routine_t *rt) { /* Stub */ }
boolean_t WriteTypeDecl(FILE *file, ipc_type_t *it) { return TRUE; /* Stub */ }
boolean_t WriteUserIndividual(FILE *file, routine_t *rt) { return TRUE; /* Stub */ }
boolean_t WriteServerIndividual(FILE *file, routine_t *rt) { return TRUE; /* Stub */ }
