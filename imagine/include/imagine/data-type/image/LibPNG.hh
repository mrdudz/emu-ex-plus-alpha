#pragma once

/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <imagine/config/defs.hh>
#include <imagine/pixmap/Pixmap.hh>
#include <imagine/data-type/image/GfxImageSource.hh>
#include <imagine/io/IO.hh>
#include <imagine/base/ApplicationContext.hh>
#include <system_error>

#define PNG_SKIP_SETJMP_CHECK
#include <png.h>

class Png
{
public:
	constexpr Png(Base::ApplicationContext ctx):
		ctx{ctx}
	{}
	std::error_code readHeader(GenericIO io);
	std::errc readImage(IG::Pixmap dest);
	bool hasAlphaChannel();
	bool isGrayscale();
	void freeImageData();
	uint32_t width();
	uint32_t height();
	IG::PixelFormat pixelFormat();
	explicit operator bool() const;
	constexpr Base::ApplicationContext appContext() const { return ctx; }

protected:
	png_structp png{};
	png_infop info{};
	//png_infop end;
	Base::ApplicationContext ctx{};
	void setTransforms(IG::PixelFormat outFormat, png_infop transInfo);
	static bool supportUncommonConv;
};

class PngFile final: public GfxImageSource
{
public:
	constexpr PngFile(Base::ApplicationContext ctx):
		png{ctx}
	{}
	~PngFile();
	std::error_code load(GenericIO io);
	std::error_code load(const char *name);
	std::error_code loadAsset(const char *name, const char *appName = Base::ApplicationContext::applicationName);
	void deinit();
	std::errc write(IG::Pixmap dest) final;
	IG::Pixmap pixmapView() final;
	explicit operator bool() const final;

protected:
	Png png;
};
