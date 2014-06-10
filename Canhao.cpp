#include "Canhao.h"
#include <iostream>

Canhao::Canhao(char *p_base, char *p_canhao){
    //std::cerr << "Inicio Canhao::Canhao(char *p_base, char *p_canhao)" << std::endl;
    _podeDisparar = true;

    _rotacaoBase = 0;
    _rotacaoCanhao = 0;

    _baseTanque = NULL;
    _canhaoTanque = NULL;

    _tiros.clear();

    if(!_baseTanque) {
        _baseTanque = glmReadOBJ(p_base);
        if(!_baseTanque) std::cerr << "Não foi possível carregar o arquivo .OBJ" << std::endl;
        glmUnitize(_baseTanque);
        glmFacetNormals(_baseTanque);
        glmVertexNormals(_baseTanque,180.0);
    }

    if(!_canhaoTanque) {
        _canhaoTanque = glmReadOBJ(p_canhao);
        if(!_canhaoTanque) std::cerr << "Não foi possível carregar o arquivo .OBJ" << std::endl;
        glmUnitize(_canhaoTanque);
        glmFacetNormals(_canhaoTanque);
        glmVertexNormals(_canhaoTanque,180.0);
    }

    // definir posicao inicial do canhao deste jogador
    _posicaoBase[0] = 0.0;
    _posicaoBase[1] = 0.0;
    _posicaoBase[2] = 0.0;
    _posicaoCanhao[0] = 0.0;
    _posicaoCanhao[1] = 0.2;
    _posicaoCanhao[2] = 0.0;
    //std::cerr << "Fim Canhao::Canhao(char *p_base, char *p_canhao)" << std::endl;
}

Canhao::Canhao(){
    _baseTanque = NULL;
    _canhaoTanque = NULL;
    _posicaoBase[0] = 0.0;
    _posicaoBase[1] = 0.0;
    _posicaoBase[2] = 0.0;
    _posicaoCanhao[0] = 0.0;
    _posicaoCanhao[1] = 0.2;
    _posicaoCanhao[2] = 0.0;
}

Canhao::~Canhao(){
    delete _baseTanque;
}

void Canhao::carregaOBJ(char* p_base, char* p_canhao){
    if(!_baseTanque) {
        _baseTanque = glmReadOBJ(p_base);
        if(!_baseTanque)
            std::cerr << "Não foi possível carregar o arquivo .OBJ da base do tanque" << std::endl;
        glmUnitize(_baseTanque);
        glmFacetNormals(_baseTanque);
        glmVertexNormals(_baseTanque,180.0);
    }

    if(!_canhaoTanque) {
        _canhaoTanque = glmReadOBJ(p_canhao);
        if(!_canhaoTanque)
            std::cerr << "Não foi possível carregar o arquivo .OBJ do canhao do tanque" << std::endl;
        glmUnitize(_canhaoTanque);
        glmFacetNormals(_canhaoTanque);
        glmVertexNormals(_canhaoTanque,180.0);
    }
}

float * Canhao::getPosicaoBase() {
    return _posicaoBase;
}

float * Canhao::getPosicaoCanhao() {
    return _posicaoBase;
}

void Canhao::setPosicaoBase(float x, float y, float z){
    _posicaoBase[0] += x;
    _posicaoBase[1] += y;
    _posicaoBase[2] += z;
}

void Canhao::setPosicaoCanhao(float x, float y, float z){
    _posicaoCanhao[0] += x;
    _posicaoCanhao[1] += y;
    _posicaoCanhao[2] += z;
}

void Canhao::resetPosicao(float x, float y, float z, float graus) {
    _posicaoBase[0] = x;
    _posicaoBase[1] = y;
    _posicaoBase[2] = z;
    _posicaoCanhao[0] = x;
    _posicaoCanhao[1] = 0.3;
    _posicaoCanhao[2] = z;
    _rotacaoCanhao = graus;

    _tiros.clear();
}

void Canhao::setRotacaoBase(float graus){
    _rotacaoBase = graus;
}

void Canhao::setRotacaoCanhao(float graus){
    if ((_rotacaoCanhao + graus) > 360)
        _rotacaoCanhao = _rotacaoCanhao + graus - 360;
    if ((_rotacaoCanhao + graus) < 0)
        _rotacaoCanhao = _rotacaoCanhao + graus + 360;

    _rotacaoCanhao += graus;
}

void Canhao::pinta() {
    //std::cerr << "Inicio Canhao::pinta()" << std::endl;
    glPushMatrix();
        glTranslatef(_posicaoBase[0],_posicaoBase[1],_posicaoBase[2]);
        //std::cerr << "Base" << std::endl;
        //std::cerr << " Canhao::pinta() - x: " << _posicaoBase[0] << " y: "<< _posicaoBase[1] << " z: " << _posicaoBase[2] << "." << std::endl;
        glScalef(0.8,0.8,0.8);
        glRotatef(_rotacaoBase,0.0,1.0,0.0);
        glmDraw(_baseTanque,GLM_SMOOTH);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(_posicaoCanhao[0],_posicaoCanhao[1],_posicaoCanhao[2]);
        //std::cerr << "Canhao" << std::endl;
        //std::cerr << " Canhao::pinta() - x: " << _posicaoCanhao[0] << " y: "<< _posicaoCanhao[1] << " z: " << _posicaoCanhao[2] << "." << std::endl;
        glScalef(0.8,0.8,0.8);
        glRotatef(_rotacaoCanhao,0.0,1.0,0.0);
        glmDraw(_canhaoTanque,GLM_SMOOTH);
    glPopMatrix();

    //std::cerr << "Fim Canhao::pinta()" << std::endl;
}

bool Canhao::validaMovimentoBase(float x, float y, float z) {
    //std::cerr << "Inicio Canhao::validaMovimento()" << std::endl;
    bool retorno = true;
    if(((_posicaoBase[0]+x) >= 4.7) || ((_posicaoBase[0]+x) <= -4.7)) {
        std::cerr << "Movimentação inválida no eixo X" << std::endl;
        retorno = false;
    }
    if (((_posicaoBase[2]+z) >= 9.6) || ((_posicaoBase[2]+z) <= -9.6)) {
        std::cerr << "Movimentação inválida no eixo Z" << std::endl;
        retorno = false;
    }

    return retorno;
    //std::cerr << "Fim Canhao::validaMovimento()" << std::endl;
}

void Canhao::atira() {
    //std::cerr << "Inicio Canhao::atira() " << std::endl;
    if(_podeDisparar)
        _tiros << new Disparo(_posicaoCanhao[0],_posicaoCanhao[1],_posicaoCanhao[2], _rotacaoCanhao);
    //std::cerr << _rotacaoCanhao<<" "<<_posicaoCanhao[0] << " "<<_posicaoCanhao[1] << " "<<_posicaoCanhao[2] << std::endl;
    //std::cerr << "Fim Canhao::atira() " << std::endl;
}

void Canhao::pintaDisparos(float * inimigo) {
    //std::cerr << "Inicio Canhao::pintaDisparos()" << std::endl;
    for(int i = 0; i<_tiros.size(); i++) {
        if(!_tiros[i]->detectaColisaoCanhao(inimigo))
            if(!_tiros[i]->detectaColisaoCenario())
                _tiros[i]->pintaDisparo();
            else
                _tiros.removeAt(i);
        else {
            _tiros.removeAt(i);
            emit inimigoAtingido();
        }
    }
    //std::cerr << "Fim Canhao::pintaDisparos()" << std::endl;
}

// ************** SLOTS ******************
void Canhao::permiteNovoDisparo() {
    this->_podeDisparar = true;
}

