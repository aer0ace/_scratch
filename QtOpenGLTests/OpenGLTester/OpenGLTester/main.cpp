#include "opengltester.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLTester w;
	w.show();
	return a.exec();
}
