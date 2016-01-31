#include "opengltester.h"

OpenGLTester::OpenGLTester(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mViewport = new ViewportWidget();

	setCentralWidget(mViewport);
}

OpenGLTester::~OpenGLTester()
{
}
