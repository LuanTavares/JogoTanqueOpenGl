#pragma once
#include <GL/glu.h>
#include <QObject>
#include <QTimer>

class Disparo : public QObject{

    Q_OBJECT

private:
    float _posicao[3];
    float _rotacao;
    float _movimento, _deslocamentoX, _deslocamentoZ, _rad;
    GLUquadric * _tiro;
    QTimer * _velocidade;

public:
    explicit Disparo(float xPosicao, float yPosicao, float zPosicao, float anguloRotacao);
    virtual ~Disparo();
    void pintaDisparo();
    bool detectaColisaoCanhao(float *inimigo);
    bool detectaColisaoCenario();

public slots:
    void moveDisparo();

};
