#ifndef OPENGLTESTER_H
#define OPENGLTESTER_H

#include <QtWidgets/QMainWindow>
#include "ui_opengltester.h"

class OpenGLTester : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLTester(QWidget *parent = 0);
	~OpenGLTester();

private:
	Ui::OpenGLTesterClass ui;
};

#endif // OPENGLTESTER_H
