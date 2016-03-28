#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include <ObjectBase.h>

class BoxObject : public ObjectBase
{
public:
	BoxObject();
	~BoxObject();

protected:
	virtual void BuildVertexData();

private:
	
};

#endif // BOXOBJECT_H
