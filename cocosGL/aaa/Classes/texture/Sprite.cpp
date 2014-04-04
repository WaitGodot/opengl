#include "Sprite.h"
#include "Texture.h"
#include "MacroConfig.h"
#include "shader/GLShaderMgr.h"
#include "shader/GLShaderProgram.h"

using namespace glShaderSpace;

Sprite::Sprite():
m_texture(0)
{

}

Sprite::~Sprite()
{
	DELETE_SAFE(m_texture);
}

Sprite* Sprite::create( Texture* tx )
{
	Sprite* p = new Sprite();
	if (p && p->initWithTexture(tx))
	{
		return p;
	}
	DELETE_SAFE(p);
	return NULL;
}

bool Sprite::initWithTexture( Texture* tx )
{
// 	if (tx == NULL)
// 	{
// 		return false;
// 	}
	m_texture = tx;
	return true;
}


void Sprite::draw()
{
	if (!m_texture || m_texture->getId()<=0)
	{
		return;
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,m_texture->getId());

	GLShaderProgram* p = shareGLShaderManager()->getByKey(_Texture_key);
	p->use();
	p->updateMVPMatrix();

	GLint l_position = p->getVertexAttLoction(_Vertex_Position);
	GLint l_texCoords = p->getVertexAttLoction(_Vertex_texCoords);

	glEnableVertexAttribArray(l_position);
	float vec[] = {
		-4,4,0,
		-4,-4,0,
		4,4,0,
		4,-4,0,
	};

	glVertexAttribPointer(l_position,3,GL_FLOAT,GL_FALSE,0,vec);

	glEnableVertexAttribArray(l_texCoords);

	float vecCoords[] = {
		0,0,0,
		0,1,0,
		1,0,0,
		1,1,0,
	};
	glVertexAttribPointer(l_texCoords,3,GL_FLOAT,GL_FALSE,0,vecCoords);

	glDrawArrays(GL_TRIANGLE_STRIP,0,4);

}

void Sprite::setTexture( Texture* tx )
{
	if (m_texture == tx)
	{
		return ;
	}
	m_texture = tx;
}
