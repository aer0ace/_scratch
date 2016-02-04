#ifndef CAMERA_H
#define CAMERA_H

//#include <QOpenGL.h>
//#include <QVector>
#include <QVector3D>
#include <qmatrix4x4.h>
#include <ObjectUtils.h>

using namespace Utils;

class Camera
{
public:
    Camera();
    ~Camera();

	void SetPosition(const QVector3D& pos);
	void SetTarget(const QVector3D& target);

	const QVector3D& GetPosition() { return mPosition; };
	const QVector3D& GetTarget() { return mTarget; };

	const QMatrix4x4& GetTransform() { return mTransform; };

	void Pan(const QVector3D& deltaVector);
	void Tilt(float deltaAngle);
	void Orbit(float deltaAngle);
	void Zoom(float deltaDistance);

private:
	void UpdateTransform();

	QVector3D mPosition;
	QVector3D mTarget;

	float mCamTilt;
	float mCamOrbit;
	float mZoom;
	QMatrix4x4 mTransform;

	PosQuat mPosQuat;
	
};

#endif // CAMERA_H
