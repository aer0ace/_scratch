#include "Camera.h"

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mTarget(0.0f, 0.0f, 0.0f)

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
}
