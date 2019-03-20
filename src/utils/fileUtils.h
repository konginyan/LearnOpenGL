#include <string>
#include <fstream>
#include <streambuf>

namespace ace
{
    namespace utils
    {
        std::string readFile(char* filename)
        {
            std::ifstream t(filename);
            std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
            return str;
        }
    }
}