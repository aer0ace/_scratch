#include "ViewportWidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
<<<<<<< HEAD
#include <QPainter>
=======
#include <QMouseEvent>
>>>>>>> origin/master

static const char *vertexShaderSourceCore =
"#version 150\n"
"in vec4 vertex;\n"
"in vec3 normal;\n"
"out vec3 vert;\n"
"out vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
"   gl_Position = projMatrix * mvMatrix * vertex;\n"
"}\n";

static const char *fragmentShaderSourceCore =
"#version 150\n"
"in highp vec3 vert;\n"
"in highp vec3 vertNormal;\n"
"out highp vec4 fragColor;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";

static const char *vertexShaderSource =
"attribute vec4 vertex;\n"
"attribute vec3 normal;\n"
"varying vec3 vert;\n"
"varying vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
"   gl_Position = projMatrix * mvMatrix * vertex;\n"
"}\n";

static const char *fragmentShaderSource =
"varying highp vec3 vert;\n"
"varying highp vec3 vertNormal;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   gl_FragColor = vec4(col, 1.0);\n"
"}\n";


ViewportWidget::ViewportWidget(QWidget *parent)
	: QOpenGLWidget(parent)
	, mCamTilt(0.0f)
	, mCamOrbit(0.0f)
{
	mCore = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
	// --transparent causes the clear color to be transparent. Therefore, on systems that
	// support it, the widget will become transparent apart from the logo.
	mTransparent = QCoreApplication::arguments().contains(QStringLiteral("--transparent"));
	if (mTransparent)
		setAttribute(Qt::WA_TranslucentBackground);
}

ViewportWidget::~ViewportWidget()
{
	Cleanup();
}

QSize ViewportWidget::minimumSizeHint() const
{
	return QSize(640, 480);
}

QSize ViewportWidget::sizeHint() const
{
	return QSize(1024, 768);
}

void ViewportWidget::Cleanup()
{
	makeCurrent();

	mVBO.destroy();
	if (mShaderProgram)
	{
		delete mShaderProgram;
		mShaderProgram = nullptr;
	}

	doneCurrent();
}

void ViewportWidget::initializeGL()
{
	// From the Qt OpenGL example
	// In this example the widget's corresponding top-level window can change
	// several times during the widget's lifetime. Whenever this happens, the
	// QOpenGLWidget's associated context is destroyed and a new one is created.
	// Therefore we have to be prepared to clean up the resources on the
	// aboutToBeDestroyed() signal, instead of the destructor. The emission of
	// the signal will be followed by an invocation of initializeGL() where we
	// can recreate all resources.
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &ViewportWidget::Cleanup);

	//initializeOpenGLFunctions();
	glClearColor(0.9f, 0.9f, 0.9f, mTransparent ? 0 : 1);
	glLineWidth(1.0f);

	mShaderProgram = new QOpenGLShaderProgram;
	mShaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, mCore ? vertexShaderSourceCore : vertexShaderSource);
	mShaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, mCore ? fragmentShaderSourceCore : fragmentShaderSource);
	mShaderProgram->bindAttributeLocation("vertex", 0);
	mShaderProgram->bindAttributeLocation("normal", 1);
	mShaderProgram->link();

	mShaderProgram->bind();
	mLocProjectionMatrix = mShaderProgram->uniformLocation("projMatrix");
	mLocMvMatrix = mShaderProgram->uniformLocation("mvMatrix");
	mLocNormalMatrix = mShaderProgram->uniformLocation("normalMatrix");
	mLocLightPosition = mShaderProgram->uniformLocation("lightPos");

	// Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
	// implementations this is optional and support may not be present
	// at all. Nonetheless the below code works in all cases and makes
	// sure there is a VAO when one is needed.
	mVAO.create();
	QOpenGLVertexArrayObject::Binder vaoBinder(&mVAO);

	// Setup our vertex buffer object.
	mVBO.create();
	mVBO.bind();
	//m_vbo.allocate(mBasicShape.constData(), mBasicShape.count() * sizeof(GLfloat));
	mVBO.allocate(mGridObject.constData(), mGridObject.count() * sizeof(GLfloat));

	// Store the vertex attribute bindings for the program.
	SetupVertexAttributes();

	// Our camera never changes in this example.
	mCamera.setToIdentity();
	mCamera.translate(0, -0.5f, -1);

	//// Light position is fixed.
	mShaderProgram->setUniformValue(mLocLightPosition, QVector3D(0, 0, 70));

	mShaderProgram->release();
}

void ViewportWidget::SetupVertexAttributes()
{
	mVBO.bind();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glEnableVertexAttribArray(0);
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	mVBO.release();
}

void ViewportWidget::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.setFont(QFont("Arial", 24));
	painter.drawText(rect(), Qt::AlignCenter, "Test");
}

void ViewportWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	mWorld.setToIdentity();
	////    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	////    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	////    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);
	////m_world.rotate(mRot / 16.0f, 0, 1, 0);
	//m_world.rotate(mRot / 16.0f, 1, 0, 0);
	//mWorld.rotate(15.0f, 1, 0, 0);

	mCamera.setToIdentity();
	mCamera.translate(0, 0, -3);
	mCamera.rotate(mCamTilt, QVector3D(1.0f, 0.0f, 0.0f));
	mCamera.rotate(mCamOrbit, QVector3D(0.0f, 1.0f, 0.0f));
	
	QOpenGLVertexArrayObject::Binder vaoBinder(&mVAO);
	mShaderProgram->bind();
	mShaderProgram->setUniformValue(mLocProjectionMatrix, mProjection);
	mShaderProgram->setUniformValue(mLocMvMatrix, mCamera /** mWorld*/);
	QMatrix3x3 normalMatrix = mWorld.normalMatrix();
	mShaderProgram->setUniformValue(mLocNormalMatrix, normalMatrix);

	////glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());
	////glDrawArrays(GL_LINES, 0, m_logo.vertexCount());
	////glDrawArrays(GL_TRIANGLES, 0, mBasicShape.vertexCount());
	//glDrawArrays(GL_LINES, 0, mBasicShape.vertexCount());
	glDrawArrays(GL_LINES, 0, mGridObject.vertexCount());

	mShaderProgram->release();

	update();	// force loop
}



void ViewportWidget::resizeGL(int w, int h)
{
	mProjection.setToIdentity();
	mProjection.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void ViewportWidget::mousePressEvent(QMouseEvent *event)
{
	printf("Mouse Press\n");
	mLastPos = event->pos();
}

void ViewportWidget::mouseMoveEvent(QMouseEvent *event)
{
	float multiplier = 0.1f;

	int dx = event->x() - mLastPos.x();
	int dy = event->y() - mLastPos.y();

	mCamTilt += multiplier * dy;
	mCamOrbit += multiplier * dx;

	mLastPos = event->pos();

	printf("Mouse Move\n");
}

void ViewportWidget::mouseReleaseEvent(QMouseEvent * event)
{
	printf("Mouse Release\n");
}

