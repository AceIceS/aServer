#pragma once

#ifdef RE3D_STATIC
#define _RE3D_API
#endif

#ifndef _RE3D_API

#if defined(_WIN32)

#ifdef RE3D_EXPORTS
#define _RE3D_API __declspec(dllexport)
#else
#define _RE3D_API __declspec(dllimport)
#endif

#pragma warning(disable:4251)

#elif defined(__GNUC__) && __GNUC__ >= 4

#ifdef RE3D_EXPORTS
#define _RE3D_API __attribute__ ((visibility ("default")))
#else
#define _RE3D_API 
#endif

#elif
#define _RE3D_API
#endif

#endif

#define _RE3D_BEG  namespace re3d{
#define _RE3D_END  }

#define _STATIC_BEG  using namespace re3d; namespace { 
#define _STATIC_END  }





