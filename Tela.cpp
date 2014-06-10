#include "Tela.h"

Tela::Tela(){

    _labelVidasP1 = new QLabel("Vidas Jogador 1:");
    _labelVidasP2 = new QLabel("Vidas Jogador 2:");
    _qtdVidasP1 = new QLCDNumber();
    _qtdVidasP2 = new QLCDNumber();
    _barraStatus = new QHBoxLayout();
    _principal = new QVBoxLayout();
    _jogo = new Tabuleiro();
    _fps = new QTimer();

    _qtdVidasP1->setFixedSize(50,30);
    _qtdVidasP2->setFixedSize(50,30);
    _labelVidasP1->setFixedSize(100,30);
    _labelVidasP2->setFixedSize(100,30);

    _fps->setInterval(33);

    _qtdVidasP1->display(3);
    _qtdVidasP2->display(3);

    _barraStatus->addWidget(_labelVidasP1);
    _barraStatus->addWidget(_qtdVidasP1);
    _barraStatus->addWidget(_labelVidasP2);
    _barraStatus->addWidget(_qtdVidasP2);

    _principal->addLayout(_barraStatus);
    _principal->addWidget(_jogo);

    setLayout(_principal);

    connect(_jogo,SIGNAL(atualizaVidasP1(int)),_qtdVidasP1,SLOT(display(int)));
    connect(_jogo,SIGNAL(atualizaVidasP2(int)),_qtdVidasP2,SLOT(display(int)));
    connect(_fps,SIGNAL(timeout()),_jogo,SLOT(atualizaTela()));

    _fps->start();



}

Tela::~Tela() {

}

void Tela::keyPressEvent(QKeyEvent *event) {
    //std::cerr << "Inicio Tela::KeyPressEvent()" << std::endl;

    _jogo->keyPressEvent(event);

    //std::cerr << "Fim Tela::KeyPressEvent()" << std::endl;
}
