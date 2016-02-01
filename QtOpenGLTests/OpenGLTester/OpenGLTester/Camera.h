#ifndef CAMERA_H
#define CAMERA_H

//#include <QOpenGL.h>
//#include <QVector>
#include <QVector3D>
#include <qmatrix4x4.h>

class Camera
{
public:
    Camera();
    ~Camera();

	void SetPosition(const QVector3D& pos);

	const QVector3D& GetPosition() { return mPosition; };
	const QVector3D& GetTarget() { return mTarget; };

private:
	void UpdateTransform();

	QVector3D mPosition;
	QVector3D mTarget;

	QMatrix4x4 mTransform;
};

#endif // CAMERA_H
