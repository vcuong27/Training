#pragma once

#include <string>
#include <vector>

class FileUtils
{
public:
	static FileUtils* create();
	static FileUtils* getInstance();
	static void destroyInstance();

	void addSearchPath(const std::string& path);

	std::string getFileContentText(const std::string& path);
	char * LoadTGA( const std::string& path, int * width, int * height, int * bpp );
	std::string getAbsolutePath(const std::string& path);
	bool isExist(const std::string& path);

protected:
	FileUtils() {}
	virtual ~FileUtils() {}

private:
	static FileUtils* _instance;
	std::vector<std::string> _searchPaths;

#pragma pack(push,x1)					// Byte alignment (8-bit)
#pragma pack(1)
	typedef struct
	{
		unsigned char  identsize;			// size of ID field that follows 18 byte header (0 usually)
		unsigned char  colourmaptype;		// type of colour map 0=none, 1=has palette
		unsigned char  imagetype;			// type of image 2=rgb uncompressed, 10 - rgb rle compressed

		short colourmapstart;				// first colour map entry in palette
		short colourmaplength;				// number of colours in palette
		unsigned char  colourmapbits;		// number of bits per palette entry 15,16,24,32

		short xstart;						// image x origin
		short ystart;						// image y origin
		short width;						// image width in pixels
		short height;						// image height in pixels
		unsigned char  bits;				// image bits per pixel 24,32
		unsigned char  descriptor;			// image descriptor bits (vh flip bits)

		// pixel data follows header

	} TGA_HEADER;

#pragma pack(pop,x1)

	static const int IT_COMPRESSED ;
	static const int IT_UNCOMPRESSED ;
	void LoadUncompressedImage( char* pDest, char * pSrc, TGA_HEADER * pHeader );
	void LoadCompressedImage( char* pDest, char * pSrc, TGA_HEADER * pHeader );




};

