#include "MatrixPool.h"
#include "Vector3.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "_MacroConfig.h"

#define DEFAULT_CAPACITY 20

namespace cxMatrix
{

	cxGLStack::cxGLStack()
	{
		m_count = 0;
		m_capacity = DEFAULT_CAPACITY;
		m_statck = new matrix4[m_capacity];
		m_top = &m_statck[0];
	}

	cxGLStack::~cxGLStack()
	{
		if ( m_statck)
		{
			delete [] m_statck;
		}
	}

	void cxGLStack::push( matrix4* item )
	{
		assert( item != NULL,"push,item must not nil!");
		if ( m_count >= m_capacity)
		{
			matrix4* temp = m_statck;
			m_statck = new matrix4[m_capacity + DEFAULT_CAPACITY];
			memcpy(m_statck,temp,sizeof(matrix4) * m_capacity);
			m_capacity += DEFAULT_CAPACITY;
			delete [] temp;
			m_top = &m_statck[m_count -1];
		}

		m_count++;
		m_top = &m_statck[m_count];
		MCopy(m_top,item);
		
	//	LOG_ERROR("push count : %d",m_count);

	}

	void cxGLStack::pop()
	{
		assert(m_count != 0 ,"the stack is nil");
		m_count -- ;
		m_top = &m_statck[m_count -1 < 0 ? 0 : m_count -1 ];
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

	matrix4* cxGLStack::top()
	{
		return m_top;
	}


	void MVPMatrixStack::loadIdentity()
	{
		MLoadIdentity(currentStack->top());
	}

	void MVPMatrixStack::pushMatrix()
	{
		matrix4 mat4;
		MCopy(&mat4,currentStack->top());
		m_modelViewMatrixStack.push(&mat4);
	}

	void MVPMatrixStack::popMatrix()
	{
		m_modelViewMatrixStack.pop();
	}

	void MVPMatrixStack::translatef( float x,float y,float z )
	{
		matrix4* mat4 = currentStack->top();
		matrix4 mat_translate;
		MTranslatef(&mat_translate,x,y,z);
		MMult(mat4,mat4,&mat_translate);
	}

	void MVPMatrixStack::rotatef( float angle,float x,float y,float z )
	{
		matrix4* mat4 = currentStack->top();
		matrix4 mat_rotate;
		MRotatef(&mat_rotate,DEGREE(angle),x,y,z);
		MMult(mat4,mat4,&mat_rotate);
	}

	void MVPMatrixStack::scalef( float x,float y,float z )
	{
		matrix4* mat4 = currentStack->top();
		matrix4 mat_scale;
		MScalef(&mat_scale,x,y,z);
		MMult(mat4,mat4,&mat_scale);
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
		glUniformMatrix4fv(location,1,GL_FALSE,m_modelViewMatrixStack.top()->m_mat);
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

	matrix4* MVPMatrixStack::getMatrixMode( cxMatrixMode mode )
	{
		matrix4* res = NULL;
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

		
		matrix4 mat4;
		mat4.m_mat[0] = xaxis.x;
		mat4.m_mat[4] = xaxis.y;
		mat4.m_mat[8] = xaxis.z;
		mat4.m_mat[12] = -Vector3::DotVector3(&xaxis,&eye);

		mat4.m_mat[1] = yaxis.x;
		mat4.m_mat[5] = yaxis.y;
		mat4.m_mat[9] = yaxis.z;
		mat4.m_mat[13] = -Vector3::DotVector3(&yaxis,&eye);

		mat4.m_mat[2] = zaxis.x;
		mat4.m_mat[6] = zaxis.y;
		mat4.m_mat[10] = zaxis.z;
		mat4.m_mat[14] = -Vector3::DotVector3(&zaxis,&eye);

		mat4.m_mat[3] = mat4.m_mat[7] = mat4.m_mat[11] = 0;
		mat4.m_mat[15] = 1.0f;

		matrix4* top = currentStack->top();
		MMult(top,top,&mat4);
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
		matrix4* mat = currentStack->top();

		mat->m_mat[0] = cotangent / aspect;
		mat->m_mat[5] = cotangent;
		mat->m_mat[10] = -(zfar + znear) / deltaZ;
		mat->m_mat[11] = -1;
		mat->m_mat[14] = -2 * znear * zfar / deltaZ;
		mat->m_mat[15] = 0;
	}

	MVPMatrixStack* MVPMatrixStack::sg_MVPMatrixStack = NULL;


}