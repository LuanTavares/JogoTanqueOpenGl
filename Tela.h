#include "Tabuleiro.h"
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QKeyEvent>
#include <QTimer>

class Tela : public QWidget {

    Q_OBJECT

private:
    QTimer * _fps;
    QLabel * _labelVidasP1;
    QLabel * _labelVidasP2;
    QLCDNumber * _qtdVidasP1;
    QLCDNumber * _qtdVidasP2;
    QHBoxLayout * _barraStatus;
    QVBoxLayout * _principal;
    Tabuleiro * _jogo;

public:
    explicit Tela();
    virtual ~Tela();
    void keyPressEvent(QKeyEvent *event);

};
