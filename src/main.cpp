#include <iostream>
#include <string>
#include <vector>

#include "diretorio.h"

int main() {
    try {
        Diretorio diretorio("documentos");
        std::string termo;
        std::getline(std::cin, termo);
        std::map<std::string, int> documentos = diretorio.buscar(termo);
        for (const auto& documento : documentos) {
            std::cout << documento.first << ": " << documento.second << " ocorrência(s)\n";
        }
    } catch (...) {
        std::cout << "Erro desconhecido!" << std::endl;
        return 1;
    }
    return 0;
}