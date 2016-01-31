#include <GridObject.h>

GridObject::GridObject()
	: m_count(0)
{
	m_data.resize(2500 * 6);

	Build();
}

void GridObject::Build()
{
	float length = 0.2f;

	float xOffset = -1.0f;

	float gridExtent = 3.0f;

	float zMin = -gridExtent;
	float zMax = gridExtent;

	for (int i = 0; i < 20; ++i)
	{
		//quad(0.0f, 0.0f, length, 0.0f, length, length, 0.0f, length);
		add(QVector3D(xOffset, 0.0f, zMin), QVector3D(0.0f, 1.0f, 0.0f));
		add(QVector3D(xOffset, 0.0f, zMax), QVector3D(0.0f, 1.0f, 0.0f));

		add(QVector3D(zMin, 0.0f, xOffset), QVector3D(0.0f, 1.0f, 0.0f));
		add(QVector3D(zMax, 0.0f, xOffset), QVector3D(0.0f, 1.0f, 0.0f));

		xOffset += 0.1f;
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
