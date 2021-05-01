#pragma once

#include <internal/errors.h>


err_code_e signal_init(int sig, void *handler);

err_code_e signal_block();
