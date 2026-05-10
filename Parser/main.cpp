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

        if (Args[0] != "0")
        {
            NewFile[LineThatMacroHasBeenDetected] = "";


            std::vector<std::string> UnSplited = StringManipulation::Split(NewFile[LineThatMacroHasBeenDetected + 1],' ');
            std::vector<std::string> Splited;

            NewFile[LineThatMacroHasBeenDetected] = "";

            // Ignore all splis = ""
            for(size_t loop1 = 0; loop1 < UnSplited.size(); loop1++)
            {
                if (UnSplited[loop1] != "")
                {
                    Splited.push_back(UnSplited[loop1]);
                }
            }


            NewFile[LineThatMacroHasBeenDetected + 1] = "std::cout << \"" + Splited[1] + "\" << std::endl;";
        }

        return NewFile;
    }
};

int main() {

    std::string FileName = "";
    std::cout << "Arquivo: ";
    std::cin >> FileName;


    std::cout << "Debug:\n\n\n";



    std::string nomeArquivo = FileName;
    std::vector<std::string> File;
    
    std::ifstream arquivo(nomeArquivo);

    // Verifica se o arquivo abriu corretamente
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        File.push_back(linha);
    }

    arquivo.close();





    std::vector<std::shared_ptr<CustomMacro>> CustomMacros;
    CustomMacros.push_back(std::make_shared<FirstMacro>("FirstMacro"));


    Parser MainParser(CustomMacros);

    std::vector<std::string> NewFile = MainParser.ExecMacrosToFile(File);

    std::cout << "\n\n\n";
    std::cout << "output file: \n\n\n";
    for(size_t Loop1 = 0; Loop1 < File.size(); Loop1++)
    {
        std::cout << NewFile[Loop1] << "\n";
    }

    return 0;
}
