#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include <QOpenGL.h>
#include <QVector>
#include <QVector3D>
#include <ObjectBase.h>

class LineObject : public ObjectBase
{
public:
	LineObject();
	void Update(const QVector3D& pos, const QVector3D &n);

	//int count() const { return 12; }
	//int vertexCount() const { return 2; }

	virtual void Build();

	void InitVertexArrays();

	virtual void PreDraw();

protected:
	virtual void InitVBOAttribs();
private:
	//void add(const QVector3D &v, const QVector3D &n);
	//QVector<GLfloat> mData;
	//int mCount;

	QVector3D mPos;
	QVector3D mNormal;
};


#endif // LINEOBJECT_H
