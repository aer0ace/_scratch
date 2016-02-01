#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QObject>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <qopenglwidget>
#include <QMatrix4x4>
#include <GridObject.h>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class ViewportWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	ViewportWidget(QWidget *parent = 0);
	~ViewportWidget();

	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

	void Cleanup();

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	void SetupVertexAttributes();

private:
	bool mCore;
	bool mTransparent;

	QMatrix4x4 mProjection;
	QMatrix4x4 mCamera;
	QPoint mLastPos;
	float mCamTilt;
	float mCamOrbit;
	QMatrix4x4 mWorld;

	QOpenGLVertexArrayObject mVAO;
	QOpenGLBuffer mVBO;

	QOpenGLShaderProgram* mShaderProgram;

	// Uniform location index in shader program
	int mLocProjectionMatrix;
	int mLocMvMatrix;
	int mLocNormalMatrix;
	int mLocLightPosition;


	GridObject mGridObject;
};

#endif // VIEWPORTWIDGET_H
