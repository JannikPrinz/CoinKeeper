#include "supervisorpresenter.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SupervisorPresenter supervisor;
	return a.exec();
}