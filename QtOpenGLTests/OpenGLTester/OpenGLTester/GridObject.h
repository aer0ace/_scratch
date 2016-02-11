#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QOpenGL.h>
#include <QVector>
#include <QVector3D>
#include <ObjectBase.h>

class GridObject : public ObjectBase
{
public:
	static const int32_t kDefaultGridSize = 2;

	GridObject(int32_t gridSize = kDefaultGridSize);

	void InitVertexArrays();

	virtual void Build();

private:

	int32_t mSize;
};

#endif // GRIDOBJECT_H
