#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QOpenGL.h>
#include <QVector>
#include <QVector3D>

class GridObject
{
public:
	static const int32_t kDefaultGridSize = 2;

	GridObject(int32_t gridSize = kDefaultGridSize);
	const GLfloat *constData() const { return m_data.constData(); }
	int count() const { return m_count; }
	int vertexCount() const { return m_count / 6; }

protected:
	virtual void Build();

private:
	void add(const QVector3D &v, const QVector3D &n);

	QVector<GLfloat> m_data;
	int m_count;

	int32_t mSize;
};

#endif // GRIDOBJECT_H
