#ifndef OBJECTUTILS_H
#define OBJECTUTILS_H

#include <QVector3D>
#include <QQuaternion>

namespace Utils
{
	class PosQuat
	{
	public:
		QVector3D mPos;
		QQuaternion mQuat;
	};

	float clamp(float n, float lower, float upper);
}
class ObjectUtils
{
public:
	//ObjectUtils();
	//~ObjectUtils();

private:
	
};

#endif // OBJECTUTILS_H
