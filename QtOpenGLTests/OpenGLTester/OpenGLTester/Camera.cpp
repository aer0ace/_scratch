#include "Camera.h"
#include <ObjectUtils.h>
#include <QVector2D>
#include <QtMath>
#include <QTransform>

QVector3D kAxisForward(0.0f, 0.0f, 1.0f);
QVector3D kAxisUp(0.0f, 1.0f, 0.0f);
QVector3D kAxisRight(1.0f, 0.0f, 0.0f);

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
	, mTiltAxis(1.0f, 0.0f, 0.0f)
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

	//Vector3D right = QVector3D::crossProduct(upAxis, dir);
	//right.normalize();

	//QVector3D up = QVector3D::crossProduct(dir, right);
	//up.normalize();
	mTransform.setToIdentity();
	mTransform.lookAt(mPosition, mTarget, kAxisUp);

	Q_ASSERT_X(!qIsNaN(mTransform.row(3).x()), "Camera", "Bad Transform in Update");

#if 0
	mTransform.setToIdentity();
	mTransform.translate(0, 0, -mZoom);
	mTransform.rotate(mCamTilt, QVector3D(1.0f, 0.0f, 0.0f));
	mTransform.rotate(mCamOrbit, QVector3D(0.0f, 1.0f, 0.0f));
	mTransform.translate(mPosition);
#endif
}

void Camera::Pan(const float& screenX, const float& screenY)
{
	// Using mTransform was resulting in eventual NaN errors when multiplying
	// kAxisRight and kAxisUp by mTransform, which is odd, so this is an alternate
	// method for generating the basis vectors, and probably less computationally
	// intensive while being more straightforward.

	Basis basis;
	basis.Set((mTarget - mPosition), kAxisUp);
	
	QVector3D up;
	QVector3D right;
	QVector3D forward;
	basis.Get(forward, right, up);
	
	Q_ASSERT_X(!qIsNaN(right.x()) && !qIsNaN(up.x()), "Camera", "Transform is bad");

	qDebug("right: %.3f %.3f %.3f", right.x(), right.y(), right.z());
	qDebug("up: %.3f %.3f %.3f", up.x(), up.y(), up.z());

	QVector3D dirVecX = screenX * right;
	QVector3D dirVecY = screenY * up;

	QVector3D dirVec = dirVecX + dirVecY;
	
	mPosition += dirVec;
	mTarget += dirVec;
	
	qDebug("dirVec: %.3f %.3f %.3f", dirVec.x(), dirVec.y(), dirVec.z());

	
	

	UpdateTransform();
}

void Camera::Tilt(float deltaAngle)
{
	mCamTilt += deltaAngle;

	//QVector3D dirVec = mTarget - mPosition;
	//QVector3D up(0.0f, 1.0f, 0.0f);
	//QVector3D right = QVector3D::crossProduct(dirVec, up);

	QMatrix4x4 rotMat;
	rotMat.setToIdentity();
	rotMat.rotate(deltaAngle, 1.0f, 0.0f, 0.0f);

	mPosition = rotMat * mPosition;

	UpdateTransform();
}

void Camera::Orbit(float deltaAngle)
{
	mCamOrbit += deltaAngle;

	QMatrix4x4 rotMat;
	rotMat.setToIdentity();
	rotMat.rotate(deltaAngle, 0.0f, 1.0f, 0.0f);

	mPosition = rotMat * mPosition;

	UpdateTransform();
}

void Camera::TiltAndOrbit(float deltaTiltAngle, float deltaOrbitAngle)
{
	QMatrix4x4 transform;
	transform.setToIdentity();
	transform.rotate(deltaOrbitAngle, 0.0f, 1.0f, 0.0f);

	QMatrix4x4 tiltAxisTransform = mTransform;
	tiltAxisTransform.setRow(3, QVector4D(0.0f, 0.0f, 0.0f, 1.0f));

	mTiltAxis = kAxisRight * tiltAxisTransform;	// Rotates the right axis so that it serves as the axis of rotation for tilt.
	mTiltAxis.setY(0.0f);

	mTiltAxis.normalize();

	transform.rotate(deltaTiltAngle, mTiltAxis.x(), 0.0f, mTiltAxis.z());

	mPosition = mPosition * transform;

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
