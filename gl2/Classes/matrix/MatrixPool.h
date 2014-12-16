#ifndef _MATRIX_POOL_H
#define _MATRIX_POOL_H

#include "Matrix4x4.h"
#include <gl/glew.h>

namespace cxMatrix
{

	class cxGLStack 
	{
	
		Matrix4x4* m_top;
		Matrix4x4* m_statck;
		int m_count;
		int m_capacity;

	public:
		cxGLStack();
		~cxGLStack();

		void push(Matrix4x4* item);
		void pop();

		int itemSize();
		int capacity();
		Matrix4x4* top();


	};

	enum cxMatrixMode{
		CXGL_VIEWMODE,
		CXGL_PROJECT,
	};

	class Vector3;

	class MVPMatrixStack
	{
		cxGLStack m_modelViewMatrixStack;
		cxGLStack m_projectMatrixStack;

		cxGLStack* currentStack;

		static MVPMatrixStack* sg_MVPMatrixStack;

		MVPMatrixStack();

	public:

		void loadIdentity();
		void pushMatrix();
		void popMatrix();
		void translatef(float x,float y,float z);
		void rotatef(float angle,float x,float y,float z);
		void scalef(float x,float y,float z);
		//..
		void lookAt(float eyex,float eyey,float eyez,float targetx,float targety,float targetz,
			float upx,float upy,float upz);
		void lookAt(Vector3& eye, Vector3& target,Vector3& up);

		void perspectiveProjection(float fovy,float aspect,float znear,float zfar);

		void uniformMatrix4fv(GLint location);

		void matrixMode(cxMatrixMode mode);
		Matrix4x4* getMatrixMode(cxMatrixMode mode);

		static MVPMatrixStack* sharedMVPMatrixStack();
		static void freeMVPMatrixStack();
	};

#define cxGLLoadentity() MVPMatrixStack::sharedMVPMatrixStack()->loadIdentity()
#define cxGLPushMatrix() MVPMatrixStack::sharedMVPMatrixStack()->pushMatrix()
#define cxGLPopMatrix() MVPMatrixStack::sharedMVPMatrixStack()->popMatrix()
#define cxGLTranslatef(x,y,z) MVPMatrixStack::sharedMVPMatrixStack()->translatef(x,y,z)
#define cxGLRotatef(angle,x,y,z) MVPMatrixStack::sharedMVPMatrixStack()->rotatef(angle,x,y,z)
#define cxGLScalef(x,y,z) MVPMatrixStack::sharedMVPMatrixStack()->scalef(x,y,z)
#define cxGLUniformMatrix4f(location) MVPMatrixStack::sharedMVPMatrixStack()->uniformMatrix4fv(location)
#define cxGLMatrixMode(mode)  MVPMatrixStack::sharedMVPMatrixStack()->matrixMode(mode)
#define cxGLGetMatrixMode(mode) MVPMatrixStack::sharedMVPMatrixStack()->getMatrixMode(mode)
#define cxGLLookAt(eyex,eyey,eyez,targetx,targety,targetz,upx,upy,upz) MVPMatrixStack::sharedMVPMatrixStack()->lookAt(eyex,eyey,eyez,targetx,targety,targetz,upx,upy,upz)
#define cxGLPerspectiveProjection(fovY,aspect,zNear,zFar) MVPMatrixStack::sharedMVPMatrixStack()->perspectiveProjection(fovY,aspect,zNear,zFar)

#define cxGLFreeStack() MVPMatrixStack::sharedMVPMatrixStack()->freeMVPMatrixStack()
}


#endif