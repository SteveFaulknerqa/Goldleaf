#pragma once

#include <stdexcept>
#include <stdio.h>
#include <switch.h>
#include "debug.h"

#define ASSERT_OK(rc_out, desc) if (R_FAILED(rc_out)) { char msg[256] = {0}; snprintf(msg, 256, "%s:%u: %s.  Error code: 0x%08x\n", __func__, __LINE__, desc, rc_out); throw std::runtime_error(msg); }