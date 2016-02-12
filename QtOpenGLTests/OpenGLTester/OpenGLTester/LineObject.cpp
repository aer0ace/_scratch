#include "LineObject.h"

static const uint32_t kVertexCount = 2;
static const uint32_t kValueStride = 6;	// Not the most ideal solution here either.

LineObject::LineObject()
{
	mData.resize(kVertexCount * kValueStride);
}

void LineObject::Update(const QVector3D& pos, const QVector3D &n)
{
	mPos = pos;
	mNormal = n;

	Build(true);


}

void LineObject::BuildVertexData()
{
	mDataCount = 0;

	Add(QVector3D(0.0f, 0.0f, 0.0f), mNormal);
	Add(mPos, mNormal);
}

void LineObject::InitVBOAttribs()
{
	mVBO.setUsagePattern(QOpenGLBuffer::UsagePattern::DynamicDraw);
}
//
//void LineObject::InitVertexArrays()
//{
//	ObjectBase::InitVertexArrays(nullptr, kVertexCount * kValueStride);
//}

void LineObject::PreDraw()
{
	mVBO.bind();
	mVBO.write(0, GetConstData(), GetDataCount() * sizeof(GLfloat));
	mVBO.release();
}
