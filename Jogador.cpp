#include "Jogador.h"
#include <iostream>

Jogador::Jogador() {
    _tanque = new Canhao();
    _vidas = 3;
    _pontos = 0;
    connect(_tanque,SIGNAL(inimigoAtingido()),this,SLOT(setIncrementaPontos()));
}

Jogador::Jogador(char* p_base, char* p_canhao) {
    _tanque = new Canhao(p_base,p_canhao);
    _pontos = 0;
    _vidas = 3;
    connect(_tanque,SIGNAL(inimigoAtingido()),this,SLOT(setIncrementaPontos()));
}

Jogador::~Jogador() {
    delete _tanque;
}

void Jogador::setInimigo(Jogador *inimigo) {
    this->_inimigo = inimigo;
}

void Jogador::setObj(char* p_base, char *p_canhao) {
    _tanque->carregaOBJ(p_base,p_canhao);
}

void Jogador::setVidas(int p_qtdVidas) {
    _vidas = p_qtdVidas;
}

int Jogador::getVidas() {
    return _vidas;
}

void Jogador::zeraPontos() {
    _pontos = 0;
}

void Jogador::pintaCanhao() {
    //std::cerr << "Inicio Jogador::pintaCanhao()" << std::endl;
    _tanque->pinta();
    //std::cerr << "Fim Jogador::pintaCanhao()" << std::endl;
}

void Jogador::moveCanhao(float x, float y, float z) {
    //std::cerr << "Inicio Jogador::moveCanhao()" << std::endl;

    if(_tanque->validaMovimentoBase(x,y,z)){
        _tanque->setPosicaoBase(x,y,z);
        _tanque->setPosicaoCanhao(x,y,z);
    }

    //std::cerr << "Fim Jogador::moveCanhao()" << std::endl;
}

void Jogador::rotacionaCanhao(float graus) {
    _tanque->setRotacaoCanhao(graus);
}

void Jogador::atira() {
    //std::cerr << "Inicio Jogador::atira() " << std::endl;
    _tanque->atira();
    //std::cerr << "Fim Jogador::atira() " << std::endl;
}

void Jogador::pintaDisparos() {
    _tanque->pintaDisparos(_inimigo->getPosicao());
}

float * Jogador::getPosicao() {
    return _tanque->getPosicaoBase();
}

// slots:

void Jogador::setIncrementaPontos(){
    //std::cerr << "Inicio Slot setIncrementaPontos()" << std::endl;
    _pontos++;
    _inimigo->setVidas(( _inimigo->getVidas() - 1));
    emit reiniciaPosicoes();
    //std::cerr << "Fim Slot setIncrementaPontos()" << std::endl;
}

void Jogador::resetPosicao(float x, float y, float z, float graus) {
    _tanque->resetPosicao(x,y,z,graus);
}






