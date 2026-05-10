#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <vector>

#include "StringManipulation.h"



class CustomMacro
{
private:
    std::string MacroName = "";
protected:
public:
    CustomMacro(const std::string MacroName)
    {
        this->MacroName = MacroName;
    }

    const std::string& GetMacroName()
    {
        return MacroName;
    }

    virtual std::vector<std::string> WhenDetected(const std::vector<std::string>& Args, size_t LineThatMacroHasBeenDetected, std::vector<std::string> File)
    {
        std::vector<std::string> NewFile = File;

        // Error message
        std::cout << "[Error], custom macro: " << GetMacroName() << " non implemented\n";

        return NewFile;
    }
};






class Parser
{
private:
    std::vector<std::shared_ptr<CustomMacro>> CustomMacros;
protected:
public:
    Parser(std::vector<std::shared_ptr<CustomMacro>>& CustomMacros)
    {
        this->CustomMacros = CustomMacros;
    }

    std::vector<std::string> ExecMacrosToFile(const std::vector<std::string> File)
    {

        std::vector<std::string> NewFile = File;

        bool Continue = true;

        while(Continue == true)
        {
            // If any macro has been detected, continue sould be true
            Continue = false;

            // Execute every line
            for(size_t loop1 = 0; loop1 < NewFile.size(); loop1++)
            {
                std::cout << "Searching line: ";

                // Search for the macro
                for(size_t loop2 = 0; loop2 < CustomMacros.size(); loop2++)
                {

                    
                    // Pega a linha, limpa todos os espaços
                    std::string CurrentLine = StringManipulation::DelSomething(NewFile[loop1],' ');
    
                    // Pega todos os caracteres atraz de '('
                    std::string MacroName = StringManipulation::GetBefore(CurrentLine,"(");
    
                    // Pega todos os argumentos da macro
                    std::vector<std::string> MacroArgs = StringManipulation::Split(StringManipulation::DelSomething(StringManipulation::DelSomething(StringManipulation::DelSomething(StringManipulation::GetAfter(CurrentLine,"("),' '),')'),','),';');
    
    
                    // Procura a macro por nome
                    size_t IndexOfCurrentMacro = -1;
                    for (size_t loop1 = 0; loop1 < CustomMacros.size(); loop1++)
                    {
                        if (CustomMacros[loop1]->GetMacroName() == MacroName)
                        {
                            Continue = true;

                            std::cout << "Macro detected: ";
                            IndexOfCurrentMacro = loop1;
                            break;
                        } 
                    }
    
                    if (IndexOfCurrentMacro == -1)
                    {
                        std::cout << "Jumping line, no custom macros found\n";
                    }
                    else
                    {
                        Continue = true;

                        std::cout << "Macro found: " << CustomMacros[IndexOfCurrentMacro]->GetMacroName() << "\n";
                        NewFile = CustomMacros[IndexOfCurrentMacro]->WhenDetected(MacroArgs,loop1,File);
                    }
                }
            }
        }

        return NewFile;
    }
};

#endif
