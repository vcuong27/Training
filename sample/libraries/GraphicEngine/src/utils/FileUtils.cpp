#include "FileUtils.h"
#include <fstream>


FileUtils* FileUtils::_instance = nullptr;
const int FileUtils::IT_COMPRESSED = 10;
const int FileUtils::IT_UNCOMPRESSED = 2;

FileUtils* FileUtils::create()
{
	if (!_instance)
	{
		_instance = new FileUtils();
	}

	return _instance;
}

FileUtils* FileUtils::getInstance()
{
	return _instance;
}

void FileUtils::destroyInstance()
{
	delete _instance;
	_instance = nullptr;
}

void FileUtils::addSearchPath(const std::string& path)
{
	std::string formattedPath = path;
	formattedPath.append("/");

	_searchPaths.push_back(formattedPath);
}

std::string FileUtils::getFileContentText(const std::string& path)
{
	std::string absolutePath = getAbsolutePath(path);
	if (absolutePath == "")
	{
		return "";
	}

	std::ifstream ifs(absolutePath);
	if (ifs.is_open())
	{
		std::string content = "";

		while (!ifs.eof())
		{
			std::string line;
			getline(ifs, line);
			line.append("\n");
			content.append(line);
		}

		ifs.close();

		return content;
	}

	return "";
}


char * FileUtils::LoadTGA( const std::string& path, int * width, int * height, int * bpp )
{
    std::string absolutePath = getAbsolutePath(path);
    FILE * f;
	
	if (fopen_s(&f, absolutePath.c_str(), "rb") != 0)
        return NULL;

    TGA_HEADER header;
    fread( &header, sizeof(header), 1, f );

    fseek( f, 0, SEEK_END );
    int fileLen = ftell( f );
    fseek( f, sizeof( header ) + header.identsize, SEEK_SET );

    if ( header.imagetype != IT_COMPRESSED && header.imagetype != IT_UNCOMPRESSED )
    {
        fclose( f );
        return NULL;
    }

    if ( header.bits != 24 && header.bits != 32 )
    {
        fclose( f );
        return NULL;
    }

    int bufferSize = fileLen - sizeof( header ) - header.identsize;
    char * pBuffer = new char[bufferSize];
    fread( pBuffer, 1, bufferSize, f );
    fclose( f );

    *width = header.width;
    *height = header.height;
    *bpp = header.bits;
    char * pOutBuffer = new char[ header.width * header.height * header.bits / 8 ];

    switch( header.imagetype )
    {
    case IT_UNCOMPRESSED:
        LoadUncompressedImage( pOutBuffer, pBuffer, &header );
        break;
    case IT_COMPRESSED:
        LoadCompressedImage( pOutBuffer, pBuffer, &header );
        break;
    }

    delete[] pBuffer;

    return pOutBuffer;
}

bool FileUtils::isExist(const std::string& path)
{
	std::ifstream ifs(path);
	return ifs.good();
}

std::string FileUtils::getAbsolutePath(const std::string& path)
{
	if (_searchPaths.size() == 0)
	{
		return "";
	}

	for each (auto& searchpath in _searchPaths)
	{
		std::string absolutePath = searchpath;
		absolutePath = absolutePath.append(path);

		if (isExist(absolutePath))
		{
			return absolutePath;
		}
	}

	return "";
}


void FileUtils::LoadCompressedImage( char* pDest, char * pSrc, TGA_HEADER * pHeader )
{
    int w = pHeader->width;
    int h = pHeader->height;
    int rowSize = w * pHeader->bits / 8;
    bool bInverted = ( (pHeader->descriptor & (1 << 5)) != 0 );
    char * pDestPtr = bInverted ? pDest + (h + 1) * rowSize : pDest;
    int countPixels = 0;
    int nPixels = w * h;

    while( nPixels > countPixels )
    {
        unsigned char chunk = *pSrc ++;
        if ( chunk < 128 )
        {
            int chunkSize = chunk + 1;
            for ( int i = 0; i < chunkSize; i ++ )
            {
                if ( bInverted && (countPixels % w) == 0 )
                    pDestPtr -= 2 * rowSize;
                *pDestPtr ++ = pSrc[2];
                *pDestPtr ++ = pSrc[1];
                *pDestPtr ++ = pSrc[0];
                pSrc += 3;
                if ( pHeader->bits != 24 )
                    *pDestPtr ++ = *pSrc ++;
                countPixels ++;
            }
        }
        else
        {
            int chunkSize = chunk - 127;
            for ( int i = 0; i < chunkSize; i ++ )
            {
                if ( bInverted && (countPixels % w) == 0 )
                    pDestPtr -= 2 * rowSize;
                *pDestPtr ++ = pSrc[2];
                *pDestPtr ++ = pSrc[1];
                *pDestPtr ++ = pSrc[0];
                if ( pHeader->bits != 24 )
                    *pDestPtr ++ = pSrc[3];
                countPixels ++;
            }
            pSrc += (pHeader->bits >> 3);
        }
    }
}

void FileUtils::LoadUncompressedImage( char* pDest, char * pSrc, TGA_HEADER * pHeader )
{
    int w = pHeader->width;
    int h = pHeader->height;
    int rowSize = w * pHeader->bits / 8;
    bool bInverted = ( (pHeader->descriptor & (1 << 5)) != 0 );
	bInverted = ! bInverted;
    for ( int i = 0; i < h; i ++ )
    {
        char * pSrcRow = pSrc + 
            ( bInverted ? ( h - i - 1 ) * rowSize : i * rowSize );
        if ( pHeader->bits == 24 )
        {
            for ( int j = 0; j < w; j ++ )
            {
                *pDest ++ = pSrcRow[2];
                *pDest ++ = pSrcRow[1];
                *pDest ++ = pSrcRow[0];
                pSrcRow += 3;
            }
        }
        else
        {
            for ( int j = 0; j < w; j ++ )
            {
                *pDest ++ = pSrcRow[2];
                *pDest ++ = pSrcRow[1];
                *pDest ++ = pSrcRow[0];
                *pDest ++ = pSrcRow[3];
				pSrcRow += 4;
            }
        }
    }
}