#ifndef StrintManipulation_h
#define StrintManipulation_h

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>


class StringManipulation
{
private:
protected:
public:
    static std::string DelSomething(std::string String, const char& Key)
    {
        String.erase(std::remove(String.begin(), String.end(), Key), String.end());

        return String;
    }



    static std::string GetAfter(const std::string& str, const std::string& delimiter) {
        size_t pos = str.find(delimiter);
        if (pos == std::string::npos) {
            return "";
            std::cout << "[Error]: GetAfter incorreto, caracter não encontrado\n";
        }
        return str.substr(pos + delimiter.length());
    }



    static std::string GetBefore(const std::string& str, const std::string& delimiter) {
        size_t pos = str.find(delimiter);
        if (pos == std::string::npos) {
            return "";
            std::cout << "[Error]: GetBefore incorreto, caracter não encontrado\n";
        }
        return str.substr(0, pos);
    }



    static std::vector<std::string> Split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            // Extrai a parte entre o início e o delimitador
            tokens.push_back(str.substr(start, end - start));
        
            // Move o início para logo após o delimitador
            start = end + 1;
        
            // Procura o próximo delimitador
            end = str.find(delimiter, start);
        }

        // Adiciona o último pedaço (depois do último delimitador)
        tokens.push_back(str.substr(start));

        return tokens;
    }
};

#endif
