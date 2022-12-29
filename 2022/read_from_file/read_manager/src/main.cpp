#include "read_manager.h"
#include "file_names.h"

#include <iostream>
#include <fstream>
#include <time.h>

const std::string Tag = "[ReadManager] ";
const std::string ErrorTag = "[Error] ";

void HelloListOutput(const WordList& words)
{
    for(const auto& Word : words)
    {
        std::cout << Word << std::endl;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        ReadManager file;

        // Read the file we have access to.
        std::cout << Tag << "Try to read '" << HelloListFileName << "' file" << std::endl;
        if (!file.Read(HelloListFileName))
        {
               std::cout << Tag << ErrorTag << "Unable to read file: '" << HelloListFileName << "'" << std::endl;
        }
        else
        {
            std::cout << Tag << "Success" << std::endl;
            HelloListOutput(file.Get());
        }
    }
    catch(std::exception& ex)
    {
        std::cout << Tag << ErrorTag << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}