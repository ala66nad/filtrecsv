#pragma once
#include "App.hpp"

class ControlA
{
    private:
        std::mutex m;
        std::unique_ptr<App> app;
        std::vector<std::string> listOfCSV;

    public : 
        ControlA();
        void Control1A();
        void test(const std::string file);
        void SaveCsv(const std::string file, const char *array, const size_t length);
};