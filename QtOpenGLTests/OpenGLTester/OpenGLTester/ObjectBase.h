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

	void InitVertexArrays(const void* data, uint32_t size);

	
	virtual void Build() = 0;

	virtual void Draw();

	virtual void PreDraw();

protected:
	// Default attribs: Position, Normal
	virtual void SetupVertexAttributes(QOpenGLBuffer* vbo);
	virtual void Add(const QVector3D &v, const QVector3D &n);	// TODO: This should be moved somewhere else, like a Builder class

	void InitVertexData(const void* data, uint32_t size);

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
