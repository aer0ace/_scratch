#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <QObject>
#include <QOpenGL.h>
#include <QVector>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector3D>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	const GLfloat* GetConstData() const { return mData.constData(); }
	uint32_t GetDataCount() const { return mDataCount; }
	uint32_t GetVertexCount() const;

	void SetShader(QOpenGLShaderProgram* shader)
	{
		mShaderProgram = shader;
	}

	void InitAttribs();

	virtual void Build(bool dynamic);

	virtual void Draw();

	virtual void PreDraw();

protected:

	/*
		TODO: There's a catch-22 situation here, in that during initialization,
		we want to set up the vertex attributes to initialize the stride size,
		but we can't initialize the vbo until we know what size we want, but
		we can't know the size until we know what we're building. And we can't
		build it unless we know the stride (since the vertex data comprises 
		what is described in the vertex attributes.

		I guess we don't have to allocate the vbo before creating the vertex attribs
		(assuming, this will be the next attempt). We only need to allocate the
		vbo before knowing what the data is made up of.
		
	*/
	// Default attribs: Position, Normal
	virtual void SetupVertexAttributes(QOpenGLBuffer* vbo);
	virtual void Add(const QVector3D &v, const QVector3D &n);	// TODO: This should be moved somewhere else, like a Builder class

	void InitVertexData(const void* data, uint32_t size);

	virtual void BuildVertexData() = 0;

	virtual void InitVBOAttribs();

protected:
	QOpenGLShaderProgram* mShaderProgram;	// Eventually, this should be a pointer to a Material that has a pointer to the shader

	QOpenGLVertexArrayObject mVAO;
	QOpenGLBuffer mVBO;
	
	QVector<GLfloat> mData;	// Vertex data
	uint32_t mDataCount;			// Number of values (i.e. floats, indices, etc)
	uint32_t mValueStride;		// Number of values to bypass to the next vertex
};

#endif // OBJECTBASE_H
