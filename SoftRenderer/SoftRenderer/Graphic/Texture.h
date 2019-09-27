#ifndef  __TEXTURE__H__
#define  __TEXTURE__H__

#include "BmpLoader.h"
#include "Sampler.h"


class Texture
{
public:
	Texture(const char* src);
	~Texture();
	Sampler* getSampler(){ return _sampler; }

private:
	Sampler* _sampler;
};


#endif