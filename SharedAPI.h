#pragma once

#define SHARED_API __declspec(dllexport)

struct ImageData
{
	int				_imageWidth;		// width
	int				_imageHeight;		// height
	int				_imageBPP;			// bits per pixel
	unsigned char*	_imageData;			// byte[] data
};

class SharedAPI
{
public:
	SharedAPI();
	virtual ~SharedAPI();

	int					getImageWidth();
	int					getImageHeight();
	int					getImageBPP();
	unsigned char*		getImageData();
	char*				getImagePath();
	void				CleanStringBuffer();
	void				LoadImage(const char* _path);

private:
	int					m_imgWidth;
	int					m_imgHeight;
	int					m_imgBPP;
	unsigned char*		m_imgData;
	char*				m_ptrFilepath;

	ImageData*			m_structData;
};

extern "C"
{
	SHARED_API int				Add(int a, int b);
	SHARED_API SharedAPI*		CreateSharedAPI();
	SHARED_API int				getImageWidth(SharedAPI* api);
	SHARED_API int				getImageHeight(SharedAPI* api);
	SHARED_API int				getImageBPP(SharedAPI* api);
	SHARED_API unsigned char*	getImageData(SharedAPI* api);
	SHARED_API char*			getImagePath(SharedAPI* api);
	SHARED_API void				LoadImage(SharedAPI* api, const char* _path);
}



