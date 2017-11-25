#include "SharedAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
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

SHARED_API void SetDebugFunction(FuncPtr fp)
{
	DEBUG_CONSOLE_LOG = fp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SharedAPI::SharedAPI()
	:	m_ptrFilepath(NULL)
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
		m_imgData = NULL;
	}
}


ImageData* SharedAPI::LoadImage(const char* _path)
{
	// initialize data structure to hold image properties!
	m_imgData = (ImageData*)malloc(sizeof(ImageData));
	
	// store filepath for local reference!
	m_ptrFilepath = (char*)malloc(strlen(_path) + 1);
	strcpy(m_ptrFilepath, _path);

#if defined _WIN32
	DEBUG_CONSOLE_LOG(m_ptrFilepath);
#else
	printf("==================== FROM NATIVE ====================");
	printf("%s", m_ptrFilepath);
#endif
	

	// load image data
	stbi_set_flip_vertically_on_load(1);
	m_imgData->_data = stbi_load(_path, &(m_imgData->_width), &(m_imgData->_height), &(m_imgData->_bpp), 0);

	if (m_imgData->_data == NULL)
	{

#if defined _WIN32
		DEBUG_CONSOLE_LOG(stbi_failure_reason());
#else
		printf("==================== FROM NATIVE ====================");
		printf("%s", stbi_failure_reason());
#endif

		m_imgData->_width = -1;
		m_imgData->_height = -1;
		m_imgData->_bpp = -1;
	}

	return m_imgData;
}