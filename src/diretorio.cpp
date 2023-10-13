#include "diretorio.h"

#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

bool cmp(std::pair<std::string, int>& a,
        std::pair<std::string, int>& b)
{
    return a.second < b.second;
}
 
// Function to sort the map according
// to value in a (key-value) pairs
void sort(std::map<std::string, int>& M) {
    // Declare vector of pairs
    std::vector<std::pair<std::string, int>> A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
 
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
}

std::string Diretorio::normatizar(const std::string& palavra) const {
    std::string palavraFormatada;
    int tam = palavra.size();
    int c = 0;
    /* Normatizacao de acordo com a tabela ASC. */
    while (c < tam) {
         if(palavra[c] >= 65 && palavra[c] <= 90) {
            palavraFormatada.push_back(palavra[c] + 32);
        } else if(palavra[c] >= 97 && palavra[c] <= 122) {
            palavraFormatada.push_back(palavra[c]);
        }
        c++;
    }
    return palavraFormatada;
}

Diretorio::Diretorio(std::string caminho) {
    for (const auto& entry : std::filesystem::directory_iterator(caminho)) {
        if (entry.is_regular_file()) {
            std::ifstream arquivo(entry.path());
            if (arquivo.is_open()) {
                std::string linha;
                while (getline(arquivo, linha)) {
                    auto palavra_begin = linha.begin();
                    auto palavra_end = linha.begin();
                    while (palavra_end != linha.end()) {
                        if (*palavra_end != ' ') {
                            ++palavra_end;
                        } else {
                            std::string palavra(palavra_begin, palavra_end);
                            palavras[normatizar(palavra)][entry.path().string()]++;
                            palavra_begin = ++palavra_end;
                        }
                    }
                    if (palavra_begin != linha.end()) {
                        std::string palavra(palavra_begin, linha.end());
                        palavras[normatizar(palavra)][entry.path().string()]++;
                    }
                }
                arquivo.close();
            }
        }
    }
}

std::map<std::string, int> Diretorio::buscar(const std::string& query) const {
    // Divide a query em termos distintos
    std::vector<std::string> termos;
    for (int i = 0; i < query.size(); i++) {
        if (query[i] != ' ') {
            std::string termo;
            while (query[i] != ' ' && i < query.size()) {
                termo.push_back(query[i]);
                i++;
            }
            termos.push_back(normatizar(termo));
        }
    }

    std::map<std::string, std::vector<std::string>> documentosPorTermo;
    for (const auto& termo : termos) {
        if (palavras.find(termo) != palavras.end()) {
            for (const auto& documento : palavras.at(termo)) {
                documentosPorTermo[documento.first].push_back(termo);
            }
        }
    }

    std::map<std::string, int> documentos;
    for (const auto& [documento, noDoc] : documentosPorTermo) {
        if (noDoc.size() == termos.size()) {
            int score = 0;
            for (const auto& termo : termos) {
                score += palavras.at(termo).at(documento);
            }
            documentos[documento] = score;
        }
    }

    sort(documentos);
    return documentos;
}