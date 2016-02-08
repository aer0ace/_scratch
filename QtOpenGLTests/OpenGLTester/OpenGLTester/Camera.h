#ifndef CAMERA_H
#define CAMERA_H

//#include <QOpenGL.h>
//#include <QVector>
#include <QVector3D>
#include <qmatrix4x4.h>
#include <ObjectUtils.h>

using namespace Utils;

// Orthonormal Basis
class Basis
{
public:
	Basis();
	void Set(const QVector3D& dirVector, const QVector3D& upVectorHint);

	void Get(QVector3D& forward, QVector3D& right, QVector3D& up);

private:
	void OrthoNormalize(const QVector3D& upVectorHint);

	QVector3D mForward;
	QVector3D mUp;
	QVector3D mRight;
};

class Camera
{
public:
    Camera();
    ~Camera();

	void SetPosition(const QVector3D& pos);
	void SetTarget(const QVector3D& target);

	const QVector3D& GetPosition() { return mPosition; };
	const QVector3D& GetTarget() { return mTarget; };
	const QVector3D& GetTiltAxis() { return mTiltAxis; }

	const QMatrix4x4& GetTransform() { return mTransform; };

	void Pan(const float& screenX, const float& screenY);
	void Tilt(float deltaAngle);
	void Orbit(float deltaAngle);
	void TiltAndOrbit(float deltaTiltAngle, float deltaOrbitAngle);
	void Zoom(float deltaDistance);

private:
	void UpdateTransform();

	QVector3D mPosition;
	QVector3D mTarget;
	QVector3D mTiltAxis;

	bool mHasTarget;

	float mCamTilt;
	float mCamOrbit;
	float mZoom;
	QMatrix4x4 mTransform;

	//PosQuat mPosQuat;
	
};

#endif // CAMERA_H
