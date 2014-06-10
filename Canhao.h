#pragma once
#include "glm.h"
#include "Disparo.h"
#include <QObject>
#include <QList>
#include <iostream>

class Canhao : public QObject{

    Q_OBJECT

private:
    GLMmodel * _baseTanque;
    GLMmodel * _canhaoTanque;
    float _posicaoBase [3], _posicaoCanhao [3], _rotacaoBase, _rotacaoCanhao;
    bool _podeDisparar;
    QList <Disparo *> _tiros;

public:

    explicit Canhao(char *p_base, char *p_canhao);
    explicit Canhao();
    virtual ~Canhao();

    void carregaOBJ(char * p_base, char *p_canhao);
    void setPosicaoBase(float x, float y, float z);
    void setPosicaoCanhao(float x, float y, float z);
    void setRotacaoBase(float graus);
    void setRotacaoCanhao(float graus);
    void resetPosicao(float x, float y, float z, float graus);
    bool validaMovimentoBase(float x, float y, float z);
    void pinta();
    float * getPosicaoBase();
    float * getPosicaoCanhao();
    void atira();
    void pintaDisparos(float *inimigo);

public slots:
    void permiteNovoDisparo();

signals:
    void inimigoAtingido();
};
