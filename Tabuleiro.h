#pragma once
#include <GL/glew.h>
#include <QGLWidget>
#include "Jogador.h"
#include <QKeyEvent>
#include <QMouseEvent>

class Tabuleiro : public QGLWidget {
    Q_OBJECT

private:
    Jogador * _jogador1, * _jogador2;
    QImage textura;
    GLuint texName[1];
    int _w,_h;

public:

    explicit Tabuleiro();
    virtual ~Tabuleiro();
    void initializeGL();
    void resizeGL( int width, int height);
    void paintGL();
    void pintaTabuleiro();
    void keyPressEvent(QKeyEvent * event);

public slots:
    void atualizaTela();
    void reiniciaPosicoes();

signals:
    int atualizaVidasP1(int vidas);
    int atualizaVidasP2(int Vidas);
};


