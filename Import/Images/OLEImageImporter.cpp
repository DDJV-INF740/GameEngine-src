/*******************************************************************************
 Copyright 2007 Gaspard Petit
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*******************************************************************************/

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "OLEImageImporter.h"

#include <windows.h>
#include <olectl.h>

//==============================================================================
//	PRIVATE GLOBAL CONSTANTS
//==============================================================================
namespace {
static const long HIMETRIC_INCH = 2540;
}

namespace engine {

//==============================================================================
//	CLASS OLEImageImporter::OLEImageImporterImp
//==============================================================================
class OLEImageImporter::OLEImageImporterImp
{
public:
	//--------------------------------------------------------------------------
	//
	OLEImageImporterImp()
	:
		mPicture(NULL)
	{}
	
	//--------------------------------------------------------------------------
	//
	void close()
	{
		if (mPicture)
		{
			mPicture->Release();
			mPicture = NULL;
		}
	}
	
	//--------------------------------------------------------------------------
	//
	void open(const TCHAR *path)
	{
		//----------------------------------------------------------------------
		// the following code to load from OleLoadPicture was originally taken 
		// from http://www.codeproject.com/KB/graphics/render.aspx 
		//----------------------------------------------------------------------
		
		// make sure we're in a clean state
		close();
		
		// open the file
		HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
	    {
//			AfxMessageBox ("Could not read file");
			return;
		}


		// we will read the whole file in global memory, find the size first
	    DWORD dwFileSize = GetFileSize(hFile, NULL);

		if (dwFileSize == (DWORD)-1)
		{
			CloseHandle(hFile);
//			AfxMessageBox ("File seems to be empty");
			return;
		}

		// allocate memory to read the whole file
		LPVOID pvData = NULL;

		// alloc memory based on file size
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
		if (hGlobal == NULL)
		{
			CloseHandle(hFile);
//			AfxMessageBox ("Could not allocate memory for image");
			return;
		}

		pvData = GlobalLock(hGlobal);

		if (pvData == NULL)
		{
			GlobalUnlock(hGlobal);
			CloseHandle(hFile);
//			AfxMessageBox ("Could not lock memory for image");
			return;
		}


		// read file and store in global memory
	    DWORD dwBytesRead = 0;
		BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
		GlobalUnlock(hGlobal);
		CloseHandle(hFile);

		if (!bRead)
		{
//			AfxMessageBox ("Could not read file");
			return;
		}

		// create IStream* from global memory
		LPSTREAM pstm = NULL;
		HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
		// from hereon, hGlobal will be released when we call pstm->Release();

		if (!(SUCCEEDED(hr)))
		{
//			AfxMessageBox ("CreateStreamOnHGlobal() failed");
			if (pstm != NULL) pstm->Release();
			return;
		}
		else if (pstm == NULL)
		{
//			AfxMessageBox ("CreateStreamOnHGlobal() failed");
			return;
		}

		hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&(mPicture));

		if (!(SUCCEEDED(hr)))
		{
    		pstm->Release();
			//AfxMessageBox("Could not load image (hr failure)");
			return;
		}
		else if (mPicture == NULL)
		{
			pstm->Release();
//			AfxMessageBox("Could not load image (mPicture failure)");
			return;
		}

	    pstm->Release();
	}
	
	//--------------------------------------------------------------------------
	//
	bool isOpen() const
	{
		return mPicture != NULL;
	}
	
	//--------------------------------------------------------------------------
	//
	void getNativeSize(int *outWidth, int *outHeight) const
	{
		*outWidth = *outHeight = 0;

		long hmWidth = 0, hmHeight = 0;
		mPicture->get_Width (&hmWidth);
		mPicture->get_Height(&hmHeight);

		HDC Screen = ::CreateCompatibleDC(0);

		*outWidth	= MulDiv(hmWidth, GetDeviceCaps(Screen, LOGPIXELSX), HIMETRIC_INCH);
		*outHeight	= MulDiv(hmHeight, GetDeviceCaps(Screen, LOGPIXELSY), HIMETRIC_INCH);
		::DeleteDC(Screen);
	}
	
	//--------------------------------------------------------------------------
	//
	void draw(unsigned char *data, PixelFormat format) const
	{
		int width, height;
		getNativeSize(&width, &height);
		draw(data, 0, 0, width, height, format);
	}

	//--------------------------------------------------------------------------
	//
	void draw(unsigned char *data, int x, int y, int width, int height, PixelFormat format) const
	{
		HDC hDC = CreateCompatibleDC(0);

		long hmWidth = 0, hmHeight = 0;
		mPicture->get_Width (&hmWidth);
		mPicture->get_Height(&hmHeight);

		BITMAPINFO bmInfo = {0};
		bmInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
		bmInfo.bmiHeader.biSizeImage = 0;
		bmInfo.bmiHeader.biPlanes = 1;
		bmInfo.bmiHeader.biBitCount = 32;
		bmInfo.bmiHeader.biWidth = width;
		bmInfo.bmiHeader.biHeight = height;

		unsigned char *pixels;
		HBITMAP bm = CreateDIBSection(hDC, &bmInfo, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
		HGDIOBJ old = SelectObject(hDC, bm);

		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = width;
		rc.bottom = height;
	
		HRESULT hrP =
		mPicture->Render(hDC, 0, 0, width, height, 0, hmHeight, hmWidth, -hmHeight, &rc);

		if (FAILED(hrP))
	        return;

		BITMAP b;
		SelectObject(hDC, old);
		GetObject(bm, sizeof(b), &b);
		int rowLength = b.bmWidthBytes;

		// load the texture into the data buffer
		if (format == FORMAT_BGRA)
		{
			if (GetBitmapBits(bm, b.bmHeight*rowLength, data) == 0)
			{
				return;
			}

			// scan to check if the alpha is all transparent
			bool allTransp = true;
			unsigned char *row = data;

			for (int y = 0; allTransp && y < b.bmHeight; ++y)
			{
				for (int x = 0; allTransp && x < b.bmWidth; ++x)
				{
					int a = row[x*4+3];
					if (a != 0)
						allTransp = false;
				}
				row += rowLength;
			}

			if (allTransp)
			{
				row = data;
				for (int y = 0; y < b.bmHeight; ++y)
				{
					for (int x = 0; x < b.bmWidth; ++x)
					{
						row[x*4+3] = 255;
					}
					row += rowLength;
				}
			}

		}
		else if (format == FORMAT_L8)
		{
			// load in temp BGRA buffer and convert
			unsigned char *tmpBGRA = (unsigned char*)malloc(width*height*4);
			if (GetBitmapBits(bm, b.bmHeight*rowLength, tmpBGRA) == 0)
			{
				return;
			}
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					data[x + y*width] = unsigned char(
						0.1f * tmpBGRA[(x + y*width)*4+0] +  // B
						0.6f * tmpBGRA[(x + y*width)*4+1] +  // G
						0.3f * tmpBGRA[(x + y*width)*4+2]);   // R
				}
			}
			free(tmpBGRA);
		}

		DeleteObject(bm);
		DeleteDC(hDC);
	}
	
	//--------------------------------------------------------------------------
	//
	int nativeBytesPerPixel() const
	{
		return 4;
	}
	
	//--------------------------------------------------------------------------
	//
	PixelFormat nativePixelFormat() const
	{
		return FORMAT_BGRA;
	}

private:
	LPPICTURE mPicture;
};

//==============================================================================
// CLASS OLEImageImporter
//==============================================================================

//------------------------------------------------------------------------------
//
OLEImageImporter::OLEImageImporter()
:
	mImp(new OLEImageImporterImp)
{}

//------------------------------------------------------------------------------
//
OLEImageImporter::OLEImageImporter(const TCHAR *path)
:
	mImp(new OLEImageImporterImp)
{
	open(path);
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::close()
{
	mImp->close();
}

//------------------------------------------------------------------------------
//
OLEImageImporter::~OLEImageImporter()
{
	close();
	delete mImp;
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::open(const TCHAR *file)
{
	mImp->open(file);
}

//------------------------------------------------------------------------------
//
OLEImageImporter::operator bool () const
{
	return mImp->isOpen();
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::getNativeSize(int *outWidth, int *outHeight) const
{
	return mImp->getNativeSize(outWidth, outHeight);
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::draw(unsigned char *data, int x, int y, int width, int height, PixelFormat format) const
{
	mImp->draw(data, x, y, width, height, format);
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::draw(unsigned char *data, PixelFormat format) const
{
	mImp->draw(data, format);
}

//------------------------------------------------------------------------------
//
void OLEImageImporter::supportedExtensions(std::vector<std::string> *outExts)
{
	outExts->clear();
	outExts->push_back("jpeg");
	outExts->push_back("jpg");
	outExts->push_back("gif");
	outExts->push_back("bmp");
}


//------------------------------------------------------------------------------
//
OLEImageImporter::PixelFormat OLEImageImporter::nativePixelFormat() const
{
	return mImp->nativePixelFormat();
}


//------------------------------------------------------------------------------
//
int OLEImageImporter::bytesPerPixel(PixelFormat format)
{
	switch(format)
	{
//		case (FORMAT_RGB):		return 3;
//		case (FORMAT_ARGB):		return 4;
//		case (FORMAT_BGR):		return 3;
		case (FORMAT_BGRA):		return 4;
//		case (FORMAT_ABGR):		return 4;
//		case (FORMAT_RGBA):		return 4;
//		case (FORMAT_YUYV422):	return 2;
//		case (FORMAT_UYVY422):	return 2;
		case (FORMAT_L8):		return 1;
	}

	return 4;
}

} // namespace engine
