#pragma once

class Petisco{
    private:
        int pegou;
        int eixoX;
        int eixoY;
    public:
        Petisco();
    
        int getEixoX();
        int getEixoY();
        int getPegou();
        void setPegou(int pegou);

        void move();
};