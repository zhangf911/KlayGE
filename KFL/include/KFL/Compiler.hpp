/**
 * @file Compiler.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef KFL_COMPILER_HPP
#define KFL_COMPILER_HPP

// KlayGE requires vc 14.0+, g++ 7.1+, clang 5.0+, with C++14 or C++17 option on.

// Macros for C++17 core features:
// KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
// KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT

// Macros for C++17 library features:
// KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
// KLAYGE_CXX17_LIBRARY_CHARCONV_SUPPORT
// KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT
// KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
// KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT

// Macros for C++2a library features:
// KLAYGE_CXX2A_LIBRARY_ENDIAN_SUPPORT
// KLAYGE_CXX2A_LIBRARY_FORMAT_SUPPORT
// KLAYGE_CXX2A_LIBRARY_SPAN_SUPPORT

// Macros for TS library features:
// KLAYGE_TS_LIBRARY_FILESYSTEM_SUPPORT

// Detects supported compilers
#if defined(__clang__)
	// Clang++

	#define CLANG_VERSION KFL_JOIN(__clang_major__, __clang_minor__)

	#if defined(_MSC_VER)
		#define KLAYGE_COMPILER_CLANGCL
		#define KLAYGE_COMPILER_NAME clangcl

		#if __cplusplus < 201402L
			#error "-std=c++14 must be turned on."
		#endif

		#if __cplusplus > 201402L
			#define KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
		#endif

		#if CLANG_VERSION >= 90
			#define KLAYGE_COMPILER_VERSION CLANG_VERSION
		#else
			#error "Unsupported compiler version. Please install clang-cl 9.0 or up."
		#endif

		#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
		#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
		#if CLANG_VERSION < 100
			#define KLAYGE_CXX17_LIBRARY_CHARCONV_SUPPORT
		#endif
		#define KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT
		#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
		#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT

		#define KLAYGE_HAS_DECLSPEC
		#define KLAYGE_SYMBOL_EXPORT __declspec(dllexport)
		#define KLAYGE_SYMBOL_IMPORT __declspec(dllimport)
	#else
		#define KLAYGE_COMPILER_CLANG
		#define KLAYGE_COMPILER_NAME clang

		#if __cplusplus < 201703L
			#error "-std=c++1z must be turned on."
		#endif

		#define KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT

		#if defined(__APPLE__)
			#if CLANG_VERSION >= 61
				#define KLAYGE_COMPILER_VERSION CLANG_VERSION
			#else
				#error "Unsupported compiler version. Please install Apple clang++ 6.1 or up."
			#endif

			#if CLANG_VERSION >= 80
				#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
			#endif
			#if CLANG_VERSION >= 90
				#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT
			#endif
			#if CLANG_VERSION >= 100
				#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
				#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
			#endif
		#elif defined(__ANDROID__)
			#if CLANG_VERSION >= 50
				#define KLAYGE_COMPILER_VERSION CLANG_VERSION
			#else
				#error "Unsupported compiler version. Please install clang++ 5.0 (NDK 16) or up."
			#endif

			#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT
		#elif defined(linux) || defined(__linux) || defined(__linux__)
			#if CLANG_VERSION >= 50
				#define KLAYGE_COMPILER_VERSION CLANG_VERSION
			#else
				#error "Unsupported compiler version. Please install clang++ 5.0 or up."
			#endif

			#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
			#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT
			#if CLANG_VERSION >= 70
				#define KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT
				#if __cplusplus > 201703L
					#define KLAYGE_CXX2A_LIBRARY_ENDIAN_SUPPORT
					#define KLAYGE_CXX2A_LIBRARY_SPAN_SUPPORT
				#endif
			#else
				#define KLAYGE_TS_LIBRARY_FILESYSTEM_SUPPORT
			#endif
		#else
			#error "Clang++ on an unknown platform. Only Apple, Android, and Linux are supported."
		#endif

		#define KLAYGE_SYMBOL_EXPORT __attribute__((__visibility__("default")))
		#define KLAYGE_SYMBOL_IMPORT __attribute__((__visibility__("default")))
	#endif

	#define KLAYGE_ATTRIBUTE_NORETURN __attribute__((noreturn))
	#define KLAYGE_BUILTIN_UNREACHABLE __builtin_unreachable()
#elif defined(__GNUC__)
	// GNU C++

	#define KLAYGE_COMPILER_GCC
	#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
		#define KLAYGE_COMPILER_NAME mgw
	#else
		#define KLAYGE_COMPILER_NAME gcc
	#endif

	#include <bits/c++config.h>
	#ifdef _GLIBCXX_USE_FLOAT128
		#undef _GLIBCXX_USE_FLOAT128
	#endif
	#ifdef _GLIBCXX_USE_INT128
		#undef _GLIBCXX_USE_INT128
	#endif

	#define GCC_VERSION KFL_JOIN(__GNUC__, __GNUC_MINOR__)

	#if GCC_VERSION >= 71
		#define KLAYGE_COMPILER_VERSION GCC_VERSION
	#else
		#error "Unsupported compiler version. Please install g++ 7.1 or up."
	#endif

	#if __cplusplus < 201703L
		#error "-std=c++1z must be turned on."
	#endif
	#if !defined(_GLIBCXX_HAS_GTHREADS)
		#error "_GLIBCXX_HAS_GTHREADS must be turned on."
	#endif

	#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
	#define KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
	#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
	#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
	#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT
	#if GCC_VERSION >= 80
		#if !defined(__MINGW32__) || (GCC_VERSION != 81)
			// MinGW-w64 8.1 can't use built-in filesystem due to a bug: https://sourceforge.net/p/mingw-w64/bugs/737/
			#define KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT
		#endif
		#if __cplusplus > 201703L
			#define KLAYGE_CXX2A_LIBRARY_ENDIAN_SUPPORT
		#endif
	#else
		#define KLAYGE_TS_LIBRARY_FILESYSTEM_SUPPORT
	#endif

	#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
		#define KLAYGE_SYMBOL_EXPORT __attribute__((__dllexport__))
		#define KLAYGE_SYMBOL_IMPORT __attribute__((__dllimport__))
	#else
		#define KLAYGE_SYMBOL_EXPORT __attribute__((__visibility__("default")))
		#define KLAYGE_SYMBOL_IMPORT __attribute__((__visibility__("default")))
	#endif

	#define KLAYGE_ATTRIBUTE_NORETURN __attribute__((noreturn))
	#define KLAYGE_BUILTIN_UNREACHABLE __builtin_unreachable()
#elif defined(_MSC_VER)
	// MSVC

	#define KLAYGE_COMPILER_MSVC
	#define KLAYGE_COMPILER_NAME vc

	#define KLAYGE_HAS_DECLSPEC
	#define KLAYGE_SYMBOL_EXPORT __declspec(dllexport)
	#define KLAYGE_SYMBOL_IMPORT __declspec(dllimport)

	#if _MSC_VER >= 1920
		#define KLAYGE_COMPILER_VERSION 142
	#elif _MSC_VER >= 1910
		#define KLAYGE_COMPILER_VERSION 141
	#else
		#error "Unsupported compiler version. Please install vc 14.1 (VS2017) or up."
	#endif

	#if _MSVC_LANG > 201402L
		#if _MSC_VER >= 1911
			#define KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
		#endif
		#define KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
		#define KLAYGE_CXX17_LIBRARY_ANY_SUPPORT
		#if _MSC_VER >= 1914
			#define KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT
		#endif
		#if _MSC_VER >= 1915
			#define KLAYGE_CXX17_LIBRARY_CHARCONV_SUPPORT
		#endif
		#define KLAYGE_CXX17_LIBRARY_OPTIONAL_SUPPORT
		#define KLAYGE_CXX17_LIBRARY_STRING_VIEW_SUPPORT
	#endif
	#if _MSVC_LANG > 201703L
		#if _MSC_VER >= 1922
			#define KLAYGE_CXX2A_LIBRARY_ENDIAN_SUPPORT
		#endif
		#if _MSC_VER >= 1926
			#define KLAYGE_CXX2A_LIBRARY_SPAN_SUPPORT
		#endif
	#endif

	#if !defined(KLAYGE_CXX17_LIBRARY_FILESYSTEM_SUPPORT)
		#define KLAYGE_TS_LIBRARY_FILESYSTEM_SUPPORT
	#endif

	#pragma warning(disable: 4251) // STL classes are not dllexport.
	#pragma warning(disable: 4275) // boost::noncopyable is a non dll-interface class.
	#pragma warning(disable: 4819) // Allow non-ANSI characters.

	#define KLAYGE_ATTRIBUTE_NORETURN __declspec(noreturn)
	#define KLAYGE_BUILTIN_UNREACHABLE __assume(false)
#else
	#error "Unknown compiler. Please install vc, g++, or clang."
#endif

#endif		// KFL_COMPILER_HPP
