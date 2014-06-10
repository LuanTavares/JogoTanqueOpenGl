#include <QApplication>
#include "Tela.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Tela * gl_widget;
    gl_widget = new Tela();
    gl_widget->show();

    return app.exec();
}
