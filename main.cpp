#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/freetype.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <thread>

#include "Petisco.h"
#include "GerenciaArquivo.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);
void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
void drawTransRect(Mat frame, Scalar color, double alpha, Rect region);

GerenciaArquivo arq;
Petisco pet;

string cascadeName;
int record = arq.readScore();
int countsTime = 0;
int points = 0;
int eixoX = 30, eixoY = 60;

/**
 * @brief Draws a transparent image over a frame Mat.
 * 
 * @param frame the frame where the transparent image will be drawn
 * @param transp the Mat image with transparency, read from a PNG image, with the IMREAD_UNCHANGED flag
 * @param xPos x position of the frame image where the image will start.
 * @param yPos y position of the frame image where the image will start.
 */

void drawTransparency(Mat frame, Mat transp, int xPos, int yPos) {
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}


/**
 * @brief Draws a transparent rect over a frame Mat.
 * 
 * @param frame the frame where the transparent image will be drawn
 * @param color the color of the rect
 * @param alpha transparence level. 0 is 100% transparent, 1 is opaque.
 * @param regin rect region where the should be positioned
 */
void drawTransRect(Mat frame, Scalar color, double alpha, Rect region) {
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color); 
    addWeighted(rectImg, alpha, roi, 1.0 - alpha , 0, roi); 
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip){
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255,0,0);

    if( tryflip )
        flip(img, img, 1);

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    if (scale > 1)
        resize( img, img, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();


    //cout << smallImg.rows << " " << smallImg.cols << endl; -> Checar tamanho da webcam

    cascade.detectMultiScale( smallImg, faces,
        1.3, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(40, 40) );
    t = (double)getTickCount() - t;

    // PERCORRE AS FACES ENCONTRADAS    
    for ( size_t i = 0; i < faces.size(); i++){
        Rect r = faces[i];

        Mat princesa = cv::imread("princesaIcon.png", IMREAD_UNCHANGED); // Desenha uma imagem - princesa
        try{
           drawTransparency(img, princesa, r.x + (r.width)/4 - 1, r.y + r.height/4 - 1); // Centraliza a imagem no meio do rosto da pessoa
            }catch(Exception e){} 
        
        // Colisão entre o rosto do usuário e o petisco
        if(pet.getEixoX() > cvRound(r.x) && pet.getEixoX() < cvRound((r.x + r.width-1)) && pet.getEixoY() > cvRound(r.y) && pet.getEixoY() < cvRound((r.y + r.height-1)) && pet.getPegou() == 0){
                points++;
                pet.setPegou(1);
                system("mplayer bark.mp3 &"); //som (biblioteca mplayer pelo Linux)    
                pet.move();          
        }
        
        // Exibir e salvar novo recorde
        if (points > record) {
            record = points;
            arq.saveScore(record);
            cout << "New record: " << record << endl;
        }
    }

    Mat scoreBoard = cv::imread("board2.png", IMREAD_UNCHANGED); // Desenha o bg do placar
    drawTransparency(img, scoreBoard, 375, 0);
    
    // Carregar a fonte personalizada
    const std::string fontPath = "Valoon.ttf";
    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData(fontPath, 0);

    int fontHeight = 60; // Ajusta o tamanho da letra

    // Usar a fonte personalizada para renderizar o texto com o tamanho da letra ajustado
    ft2->putText(img, "Score: " + to_string(points), Point(515, 55), fontHeight, Scalar(120, 35, 35), -1, LINE_AA, true); // fonte

    fontHeight = 30;
    ft2->putText(img, "Record: " + to_string(record), Point(415, 100), fontHeight, Scalar(120, 35, 35), -1, LINE_AA, true); // fonte
    ft2->putText(img, "Time: " + to_string(countsTime) + "s", Point(705, 100), fontHeight, Scalar(120, 35, 35), -1, LINE_AA, true); // fonte

    Mat petiscoImg = cv::imread("petisco.png", IMREAD_UNCHANGED); // // Desenha uma imagem - petisco
    drawTransparency(img, petiscoImg, pet.getEixoX(), pet.getEixoY());

    // Desenha o frame na tela
    imshow( "result", img );
}


void drawMenu(Mat &img) {
    cv::Mat bg = cv::imread("bgDia.jpg"); // bg do menu
    cv::resize(bg, img, img.size());

    const std::string fontPath = "Pixelmania.ttf";
    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData(fontPath, 0);

    int fontHeight = 80;
    ft2->putText(img, "MENU", Point(355, 100), fontHeight, Scalar(128, 0, 0), -1, LINE_AA, true);

    const std::string fontPath2 = "Valoon.ttf"; // Muda de fonte
    cv::Ptr<cv::freetype::FreeType2> ft3 = cv::freetype::createFreeType2();
    ft3->loadFontData(fontPath2, 0);

    fontHeight = 100;
    ft3->putText(img, "Record: " + std::to_string(record), Point(485, 230), fontHeight / 2, Scalar(128, 0, 0), -1, LINE_AA, true);
    ft3->putText(img, "Press 'S' to start the game", Point(280, 400), fontHeight / 2, Scalar(151, 87, 15), -1, LINE_AA, true);
    ft3->putText(img, "Press 'Q' to quit the game", Point(290, 500), fontHeight / 2, Scalar(151, 87, 15), -1, LINE_AA, true);

    imshow("result", img);
}


void drawGameOver(Mat& img, bool& restart, bool& quit) {
    cv::Mat bg = cv::imread("bg-fim.jpg"); 
    cv::resize(bg, img, img.size());

    const std::string fontPath = "Pixelmania.ttf";
    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData(fontPath, 0);

    int fontHeight = 60;
    ft2->putText(img, "GAME OVER", Point(270, 100), fontHeight, Scalar(255, 191, 0), -1, LINE_AA, true);

    const std::string fontPath2 = "Valoon.ttf";
    cv::Ptr<cv::freetype::FreeType2> ft3 = cv::freetype::createFreeType2();
    ft3->loadFontData(fontPath2, 0);

    fontHeight = 55;
    ft3->putText(img, "Score: " + to_string(points), Point(100, 270), fontHeight, Scalar(235, 216, 173), -1, LINE_AA, true);
    ft3->putText(img, "Record: " + to_string(record), Point(100, 340), fontHeight, Scalar(235, 216, 173), -1, LINE_AA, true);
    ft3->putText(img, "Press 'R' to play again", Point(260, 490), fontHeight, Scalar(222, 196, 176), -1, LINE_AA, true);
    ft3->putText(img, "Press 'Q' to quit the game", Point(210, 580), fontHeight, Scalar(222, 196, 176), -1, LINE_AA, true);

    imshow("result", img);

    char key = (char)waitKey(1);
    if (key == 'r' || key == 'R') {
        restart = true; // Definir a flag de reinício como verdadeira se a tecla "R" for pressionada
    } else if (key == 'q' || key == 'Q') {
        quit = true;
    }
}

int main(int argc, const char** argv){
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;

    cascadeName = "haarcascade_frontalface_default.xml";
    scale = 1; // usar 1, 2, 4.
    if (scale < 1){
        scale = 1;
    }

    tryflip = true;

    if (!cascade.load(cascadeName)) {
        cerr << "ERROR: Could not load classifier cascade" << endl;
    }

    if(!capture.open(0)){
        cout << "Capture from camera #0 didn't work" << endl;
    }

    if(capture.isOpened()){
        cout << "Video capturing has been started ..." << endl;

        int score = 0;
        int record = arq.readScore();
        bool operateMenu = true;
        bool startGame = false;
        bool beginCount = false;

        auto startTimer = steady_clock::now(); // Define o início do tempo de execução do jogo 
        auto endTimer = steady_clock::now(); // Define o fim do tempo de execução do jogo
        
        while(frame.empty()){
            capture >> frame;
        }

        drawMenu(frame);

        while (operateMenu) {
            char choice = (char)waitKey(10);
            if (choice == ' ') {
                break;
            }
            if (choice == 's' || choice == 'S') {
                cout << "The game is starting..." << endl; // Iniciando o jogo
                operateMenu = false;
                startGame = true;
                beginCount = true;
                countsTime = 0;
                points = 0;
            }
            if (choice == 'q' || choice == 'Q') {
                cout << "Quitting..." << endl; // Saindo do jogo
                return 0;
            }
        }
        
        if (startGame && !operateMenu) {
            while (startGame && !operateMenu) {
                for(;;){ // Loop infinito que captura os frames da câmera
                    capture >> frame;

                    if(frame.empty()){
                        break;
                    }

                    endTimer = steady_clock::now(); // Atualiza o tempo de fim com o tempo atual
                    auto exec = endTimer - startTimer; // Calcula a diferença entre os tempos de início e fim para obter a duração da execução do jogo
                    countsTime = duration_cast<seconds>(exec).count(); // Converte o tempo de duração para segundos e o armazena em countsTime
                    cout << "Timer: " << countsTime << "s" << endl;
                    
                    if (beginCount && countsTime >= 5) {
                        startGame = false;
                        operateMenu = true;
                        beginCount = false;
                        countsTime = 0;
                    }

                    if (!startGame && operateMenu) {
                        drawGameOver(frame, startGame, operateMenu);
                        countsTime = 0;
                        startTimer = steady_clock::now();
                        beginCount = true;
                        points = 0;

                        char key = (char)waitKey(0);
                        if (key == 'q' || key == 'Q') {
                            cout << "Quitting..." << endl;
                            return 0;
                        } else if (key == 'r' || key == 'R') {
                            startGame = true;
                            operateMenu = false;
                            beginCount = true;
                            countsTime = 0;
                            points = 0;
                            break; // Reinicia o loop interno
                        }
                    }

                    detectAndDraw(frame, cascade, scale, tryflip);
                    
                    char c = (char)waitKey(1);
                    if(c == 'q' || c == 'Q' || c == 27){
                        return 0;
                    }
                }
            }
        }
    }

    capture.release();
    destroyAllWindows();

    return 0;
}