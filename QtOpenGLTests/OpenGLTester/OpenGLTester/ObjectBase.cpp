#include <ObjectBase.h>
#include <QOpenGLFunctions>

ObjectBase::ObjectBase()
	: mShaderProgram(nullptr)
	, mDataCount(0)
	, mValueStride(0)
	, mRenderMode(GL_LINES)
{
	mData.resize(2500 * 6);	// Obviously not the greatest...
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::SetRenderMode(GLenum renderMode)
{
	mRenderMode = renderMode;
}

uint32_t ObjectBase::GetVertexCount() const
{
	if (mValueStride == 0)
		return 0;

	return (mDataCount / mValueStride);
}

void ObjectBase::Add(const QVector3D &v, const QVector3D &n)
{
	Q_ASSERT(mValueStride != 0);

	if (mValueStride == 0)
		return;
	
	GLfloat *p = mData.data() + mDataCount;
	*p++ = v.x();
	*p++ = v.y();
	*p++ = v.z();
	*p++ = n.x();
	*p++ = n.y();
	*p++ = n.z();
	mDataCount += mValueStride;	// Ideally, we need to set the value from the stride, but right now we are in a catch-22 situation with data/format init
}

void ObjectBase::InitAttribs()
{
	mVAO.create();
	QOpenGLVertexArrayObject::Binder vaoBinder(&mVAO);

	mVBO.create();
	mVBO.bind();

	InitVBOAttribs();
	
	// Store the vertex attribute bindings for the program.
	SetupVertexAttributes(&mVBO);
}

void ObjectBase::InitVertexData(const void* data, uint32_t size)
{
	mVBO.bind();

	if (data)
		mVBO.allocate(data, size * sizeof(GLfloat));
	else
		mVBO.allocate(size * sizeof(GLfloat));	// Allocate without data if intended for dynamic drawing

	mVBO.release();
}

void ObjectBase::SetupVertexAttributes(QOpenGLBuffer* vbo)
{
	if (!vbo)
		return;

	vbo->bind();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glEnableVertexAttribArray(0);
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	vbo->release();

	mValueStride = 6;
}

void ObjectBase::InitVBOAttribs()
{
	// Override and do some extra initing here.
}

void ObjectBase::Build(bool dynamic)
{
	BuildVertexData();
	InitVertexData(dynamic ? nullptr : GetConstData(), GetDataCount());
}

void ObjectBase::PreDraw()
{
	// Do any initialization before drawing, like updating vertex data
}

void ObjectBase::Draw()
{
	QOpenGLVertexArrayObject::Binder vaoBinder(&mVAO);

	PreDraw();

	glDrawArrays(mRenderMode, 0, GetVertexCount());
	vaoBinder.release();
}

