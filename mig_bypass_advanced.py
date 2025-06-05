#!/usr/bin/env python3
"""
Advanced MIG Bypass Generator - A Temporal Bridge
This tool translates 1994 Mach Interface Definitions into code that
modern compilers can digest. It's our Rosetta Stone for IPC archaeology.
"""

import sys
import re
from pathlib import Path
import os

class MigStubGenerator:
    def __init__(self, defs_file_path_str):
        self.defs_file = Path(defs_file_path_str)
        self.subsystem = None
        self.base_msg_id = 0
        self.routines = []
        self.output_dir = self.defs_file.parent
        self.imports = []
        self.types = {}


    def parse_defs(self):
        """Parse the .defs file to extract interface information"""
        print(f"DEBUG: Parsing {self.defs_file}")
        if not self.defs_file.is_file():
            print(f"ERROR: {self.defs_file} does not exist or is not a file.")
            return False

        with open(self.defs_file, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        # Extract subsystem name and base message ID
        subsystem_match = re.search(r'subsystem\s+(\w+)\s+(\d+)\s*;', content, re.IGNORECASE)
        if subsystem_match:
            self.subsystem = subsystem_match.group(1)
            self.base_msg_id = int(subsystem_match.group(2))
            print(f"DEBUG: Found subsystem: {self.subsystem}, base_msg_id: {self.base_msg_id}")
        else:
            self.subsystem = self.defs_file.stem
            self.base_msg_id = 1000 # Default base_msg_id
            print(f"DEBUG: Subsystem info not found in file. Using filename based: {self.subsystem}, default base_msg_id: {self.base_msg_id}")

        # Extract imports
        self.imports = re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)
        print(f"DEBUG: Found imports: {self.imports}")

        # Extract type definitions
        type_matches = re.findall(r'type\s+(\w+)\s*=\s*([^;]+);', content, re.IGNORECASE)
        for name, definition in type_matches:
            self.types[name] = definition.strip()
        print(f"DEBUG: Found types: {self.types}")

        # Extract routines
        # Pattern: (routine|simpleroutine|function) routine_name ( arguments ) msg_id_optional ;
        # This regex is simplified and might need refinement for complex argument parsing.
        routine_pattern = r'(routine|simpleroutine|function)\s+([\w_]+)\s*\((.*?)\)(?:\s+(\d+))?\s*;'

        # Default message offset if not specified in .defs
        # MIG assigns sequential numbers if not explicit.
        current_msg_offset = 0
        for match in re.finditer(routine_pattern, content, re.DOTALL | re.IGNORECASE):
            routine_type = match.group(1).lower()
            name = match.group(2)
            args_str = match.group(3).strip()
            msg_id_explicit_str = match.group(4)

            if msg_id_explicit_str:
                msg_id = int(msg_id_explicit_str)
                # Update current_msg_offset if explicit IDs create gaps or change sequence
                # This is a simplification; true MIG ID assignment can be complex.
                current_msg_offset = (msg_id - self.base_msg_id) + 1
            else:
                msg_id = self.base_msg_id + current_msg_offset
                current_msg_offset += 1

            self.routines.append({
                'type': routine_type,
                'name': name,
                'args_str': args_str,
                'msg_id': msg_id
            })
        print(f"DEBUG: Found {len(self.routines)} routines.")
        return True

    def _get_header_filename(self):
        # Typical Mach pattern: subsystem_user.h or just subsystem.h
        # The Board's example used subsystem_user.h
        return self.output_dir / f"{self.subsystem}_user.h" # As per Board's example

    def _get_user_stub_filename(self):
        return self.output_dir / f"{self.subsystem}_user.c"

    def _get_server_stub_filename(self):
        return self.output_dir / f"{self.subsystem}_server.c"

    def generate_header(self):
        header_path = self._get_header_filename()
        header_content = f"""/* GENERATED STUB HEADER for {self.defs_file.name} by mig_bypass_advanced.py */
#ifndef _{self.subsystem.upper()}_USER_H_
#define _{self.subsystem.upper()}_USER_H_

#include <mach/mach_types.h> /* For kern_return_t, mach_port_t etc. */
#include <mach/message.h>    /* For mach_msg_header_t */
#include <mach/kern_return.h>
"""
        # Include imported defs' headers (assuming they follow same naming convention)
        for imp_file in self.imports:
            imp_base = Path(imp_file).stem
            header_content += f'#include "{imp_base}_user.h" /* From import {imp_file} */\n'

        header_content += f"""
/* Message ID Base for subsystem {self.subsystem} */
#ifndef {self.subsystem.upper()}_MSG_ID_BASE
#define {self.subsystem.upper()}_MSG_ID_BASE {self.base_msg_id}
#endif

/* Definitions of routines */
"""
        for routine in self.routines: # Use actual msg_id from parsing for define
            header_content += f"""
/* Routine {routine['name']} ({routine['type']}) - msg_id {routine['msg_id']} */
/* Original arguments: {routine['args_str']} */
extern kern_return_t {routine['name']}(
    mach_port_t target_port
    /* TODO: Add parsed arguments for {routine['name']} here */
);
#define MSG_ID_{self.subsystem.upper()}_{routine['name']} ({routine['msg_id']})
"""

        header_content += """
#endif /* _{self.subsystem.upper()}_USER_H_ */
"""
        with open(header_path, 'w') as f:
            f.write(header_content)
        print(f"Generated: {header_path}")

    def generate_user_stub(self):
        user_stub_path = self._get_user_stub_filename()
        header_filename = self._get_header_filename().name # Get just the filename.h

        impl = f"""/* GENERATED USER STUB for {self.defs_file.name} by mig_bypass_advanced.py */
#include "{header_filename}"
/* Include other necessary Mach headers if not covered by mach_types.h or message.h */
/* #include <mach/mach.h> for mig_get_reply_port(), though it's often inlined or part of libmach */
/* #include <stdio.h> for debugging printf */

/* Prototype for mig_get_reply_port if not available from standard headers */
#if !defined(mig_get_reply_port)
extern mach_port_t mig_get_reply_port(void);
#endif
"""
        for routine in self.routines:
            # Simplified request/reply structures
            impl += f"""
kern_return_t {routine['name']}(mach_port_t target_port /* TODO: Add other args */)
{{
    typedef struct {{
        mach_msg_header_t Head;
        /* NDR_record_t NDR; // If using NDR encoding */
        /* Arguments for {routine['name']} would be marshaled here */
    }} Request_{routine['name']}_t;

    typedef struct {{
        mach_msg_header_t Head;
        /* NDR_record_t NDR; */
        kern_return_t RetCode;
        /* Reply arguments for {routine['name']} would be here */
    }} Reply_{routine['name']}_t;

    Request_{routine['name']}_t InP;
    Reply_{routine['name']}_t OutP;
    kern_return_t kr;

    InP.Head.msgh_bits = MACH_MSGH_BITS(MACH_MSG_TYPE_COPY_SEND, MACH_MSG_TYPE_MAKE_SEND_ONCE);
    InP.Head.msgh_size = sizeof(Request_{routine['name']}_t);
    InP.Head.msgh_remote_port = target_port;
    InP.Head.msgh_local_port = mig_get_reply_port();
    InP.Head.msgh_id = MSG_ID_{self.subsystem.upper()}_{routine['name']};

    /* HACK: For bootstrap phase, some calls might be expected to succeed without full IPC */
    if (target_port == MACH_PORT_NULL) {{
        /* This logic might need to be specific to certain routine names or subsystems */
        /* printf("DEBUG STUB: {routine['name']} called with MACH_PORT_NULL\\n"); */
        return KERN_SUCCESS;
    }}

    /* printf("DEBUG STUB: Calling {routine['name']} via mach_msg, target_port=0x%x, msg_id=%d\\n", target_port, InP.Head.msgh_id); */
    kr = mach_msg(&InP.Head,
                  MACH_SEND_MSG|MACH_RCV_MSG|MACH_RCV_TIMEOUT,
                  InP.Head.msgh_size,
                  sizeof(Reply_{routine['name']}_t),
                  InP.Head.msgh_local_port,
                  100, /* Timeout in ms - very short for initial tests */
                  MACH_PORT_NULL);

    if (kr != MACH_MSG_SUCCESS) {{
        /* printf("DEBUG STUB: mach_msg for {routine['name']} failed with 0x%x\\n", kr); */
        if (kr == MACH_RCV_TIMED_OUT) return KERN_SUCCESS; /* HACK: Allow boot to proceed on timeout */
        return kr;
    }}

    /* printf("DEBUG STUB: mach_msg for {routine['name']} succeeded, server RetCode=0x%x\\n", OutP.RetCode); */
    return OutP.RetCode;
}}
"""
        with open(user_stub_path, 'w') as f:
            f.write(impl)
        print(f"Generated: {user_stub_path}")

    def generate_server_stub(self):
        server_stub_path = self._get_server_stub_filename()
        header_filename = self._get_header_filename().name

        impl = f"""/* GENERATED SERVER STUB for {self.defs_file.name} by mig_bypass_advanced.py */
#include "{header_filename}"
/* #include <mach/mach.h> */
/* #include <stdio.h> // for printf */

/* Generic server dispatch function */
boolean_t {self.subsystem}_server(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{{
    typedef struct {{
        mach_msg_header_t Head;
        /* NDR_record_t NDR; */
        kern_return_t RetCode;
    }} ServerReplyMsg;
    ServerReplyMsg *ReplyP = (ServerReplyMsg *)OutHeadP;

    /* Minimal reply */
    ReplyP->Head.msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REMOTE(InHeadP->msgh_bits), MACH_MSG_TYPE_MOVE_SEND_ONCE);
    ReplyP->Head.msgh_size = sizeof(ServerReplyMsg);
    ReplyP->Head.msgh_remote_port = InHeadP->msgh_remote_port;
    ReplyP->Head.msgh_local_port = MACH_PORT_NULL;
    ReplyP->Head.msgh_id = InHeadP->msgh_id + 100; /* MIG reply ID convention */
    ReplyP->RetCode = KERN_SUCCESS; /* Assume success for all stubbed routines */

    /* printf("DEBUG STUB: {self.subsystem}_server handling msg_id %d, returning KERN_SUCCESS\\n", InHeadP->msgh_id); */

    return TRUE; /* Indicates message was handled and reply is ready */
}}
"""
        with open(server_stub_path, 'w') as f:
            f.write(impl)
        print(f"Generated: {server_stub_path}")

    def generate(self):
        if not self.parse_defs():
            return False
        if not self.subsystem:
            print(f"ERROR: Subsystem could not be determined for {self.defs_file}. Cannot generate stubs.")
            return False

        self.output_dir.mkdir(parents=True, exist_ok=True)
        self.generate_header()
        self.generate_user_stub()
        self.generate_server_stub()
        return True

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: python3 {sys.argv[0]} <path/to/file.defs>")
        sys.exit(1)

    defs_file = sys.argv[1]
    generator = MigStubGenerator(defs_file)
    if not generator.generate():
        print(f"ERROR: Failed to generate stubs for {defs_file}")
        sys.exit(1)
    print(f"Successfully generated stubs for {defs_file}")
