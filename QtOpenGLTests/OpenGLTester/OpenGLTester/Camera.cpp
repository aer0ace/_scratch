#include "Camera.h"
#include <ObjectUtils.h>

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mTarget(0.0f, 0.0f, 0.0f)
	, mCamTilt(0.0f)
	, mCamOrbit(0.0f)
	, mZoom(3.0f)

{
	mTransform.setToIdentity();
}

Camera::~Camera()
{

}

void Camera::SetPosition(const QVector3D& pos)
{
	mPosition = pos;

	UpdateTransform();
}

void Camera::UpdateTransform()
{
	//QVector3D dir = mPosition - mTarget;	// reversed for left
	//dir.normalize();

	QVector3D upAxis(0.0f, 1.0f, 0.0f);

	//Vector3D right = QVector3D::crossProduct(upAxis, dir);
	//right.normalize();

	//QVector3D up = QVector3D::crossProduct(dir, right);
	//up.normalize();
	mTransform.setToIdentity();
	mTransform.lookAt(mPosition, mTarget, upAxis);


	mTransform.setToIdentity();
	mTransform.translate(0, 0, -mZoom);
	mTransform.rotate(mCamTilt, QVector3D(1.0f, 0.0f, 0.0f));
	mTransform.rotate(mCamOrbit, QVector3D(0.0f, 1.0f, 0.0f));
}

void Camera::Pan(const QVector3D& deltaVector)
{

}

void Camera::Tilt(float deltaAngle)
{
	mCamTilt += deltaAngle;

	UpdateTransform();
}

void Camera::Orbit(float deltaAngle)
{
	mCamOrbit += deltaAngle;

	UpdateTransform();
}

void Camera::Zoom(float deltaDistance)
{
	const float kMin = 0.5f;
	const float kMax = 50.0f;

	mZoom -= deltaDistance;

	mZoom = Utils::clamp(mZoom, kMin, kMax);

	UpdateTransform();
}
