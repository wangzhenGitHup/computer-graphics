#include "Texture.h"
#include "Tools.h"

Texture::Texture(const char* src)
{
	BmpLoader* pBmpLoader = new BmpLoader();
	if (!pBmpLoader->loadBitmap(src))
	{
		_sampler = nullptr;
		return;
	}

	_sampler = new Sampler(pBmpLoader->getWidth(), pBmpLoader->getHeight());
	memcpy(_sampler->getImageData(),
		pBmpLoader->getData(),
		pBmpLoader->getWidth() * pBmpLoader->getHeight() * 3 * sizeof(unsigned char));
	delete pBmpLoader;
}

Texture::~Texture()
{
	if (_sampler)
	{
		delete _sampler;
		_sampler = nullptr;
	}
}
