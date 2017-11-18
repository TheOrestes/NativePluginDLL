#include "SharedAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
SHARED_API int Add(int a, int b)
{
	return a + b;
}

SHARED_API SharedAPI * CreateSharedAPI(char * path)
{
	return nullptr;
}

SHARED_API SharedAPI* CreateSharedAPI()
{
	return new SharedAPI();
}

SHARED_API int getImageWidth(SharedAPI* api)
{
	return api->getImageWidth();
}

SHARED_API int getImageHeight(SharedAPI* api)
{
	return api->getImageHeight();
}

SHARED_API int getImageBPP(SharedAPI* api)
{
	return api->getImageBPP();
}

SHARED_API unsigned char* getImageData(SharedAPI* api)
{
	return api->getImageData();
}

SHARED_API char* getImagePath(SharedAPI* api)
{
	return api->getImagePath();
}

SHARED_API void LoadImage(SharedAPI* api, const char* _path)
{
	return api->LoadImage(_path);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SharedAPI::SharedAPI()
	:	m_ptrFilepath(nullptr),
		m_imgData(nullptr),
		m_imgWidth(0),
		m_imgHeight(0),
		m_imgBPP(0)
{
	
}


SharedAPI::~SharedAPI()
{
	stbi_image_free(m_imgData);
}

int SharedAPI::getImageWidth()
{
	return m_imgWidth;
}

int SharedAPI::getImageHeight()
{
	return m_imgHeight;
}

int SharedAPI::getImageBPP()
{
	return m_imgBPP;
}

unsigned char* SharedAPI::getImageData()
{
	return m_imgData;
}

char* SharedAPI::getImagePath()
{
	return m_ptrFilepath;
}

void SharedAPI::CleanStringBuffer()
{
	free(m_ptrFilepath);
}

void SharedAPI::LoadImage(const char* _path)
{
	// store filepath for local reference!
	m_ptrFilepath = (char*)malloc(strlen(_path) + 1);
	strcpy(m_ptrFilepath, _path);

	// load image data
	stbi_set_flip_vertically_on_load(1);
	m_imgData = stbi_load(_path, &m_imgWidth, &m_imgHeight, &m_imgBPP, 0);
}