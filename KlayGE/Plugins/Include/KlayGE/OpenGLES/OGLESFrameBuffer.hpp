// OGLESFrameBuffer.hpp
// KlayGE OpenGL ES渲染到纹理类 头文件
// Ver 3.10.0
// 版权所有(C) 龚敏敏, 2010
// Homepage: http://www.klayge.org
//
// 3.10.0
// 初次建立 (2010.1.22)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#ifndef _OGLESFRAMEBUFFER_HPP
#define _OGLESFRAMEBUFFER_HPP

#pragma once

#include <KlayGE/FrameBuffer.hpp>
#include <KlayGE/RenderView.hpp>

namespace KlayGE
{
	class OGLESFrameBuffer : public FrameBuffer
	{
	public:
		explicit OGLESFrameBuffer(bool off_screen);
		virtual ~OGLESFrameBuffer();

		virtual std::wstring const & Description() const;

		void OnBind();

		void Clear(uint32_t flags, Color const & clr, float depth, int32_t stencil);
		virtual void Discard(uint32_t flags) KLAYGE_OVERRIDE;

		GLuint OGLFbo() const
		{
			return fbo_;
		}

	protected:
		GLuint fbo_;
	};

	typedef shared_ptr<OGLESFrameBuffer> OGLESFrameBufferPtr;
}

#endif			// _OGLESFRAMEBUFFER_HPP
