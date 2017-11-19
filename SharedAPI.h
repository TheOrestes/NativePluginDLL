#pragma once

#define SHARED_API __declspec(dllexport)

struct ImageData
{
	int				_width;		// width
	int				_height;		// height
	int				_bpp;			// bits per pixel
	unsigned char*	_data;			// byte[] data
};

class SharedAPI
{
public:
	SharedAPI();
	virtual ~SharedAPI();

	char*				getImagePath();	

	ImageData*			LoadImage(const char* _path);
	void				ReleaseMemory();

private:
	char*				m_ptrFilepath;
	ImageData*			m_imgData;
};

extern "C"
{
	SHARED_API SharedAPI*		CreateSharedAPI();
	SHARED_API char*			getImagePath(SharedAPI* api);
	SHARED_API ImageData*		LoadImage(SharedAPI* api, const char* _path);
	SHARED_API void				ReleaseMemory(SharedAPI* api);
}



