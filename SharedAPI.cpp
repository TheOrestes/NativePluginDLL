#include "SharedAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
SHARED_API SharedAPI* CreateSharedAPI()
{
	return new SharedAPI();
}

SHARED_API char* getImagePath(SharedAPI* api)
{
	return api->getImagePath();
}

SHARED_API ImageData* LoadImage(SharedAPI* api, const char* _path)
{
	return api->LoadImage(_path);
}

SHARED_API void ReleaseMemory(SharedAPI* api)
{
	api->ReleaseMemory();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SharedAPI::SharedAPI()
	:	m_ptrFilepath(nullptr)
{
	
}


SharedAPI::~SharedAPI()
{
	free(m_ptrFilepath);
	ReleaseMemory();
}

char* SharedAPI::getImagePath()
{
	return m_ptrFilepath;
}

void SharedAPI::ReleaseMemory()
{
	if (m_imgData)
	{
		stbi_image_free(m_imgData->_data);
		free(m_imgData);
		m_imgData = nullptr;
	}
}


ImageData* SharedAPI::LoadImage(const char* _path)
{
	// initialize data structure to hold image properties!
	m_imgData = (ImageData*)malloc(sizeof(ImageData));
	
	// store filepath for local reference!
	m_ptrFilepath = (char*)malloc(strlen(_path) + 1);
	strcpy(m_ptrFilepath, _path);

	// load image data
	stbi_set_flip_vertically_on_load(1);
	m_imgData->_data = stbi_load(_path, &(m_imgData->_width), &(m_imgData->_height), &(m_imgData->_bpp), 0);

	return m_imgData;
}