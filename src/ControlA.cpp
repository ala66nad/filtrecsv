#include "ControlA.hpp"

ControlA::ControlA()
{
    const auto app = std::make_unique<App>();
    listOfCSV = app->ListOfCSV();
}

void ControlA::Control1A()
{
    std::cout << "Controle 1A ..." << std::endl;
    
    std::vector<std::thread> threads;
    for (size_t i = 0; i < listOfCSV.size(); i++)
        threads.push_back(std::thread(&ControlA::test, this, listOfCSV[i]));

    for (auto &th : threads)
        th.join();
}

void ControlA::test(const std::string file)
{
    size_t length;
    char *array;
    bool bWrite{false};
    std::ifstream f(file, std::fstream::in);
    if (f.is_open())
    {
        length = f.rdbuf()->pubseekoff(0, std::ios_base::end);
        array = new char[length];
        f.rdbuf()->pubseekoff(0, std::ios_base::beg);
        f.read(array, length);
        for (size_t i = 0; i < length; i++)
        {
            if (array[i] == 0X1A)
            {
                m.lock();
                array[i] = 32;
                std::cout << "1A find and correct" << std::endl;
                bWrite = true;
                m.unlock();
            }
        }
        f.close();
        if (bWrite)        
            SaveCsv(file, array, length);

        delete[] array;
    }
}

void ControlA::SaveCsv(const std::string file, const char *array, const size_t length)
{
    std::ofstream f(file, std::ios::binary);
    f.write(array, length);
    f.close();
}
