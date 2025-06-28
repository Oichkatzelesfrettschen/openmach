#!/bin/bash
# Emergency MIG stub generator - even simpler than the Python version
# This is our "stone tools" backup when sophisticated tools fail

DEFS_FILE="$1"
if [ -z "$DEFS_FILE" ]; then
    echo "Usage: $0 <path/to/file.defs>"
    exit 1
fi

DEFS_FILENAME=$(basename "$DEFS_FILE")
BASE_NAME=${DEFS_FILENAME%.defs}
OUTPUT_DIR=$(dirname "$DEFS_FILE")

# Ensure output directory exists
mkdir -p "$OUTPUT_DIR"

USER_C_FILE="${OUTPUT_DIR}/${BASE_NAME}_user.c"
SERVER_C_FILE="${OUTPUT_DIR}/${BASE_NAME}_server.c"
# Match python script naming for header for consistency if used by Makefiles
HEADER_FILE="${OUTPUT_DIR}/${BASE_NAME}_user.h"

echo "Emergency stubbing for $DEFS_FILENAME in $OUTPUT_DIR ..."

# Generate minimal C file that will compile
cat > "${USER_C_FILE}" << STUB_USER
/* Emergency USER stub for ${BASE_NAME} from mig_stub_emergency.sh */
#include <mach/mach_types.h> /* For kern_return_t */
#include "${BASE_NAME}_user.h"

/* Default init stub, may not be called or expected with this name */
kern_return_t ${BASE_NAME}_emergency_user_init(void) {
    return KERN_SUCCESS;
}
STUB_USER

cat > "${SERVER_C_FILE}" << STUB_SERVER
/* Emergency SERVER stub for ${BASE_NAME} from mig_stub_emergency.sh */
#include <mach/mach_types.h> /* For boolean_t */
#include "${BASE_NAME}_user.h" /* Include shared header */

/* Default server stub, may not be called or expected with this name */
boolean_t ${BASE_NAME}_emergency_server(void *InHeadP, void *OutHeadP) {
    /* Minimal reply to satisfy mach_msg if it expects a reply struct */
    mach_msg_header_t *OutH = (mach_msg_header_t *)OutHeadP;
    mach_msg_header_t *InH = (mach_msg_header_t *)InHeadP;
    if (OutH && InH) {
        OutH->msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REMOTE(InH->msgh_bits), MACH_MSG_TYPE_MOVE_SEND_ONCE);
        OutH->msgh_size = sizeof(mach_msg_header_t);
        OutH->msgh_remote_port = InH->msgh_remote_port;
        OutH->msgh_local_port = MACH_PORT_NULL;
        OutH->msgh_id = InH->msgh_id + 100;
    }
    return TRUE; /* Indicate handled to stop further processing by a real server if this is chained */
}
STUB_SERVER

echo "/* Emergency STUB HEADER for ${BASE_NAME} from mig_stub_emergency.sh */" > "${HEADER_FILE}"
echo "#ifndef _${BASE_NAME}_EMERGENCY_USER_H_" >> "${HEADER_FILE}"
echo "#define _${BASE_NAME}_EMERGENCY_USER_H_" >> "${HEADER_FILE}"
echo "" >> "${HEADER_FILE}"
echo "#include <mach/mach_types.h>" >> "${HEADER_FILE}"
echo "" >> "${HEADER_FILE}"
echo "/* Add any absolutely essential type definitions if known, e.g.: */" >> "${HEADER_FILE}"
echo "/* typedef mach_port_t ${BASE_NAME}_port_t; */" >> "${HEADER_FILE}"
echo "" >> "${HEADER_FILE}"
echo "#endif /* _${BASE_NAME}_EMERGENCY_USER_H_ */" >> "${HEADER_FILE}"

echo "Generated emergency stubs:"
ls -l "${USER_C_FILE}" "${SERVER_C_FILE}" "${HEADER_FILE}"
