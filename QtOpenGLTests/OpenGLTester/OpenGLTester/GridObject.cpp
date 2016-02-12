#include <GridObject.h>


GridObject::GridObject(int32_t gridSize)
	: ObjectBase()
	, mSize(gridSize)
{
	mData.resize(2500 * 6);
}

void GridObject::BuildVertexData()
{
	float length = 0.2f;

	float xOffset = -mSize;

	float zMin = -mSize;
	float zMax = mSize;

	const QVector3D kNormal = QVector3D(0.0f, 1.0f, 0.0f);

	while (xOffset <= mSize)
	{
		Add(QVector3D(xOffset, 0.0f, zMin), kNormal);
		Add(QVector3D(xOffset, 0.0f, zMax), kNormal);

		Add(QVector3D(zMin, 0.0f, xOffset), kNormal);
		Add(QVector3D(zMax, 0.0f, xOffset), kNormal);

		xOffset += 1.0f;
	}
}

//void GridObject::InitVertexArrays()
//{
//	ObjectBase::InitVertexArrays(GetConstData(), GetDataCount() * sizeof(GLfloat));
//}

//void GridObject::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
//{
//	QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));
//
//	add(QVector3D(x1, y1, -0.05f), n);
//	add(QVector3D(x4, y4, -0.05f), n);
//	add(QVector3D(x2, y2, -0.05f), n);
//
//	add(QVector3D(x3, y3, -0.05f), n);
//	add(QVector3D(x2, y2, -0.05f), n);
//	add(QVector3D(x4, y4, -0.05f), n);
//
//	n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));
//
//	add(QVector3D(x4, y4, 0.05f), n);
//	add(QVector3D(x1, y1, 0.05f), n);
//	add(QVector3D(x2, y2, 0.05f), n);
//
//	add(QVector3D(x2, y2, 0.05f), n);
//	add(QVector3D(x3, y3, 0.05f), n);
//	add(QVector3D(x4, y4, 0.05f), n);
//}
