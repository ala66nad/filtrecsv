#include "App.hpp"

int main(int argc, char *argv[])
{
    clock_t begin = clock();
    
    const auto app = std::make_unique<App>();
    app->OnExecute(argc, argv);
    
    clock_t end = clock();
    std::cout << "Construit en " << (end - begin) << " ms" << std::endl;
    return 0;
}
