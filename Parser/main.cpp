#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <fstream>

#include "StringManipulation.h"
#include "Parser.h"


class FirstMacro : public CustomMacro
{
public:
    FirstMacro(const std::string& Name) : CustomMacro(Name) {}

    std::vector<std::string> WhenDetected(const std::vector<std::string>& Args, size_t LineThatMacroHasBeenDetected, std::vector<std::string> File) override
    {
        std::vector<std::string> NewFile = File;

        // Error message
        std::cout << "[Error], custom macro: " << GetMacroName() << " non implemented\n";

        return File;
    }
};

int main()
{
    Parser MainParser();

    return 0;
}