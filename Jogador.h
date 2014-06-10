#pragma once
#include "Canhao.h"
#include <QObject>

class Jogador : public QObject{

    Q_OBJECT

private:
    Jogador * _inimigo;
    Canhao * _tanque;
    int _pontos, _vidas;

public:
    explicit Jogador();
    explicit Jogador(char* p_base, char* p_canhao);
    virtual ~Jogador();

    float * getPosicao();
    void setInimigo(Jogador * inimigo);
    void setObj(char* p_base, char* p_canhao);
    void setVidas(int p_qtdVidas);
    int getVidas();
    void zeraPontos();
    void pintaCanhao();
    void moveCanhao(float x, float y, float z);
    void rotacionaCanhao(float graus);
    void atira();
    void pintaDisparos();
    void resetPosicao(float x, float y, float z, float graus);

public slots:

    void setIncrementaPontos();

signals:

    void reiniciaPosicoes();
};
