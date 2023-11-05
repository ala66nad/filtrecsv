#include "Params.hpp"

bool ControlOption(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)    
        if (std::string(argv[i]) == "-o")
            return true;
    
    return false;
}

PARAMS Params(int argc, char *argv[])
{
    PARAMS params;
    params.c = "qcofe";
    params.option = false;
    if (argc > 1)
    {
        params.c = argv[1];
        params.option = ControlOption(argc, argv);
    }
    return params;
}