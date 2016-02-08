#include <GridObject.h>

LineObject::LineObject()
{
	mData.resize(2 * 6);
}

void LineObject::Update(const QVector3D& pos, const QVector3D &n)
{
	mCount = 0;

	add(QVector3D(0.0f, 0.0f, 0.0f), n);
	add(pos, n);


	mPos = pos;
}

void LineObject::add(const QVector3D &v, const QVector3D &n)
{
	GLfloat *p = mData.data() + mCount;
	*p++ = v.x();
	*p++ = v.y();
	*p++ = v.z();
	*p++ = n.x();
	*p++ = n.y();
	*p++ = n.z();
	mCount += 6;
}



GridObject::GridObject(int32_t gridSize)
	: m_count(0)
	, mSize(gridSize)
{
	m_data.resize(2500 * 6);

	Build();
}

void GridObject::Build()
{
	float length = 0.2f;

	float xOffset = -mSize;

	float zMin = -mSize;
	float zMax = mSize;

	const QVector3D kNormal = QVector3D(0.0f, 1.0f, 0.0f);

	while (xOffset <= mSize)
	{
		//quad(0.0f, 0.0f, length, 0.0f, length, length, 0.0f, length);
		add(QVector3D(xOffset, 0.0f, zMin), kNormal);
		add(QVector3D(xOffset, 0.0f, zMax), kNormal);

		add(QVector3D(zMin, 0.0f, xOffset), kNormal);
		add(QVector3D(zMax, 0.0f, xOffset), kNormal);

		xOffset += 1.0f;
	}
}

void GridObject::add(const QVector3D &v, const QVector3D &n)
{
	GLfloat *p = m_data.data() + m_count;
	*p++ = v.x();
	*p++ = v.y();
	*p++ = v.z();
	*p++ = n.x();
	*p++ = n.y();
	*p++ = n.z();
	m_count += 6;
}

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
