#include "MatrixPool.h"
#include "Vector3.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "MacroConfig.h"

#define DEFAULT_CAPACITY 20

namespace cxMatrix
{

	cxGLStack::cxGLStack()
	{
		m_count = 0;
		m_capacity = DEFAULT_CAPACITY;
		m_statck = new Matrix4x4[m_capacity];
		m_top = &m_statck[0];
	}

	cxGLStack::~cxGLStack()
	{
		if ( m_statck)
		{
			delete [] m_statck;
		}
	}

	void cxGLStack::push( Matrix4x4* item )
	{
		assert( item != NULL,"push,item must not nil!");
		if ( m_count >= m_capacity)
		{
			Matrix4x4* temp = m_statck;
			m_statck = new Matrix4x4[m_capacity + DEFAULT_CAPACITY];
			memcpy(m_statck,temp,sizeof(Matrix4x4) * m_capacity);
			m_capacity += DEFAULT_CAPACITY;
			delete [] temp;
			m_top = &m_statck[m_count -1];
		}

		m_count++;
		m_top = &m_statck[m_count];
		MCopy4x4(m_top,item);
		
	//	LOG_ERROR("push count : %d",m_count);

	}

	void cxGLStack::pop()
	{
		assert(m_count != 0 ,"the stack is nil");
		m_count -- ;
		m_top = &m_statck[m_count -1 < 0 ? 0 : m_count ];
	//	LOG_ERROR("pop count : %d",m_count);
	}

	int cxGLStack::itemSize()
	{
		return m_count;
	}

	int cxGLStack::capacity()
	{
		return m_capacity;
	}

	Matrix4x4* cxGLStack::top()
	{
		return m_top;
	}


	void MVPMatrixStack::loadIdentity()
	{
		MLoadIdentity4x4(currentStack->top());
	}

	void MVPMatrixStack::pushMatrix()
	{
		Matrix4x4 mat4;
		MCopy4x4(&mat4,currentStack->top());
		currentStack->push(&mat4);
	}

	void MVPMatrixStack::popMatrix()
	{
		currentStack->pop();
	}

	void MVPMatrixStack::translatef( float x,float y,float z )
	{
		Matrix4x4* mat4 = currentStack->top();
		Matrix4x4 mat_translate;
		MTranslatef4x4(&mat_translate,x,y,z);
		MMult4x4(mat4,mat4,&mat_translate);
	}

	void MVPMatrixStack::rotatef( float angle,float x,float y,float z )
	{
		Matrix4x4* mat4 = currentStack->top();
		Matrix4x4 mat_rotate;
		MRotatef4x4(&mat_rotate,DEGREE(angle),x,y,z);
		MMult4x4(mat4,mat4,&mat_rotate);
	}

	void MVPMatrixStack::scalef( float x,float y,float z )
	{
		Matrix4x4* mat4 = currentStack->top();
		Matrix4x4 mat_scale;
		MScalef4x4(&mat_scale,x,y,z);
		MMult4x4(mat4,mat4,&mat_scale);
	}

	MVPMatrixStack* MVPMatrixStack::sharedMVPMatrixStack()
	{
		if( sg_MVPMatrixStack == NULL){
			sg_MVPMatrixStack = new MVPMatrixStack();
		}
		return sg_MVPMatrixStack;
	}

	void MVPMatrixStack::freeMVPMatrixStack()
	{
		if (sg_MVPMatrixStack)
		{
			delete sg_MVPMatrixStack;
			sg_MVPMatrixStack = NULL;
		}
	}

	void MVPMatrixStack::uniformMatrix4fv( GLint location )
	{
		glUniformMatrix4fv(location,1,GL_FALSE,currentStack->top()->mat);
	}

	MVPMatrixStack::MVPMatrixStack()
	{
		currentStack = & m_modelViewMatrixStack;
	}

	void MVPMatrixStack::matrixMode( cxMatrixMode mode )
	{
		switch (mode)
		{
		case CXGL_VIEWMODE:
			currentStack = & m_modelViewMatrixStack;
			break;
		case CXGL_PROJECT:
			currentStack = & m_projectMatrixStack;
			break;
		}
	}

	Matrix4x4* MVPMatrixStack::getMatrixMode( cxMatrixMode mode )
	{
		Matrix4x4* res = NULL;
		switch (mode)
		{
		case CXGL_VIEWMODE:
			res = m_modelViewMatrixStack.top();
			break;
		case CXGL_PROJECT:
			res = m_projectMatrixStack.top();
			break;
		default:
			LOG_ERROR("########getMatrixMode,please assign the mode!!");
			break;
		}
		return res;
	}

	void MVPMatrixStack::lookAt(Vector3& eye,Vector3& target,Vector3& up )
	{
		Vector3 xaxis,yaxis,zaxis;
		Vector3::Subtract(&zaxis,&eye,&target);
		up.normalize();
		zaxis.normalize();

		Vector3::CrossVector3(&xaxis,&up,&zaxis);
		xaxis.normalize();

		Vector3::CrossVector3(&yaxis,&zaxis,&xaxis);
		yaxis.normalize();

		
		Matrix4x4 mat4;
		mat4.mat[0] = xaxis.x;
		mat4.mat[4] = xaxis.y;
		mat4.mat[8] = xaxis.z;
		mat4.mat[12] = -Vector3::DotVector3(&xaxis,&eye);

		mat4.mat[1] = yaxis.x;
		mat4.mat[5] = yaxis.y;
		mat4.mat[9] = yaxis.z;
		mat4.mat[13] = -Vector3::DotVector3(&yaxis,&eye);

		mat4.mat[2] = zaxis.x;
		mat4.mat[6] = zaxis.y;
		mat4.mat[10] = zaxis.z;
		mat4.mat[14] = -Vector3::DotVector3(&zaxis,&eye);

		mat4.mat[3] = mat4.mat[7] = mat4.mat[11] = 0;
		mat4.mat[15] = 1.0f;

		Matrix4x4* top = currentStack->top();
		MMult4x4(top,top,&mat4);
	}

	void MVPMatrixStack::lookAt( float eyex,float eyey,float eyez,float targetx,float targety,float targetz, float upx,float upy,float upz )
	{
		Vector3 eye(eyex,eyey,eyez);
		Vector3 target(targetx,targety,targetz);
		Vector3 up(upx,upy,upz);
		lookAt(eye,target,up);
	}

	void MVPMatrixStack::perspectiveProjection( float fovy,float aspect,float znear,float zfar )
	{
		float r = DEGREE(fovy / 2);
		float deltaZ = zfar - znear;
		float s = sin(r);
		float cotangent = 0;

		if (deltaZ == 0 || s == 0 || aspect == 0) {
			return ;
		}

		//cos(r) / sin(r) = cot(r)
		cotangent = cos(r) / s;

		loadIdentity();
		Matrix4x4* mat = currentStack->top();

		mat->mat[0] = cotangent / aspect;
		mat->mat[5] = cotangent;
		mat->mat[10] = -(zfar + znear) / deltaZ;
		mat->mat[11] = -1;
		mat->mat[14] = -2 * znear * zfar / deltaZ;
		mat->mat[15] = 0;
	}

	MVPMatrixStack* MVPMatrixStack::sg_MVPMatrixStack = NULL;


}