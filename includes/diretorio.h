#ifndef DIRETORIO_H_
#define DIRETORIO_H_

#include <string>
#include <map>

class Diretorio {
    private:
        /**
         * Armazena as palavras de cada documento.
        */
        std::map<std::string, std::map<std::string, int>> palavras;

        /**
         * Normaliza uma palavra.
        */
        std::string normatizar(const std::string& palavra) const;
    
    public:
        /**
         * Construtor da classe Diretorio.
        */
        Diretorio(std::string caminho);

        /**
         * Busca um termo em todos os documentos do diretório.
        */
        std::map<std::string, int> buscar(const std::string& termo) const;
};

#endif