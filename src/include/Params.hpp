#pragma once

#include "App.hpp"

typedef struct
{
    std::string c;
    bool option;
} PARAMS;

bool ControlOption(int argc, char *argv[]);
PARAMS Params(int argc, char *argv[]);