#include "GerenciaArquivo.h"

void GerenciaArquivo::saveScore(int score) {
    std::ofstream arquivo("record.txt");
    if (arquivo.is_open()) {
        arquivo << score;
        arquivo.close();
    }
}

int GerenciaArquivo::readScore() {
    std::ifstream arquivo("record.txt");
    int score = 0;
    if (arquivo.is_open()) {
        arquivo >> score;
        arquivo.close();
    }
    return score;
}
