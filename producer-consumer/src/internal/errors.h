#pragma once


typedef enum
{
    ERR_NONE     = 0,
    ERR_MEMORY   = -1,
    ERR_PTRNULL  = -2,
    ERR_INTERNAL = -3,
    ERR_CMDLINE  = -4
} err_code_e;
