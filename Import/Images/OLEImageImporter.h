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
#ifndef __WRAPPER_OLE_OLEIMAGEIMPORTER__
#define __WRAPPER_OLE_OLEIMAGEIMPORTER__

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
#include <string>
#include <vector>
#include <tchar.h>

#ifdef WRAPPER_LAYER_NAMESPACE
namespace WRAPPER_LAYER_NAMESPACE {
#endif
//==============================================================================
//	CLASS OLEImageImporter
//==============================================================================
class OLEImageImporter
{
public:

	// Supported pixel formats
	typedef enum
	{
		FORMAT_BGRA,
		FORMAT_L8
	} PixelFormat;

	//--------------------------------------------------------------------------
	//
	// will throw an exception is QuickTime is not available
	OLEImageImporter(const TCHAR *file);
	OLEImageImporter();
	
	//--------------------------------------------------------------------------
	//
	~OLEImageImporter();
	
	//--------------------------------------------------------------------------
	//
	void open(const TCHAR *file);
	operator bool () const;
	void close();
	
	//--------------------------------------------------------------------------
	//
	void getNativeSize(int *outWidth, int *outHeight) const;
	OLEImageImporter::PixelFormat nativePixelFormat() const;

	//--------------------------------------------------------------------------
	//
	void draw(unsigned char *data, int x, int y, int width, int height, PixelFormat format) const;
	void draw(unsigned char *data, PixelFormat format) const;
	
	//--------------------------------------------------------------------------
	//
	static void supportedExtensions(std::vector<std::string> *exts);

	//--------------------------------------------------------------------------
	//
	static int bytesPerPixel(PixelFormat format);

private:
	class OLEImageImporterImp;
	OLEImageImporterImp *mImp;
};

#ifdef WRAPPER_LAYER_NAMESPACE
}
#endif

#endif // __WRAPPER_OLE_OLEIMAGEIMPORTER__

