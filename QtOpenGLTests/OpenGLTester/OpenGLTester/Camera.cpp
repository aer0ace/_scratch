#include "Camera.h"
#include <ObjectUtils.h>

QVector3D kAxisForward(0.0f, 0.0f, 1.0f);
QVector3D kAxisUp(0.0f, 1.0f, 0.0f);
QVector3D kAxisRight(1.0f, 1.0f, 0.0f);

/*
	Design notes:
	Thinking, mTransform is either Matrix or Quaternion that is only derived, and not used in the reverse direction.
	Position and Target (or direction vector) is enough to determine:
		Orbit
		Tilt
		with atan2

	The Roll value will need to be stored, but worry about that later.

	When creating the orthonormal vectors,
		1. start with the orbit angle, generate orbit vector (2d)
		2. generate the perpendicular to this orbit (2d) this becomes the prelim right vector
		3. up = right X dirVec
		4. worry about the roll angle later.

	First pass, do not cash orbit and tilt. derive it from the dirVec.
	
	If mHasTarget is false, we rotate the camera about its own local transform axis, instead of around the target.

*/

Basis::Basis()
	: mForward(kAxisForward)
	, mRight(kAxisRight)
	, mUp(kAxisUp)
{

}

void Basis::Set(const QVector3D& dirVector, const QVector3D& upVectorHint)
{
	// TODO: check for zero length on both input vecs

	mForward = dirVector.normalized();

	OrthoNormalize(upVectorHint);
}

void Basis::Get(QVector3D& forward, QVector3D& right, QVector3D& up)
{
	forward = mForward;
	right = mRight;
	up = mUp;
}

void Basis::OrthoNormalize(const QVector3D& upVectorHint)
{
	mRight = QVector3D::crossProduct(mForward, upVectorHint);
	mUp = QVector3D::crossProduct(mRight, mForward);

	mRight.normalize();
	mUp.normalize();
}

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mTarget(0.0f, 0.0f, 0.0f)
	, mHasTarget(true)
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

#if 1
	mTransform.setToIdentity();
	mTransform.translate(0, 0, -mZoom);
	mTransform.rotate(mCamTilt, QVector3D(1.0f, 0.0f, 0.0f));
	mTransform.rotate(mCamOrbit, QVector3D(0.0f, 1.0f, 0.0f));
	mTransform.translate(mPosition);
#endif
}

void Camera::Pan(const float& screenX, const float& screenY)
{
	QVector3D up = kAxisUp * mTransform;
	QVector3D right = kAxisRight * mTransform;

	mPosition += screenY * up;
	mPosition += screenX * right;

	UpdateTransform();
}

void Camera::Tilt(float deltaAngle)
{
	mCamTilt += deltaAngle;

	//QVector3D dirVec = mTarget - mPosition;
	//QVector3D up(0.0f, 1.0f, 0.0f);
	//QVector3D right = QVector3D::crossProduct(dirVec, up);

	



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
