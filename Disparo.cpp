#include "Disparo.h"
#include <iostream>
#include <math.h>

Disparo::Disparo(float xPosicao, float yPosicao, float zPosicao, float anguloRotacao) {
    //std::cerr << "Inicio Disparo::Disparo(float xPosicao, float yPosicao, float zPosicao, float anguloRotacao) " << std::endl;
    _movimento = 0.2;
    _deslocamentoX = 0;
    _deslocamentoZ = 0;

    _velocidade = new QTimer();
    _tiro = gluNewQuadric();
    if(_tiro == NULL) std::cerr << " Não foi possível alocar espaço para o tiro" << std::endl;

    _posicao[0] = xPosicao;
    _posicao[1] = yPosicao;
    _posicao[2] = zPosicao;

    connect(_velocidade,SIGNAL(timeout()),this,SLOT(moveDisparo()) );

    _rotacao = anguloRotacao; //Angulo em graus --> necessário converter em radianos para usar seno e coseno
    _rad = (_rotacao*M_PI/180);// Conversão Graus -> Radianos
    _deslocamentoX = (_movimento*sin(_rad));
    _deslocamentoZ = (_movimento*cos(_rad));
    _velocidade->start(10);

    //std::cerr << "Fim Disparo::Disparo(float xPosicao, float yPosicao, float zPosicao, float anguloRotacao) " << std::endl;
}

Disparo::~Disparo() {
    //std::cerr << "Inicio Disparo::~Disparo()" << std::endl;
    delete this;
    //std::cerr << "Fim Disparo::~Disparo()" << std::endl;
}

void Disparo::moveDisparo () {
    //std::cerr << "Inicio Disparo::moveDisparo() " << std::endl;
    _posicao[0] -= _deslocamentoX;
    _posicao[2] -= _deslocamentoZ;
    //std::cerr << "Fim Disparo::moveDisparo() " << std::endl;
}

bool Disparo::detectaColisaoCanhao(float * inimigo) {
    //std::cerr << "Inicio Disparo::detectaColisao()" << std::endl;
    boolean retorno = false;

    /**************** Detecta colisão com o Inimigo *********************/
    float * posicao = inimigo;

    //std::cerr <<"Posição Inimigo X:"<<posicao[0] << " Y:"<<posicao[1] << " Z:"<<(posicao[2])<< std::endl;
    //std::cerr <<"Posição Disparo X:"<<_posicao[0] << " Y:"<<_posicao[1] << " Z:"<<(_posicao[2])<<" Deslocamento:" << _deslocamento << std::endl;

    /********* Triangulação (Pitágoras) *********/
    // Encontra os valores de x e z do triangulo (Cateto oposto e adjacente)
    float x,z;
    x = (_posicao[0] - (posicao[0] + _deslocamentoX));
    z = (_posicao[2] - (posicao[2] + _deslocamentoZ));
    //std::cerr << "X: "<< x << " Y:" << z << std::endl;

    // Eleva ao quadrado
    float px,py;
    px = pow(x,2);
    py = pow(z,2);
    //std::cerr << "PX: "<< px << " PY:" << py << std::endl;

    // Soma o quadrado e tira a raiz para encontrar a Hipotenusa, que neste caso é a distancia entre os 2 pontos
    float spo,rso;
    spo = px + py;
    rso = sqrtf(spo);
    //std::cerr << "SPO: "<< spo << " RSO:" << rso << std::endl;

    /***********************************/

    // Se a distancia for menor que 0.7, considera colisão com o tanque inimigo
    if (rso < 0.7) {
        retorno = true;
        _velocidade->stop();
        return retorno;
    }

    /********************************************************************/

    return retorno;
    //std::cerr << "Fim Disparo::detectaColisao()" << std::endl;
}

bool Disparo::detectaColisaoCenario() {
    bool retorno = false;
    /**************** Detecta colisão com o cenário *********************/
    if(((_posicao[0]+_deslocamentoX) >= 5) || ((_posicao[0]+_deslocamentoX) <= -5)) {
        retorno = true;
        _velocidade->stop();
        return retorno;
    }
    if (((_posicao[2]+_deslocamentoZ) >= 10) || ((_posicao[2]+_deslocamentoZ) <= -10)) {
        retorno = true;
        _velocidade->stop();
        return retorno;
    }
    /********************************************************************/
    return retorno;
}

void Disparo::pintaDisparo() {
    //std::cerr << "Inicio Disparo::pintaDisparo() " << std::endl;

    glPushMatrix();
        glTranslatef(_posicao[0],_posicao[1],_posicao[2]);
        gluSphere(_tiro,0.05,5,5);
    glPopMatrix();

    //std::cerr << "Fim Disparo::fimDisparo() " << std::endl;
}


