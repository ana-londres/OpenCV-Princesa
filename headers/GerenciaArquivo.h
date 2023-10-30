#pragma once

#include <fstream>
#include <string>

class GerenciaArquivo {
    public:
        void saveScore(int score);
        int readScore();
};
