#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <filesystem>
#include <thread>
#include <mutex>
#include <iterator>

#include "Params.hpp"


class App
{
    private:
        std::ofstream _ofs;
        size_t _i{0}, _fileIndex{1};
        std::mutex m;

    public:
        int OnExecute(int argc, char *argv[]);
        std::vector<std::string> ListOfCSV();
        std::string To_lower(std::string s);
        bool Contains(std::string_view s, std::string c);
        void FileRead(std::string file, std::string c);
        void openCSV();
        void closeCSV();
        void RecupCSVTemp(std::string c);
};

