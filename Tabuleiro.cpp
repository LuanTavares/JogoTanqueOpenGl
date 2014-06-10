#include "Tabuleiro.h"
#include <iostream>

//public:

Tabuleiro::Tabuleiro() {
    //std::cerr << "Inicio Tabuleiro::Tabuleiro()" << std::endl;
    setFixedHeight(500);
    setFixedWidth(800);
    char * nameBase ("C:/Qt/Base.obj");
    char * nameCanhao ("C:/Qt/Canhao.obj");
    _jogador1 = new Jogador(nameBase,nameCanhao);
    _jogador2 = new Jogador(nameBase,nameCanhao);

    _jogador1->moveCanhao(0.0,0.3,7.0);
    _jogador2->moveCanhao(0.0,0.3,-7.0);
    _jogador2->rotacionaCanhao(180.0);

    _jogador1->setInimigo(_jogador2);
    _jogador2->setInimigo(_jogador1);

    connect(_jogador1,SIGNAL(reiniciaPosicoes()),this,SLOT(reiniciaPosicoes()));
    connect(_jogador2,SIGNAL(reiniciaPosicoes()),this,SLOT(reiniciaPosicoes()));
    //std::cerr << "Fim Tabuleiro::Tabuleiro()" << std::endl;
}

Tabuleiro::~Tabuleiro() {
    //std::cerr << "Inicio Tabuleiro::~Tabuleiro()" << std::endl;
    delete _jogador1;
    delete _jogador2;
    //std::cerr << "Fim Tabuleiro::~Tabuleiro()" << std::endl;
}

void Tabuleiro::initializeGL() {
    //std::cerr << "Inicio Tabuleiro::InitializeGL()" << std::endl;
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);

    GLfloat posicaoLuz1 [] = {0.0,0.0,18.0,0.0};
    GLfloat posicaoLuz2 [] = {0.0,0.0,-18.0,0.0};

    glLightfv(GL_LIGHT0,GL_POSITION,posicaoLuz1);
    glLightfv(GL_LIGHT1,GL_POSITION,posicaoLuz2);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    textura = QImage(":/Imagens/Imagens/textura.jpg");

    if(textura.isNull()){
        std::cerr << "Textura não carregada" << std::endl;
    }

    textura = Tabuleiro::convertToGLFormat(textura);

    glGenTextures( 1, &texName[0] );
    glBindTexture( GL_TEXTURE_2D, texName[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, textura.width(), textura.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textura.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //std::cerr << "Fim Tabuleiro::initializeGL()" << std::endl;
}

void Tabuleiro::resizeGL( int width, int height) {
    //std::cerr << "Inicio Tabuleiro::resizeGL()" << std::endl;
    _w = width;
    _h = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1.0,1.0,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //std::cerr << "Fim Tabuleiro::resizeGL()" << std::endl;
}

void Tabuleiro::paintGL() {
    //std::cerr << "Inicio Tabuleiro::paintGL()" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(0.0,6.0,18.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);
    glViewport(0,0,_w/2,_h);
    pintaTabuleiro();
    _jogador1->pintaCanhao();
    _jogador2->pintaCanhao();
    _jogador1->pintaDisparos();
    _jogador2->pintaDisparos();

    glLoadIdentity();
    gluLookAt(0.0,6.0,-18.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);
    glViewport(_w/2,0,_w/2,_h);
    pintaTabuleiro();
    _jogador1->pintaCanhao();
    _jogador2->pintaCanhao();
    _jogador1->pintaDisparos();
    _jogador2->pintaDisparos();

    glFlush();
    //std::cerr << "Fim Tabuleiro::paintGL()" << std::endl;
}

void Tabuleiro::pintaTabuleiro() {
    //std::cerr << "Inicio Tabuleiro::pintaTabuleiro()" << std::endl;
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(0.0,0.0,0.0);
        glBegin(GL_QUADS);
            glTexCoord2f(1.0,0.0); glVertex3f(5.0,0.0,10.0);
            glTexCoord2f(1.0,1.0); glVertex3f(5.0,0.0,-10.0);
            glTexCoord2f(0.0,1.0); glVertex3f(-5.0,0.0,-10.0);
            glTexCoord2f(0.0,0.0); glVertex3f(-5.0,0.0,10.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //std::cerr << "Fim Tabuleiro::pintaTabuleiro()" << std::endl;
}

void Tabuleiro::keyPressEvent(QKeyEvent *event) {
    //std::cerr << "Inicio Tabuleiro::KeyPressEvent()" << std::endl;

    switch (event->key()) {

    /************* Controles Jogador 1 ******************/
    case Qt::Key_Right:
        _jogador1->moveCanhao(0.1,0.0,0.0);
        break;

    case Qt::Key_Left:
        _jogador1->moveCanhao(-0.1,0.0,0.0);
        break;

    case Qt::Key_Up:
        _jogador1->moveCanhao(0.0,0.0,-0.1);
        break;

    case Qt::Key_Down:
        _jogador1->moveCanhao(0.0,0.0,0.1);
        break;

    case Qt::Key_PageDown:
        //Gira canhao
        _jogador1->rotacionaCanhao(2);
        break;

    case Qt::Key_PageUp:
        //Gira canhao
        _jogador1->rotacionaCanhao(-2);
        break;

    case Qt::Key_End:
        //Atira
        _jogador1->atira();
        break;

    /************* Controles Jogador 2 ******************/

    case Qt::Key_D:
        _jogador2->moveCanhao(-0.1,0.0,0.0);
        break;

    case Qt::Key_A:
        _jogador2->moveCanhao(0.1,0.0,0.0);
        break;

    case Qt::Key_W:
        _jogador2->moveCanhao(0.0,0.0,0.1);
        break;

    case Qt::Key_S:
        _jogador2->moveCanhao(0.0,0.0,-0.1);
        break;

    case Qt::Key_Q:
        //Gira canhao
        _jogador2->rotacionaCanhao(2);
        break;

    case Qt::Key_E:
        //Gira canhao
        _jogador2->rotacionaCanhao(-2);
        break;

    case Qt::Key_Space:
        _jogador2->atira();
        break;

    default:
        std::cerr << "Tecla Inválida" << std::endl;
        break;
    }
    //std::cerr << "Fim Tabuleiro::KeyPressEvent()" << std::endl;
}

//slots:

void Tabuleiro::atualizaTela() {
    //std::cerr << "Inicio Tabuleiro::atualizaTela" << std::endl;
    updateGL();
    //std::cerr << "Fim Tabuleiro::atualizaTela" << std::endl;
}

void Tabuleiro::reiniciaPosicoes() {

    _jogador1->resetPosicao(0.0,0.0,7.0,0.0);
    _jogador2->resetPosicao(0.0,0.0,-7.0,180.0);
    emit atualizaVidasP1(_jogador1->getVidas());
    emit atualizaVidasP2(_jogador2->getVidas());

}
