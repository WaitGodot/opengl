#ifndef _CX_SPRITE_H
#define _CX_SPRITE_H

#include "base/Geometry.h"


class Texture;
class Sprite
{
public:
	static Sprite* create(Texture* tx);
	bool initWithTexture(Texture* tx);

	void setTexture(Texture* tx);
	void draw();

	Sprite();
	~Sprite();

private:
	Texture* m_texture;
	cxGeomety::Rect m_texCoord;
	cxGeomety::Point m_position;
	cxGeomety::Point m_anchorPosition;
};
#endif