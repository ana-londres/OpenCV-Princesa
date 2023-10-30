#include "Petisco.h"
#include <cstdlib>

const int MAX_X = 1100;
const int MAX_Y = 500;

Petisco::Petisco(){
    move();
}

int Petisco::getEixoX(){
    return eixoX;
}

int Petisco::getEixoY(){
    return eixoY;
}

int Petisco::getPegou(){
    return pegou;
}

void Petisco::setPegou(int pegou){
    this->pegou = pegou;
}

void Petisco::move(){
    eixoX = rand() % (MAX_X - 100) + 100;
    eixoY = rand() % (MAX_Y - 70) + 70;
    pegou = 0;
}