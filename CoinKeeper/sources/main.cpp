#include "Presenter/supervisorpresenter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Presenter::SupervisorPresenter supervisor;
    return a.exec();
}
