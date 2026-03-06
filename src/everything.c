#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"
#if defined(PLATFORM_DESKTOP) || defined(PLATFORM_DESKTOP_SDL)
    #if defined(GRAPHICS_API_OPENGL_ES2)
        #include "glad_gles2.h"       // Required for: OpenGL functionality
        #define glGenVertexArrays glGenVertexArraysOES
        #define glBindVertexArray glBindVertexArrayOES
        #define glDeleteVertexArrays glDeleteVertexArraysOES
        #define GLSL_VERSION            100
    #else
        #if defined(__APPLE__)
            #define GL_SILENCE_DEPRECATION // Silence Opengl API deprecation warnings
            #include <OpenGL/gl3.h>     // OpenGL 3 library for OSX
            #include <OpenGL/gl3ext.h>  // OpenGL 3 extensions library for OSX
        #else
            #include "glad.h"       // Required for: OpenGL functionality
        #endif
        #define GLSL_VERSION            330
    #endif
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


#include "rlgl.h"

#include "points.h"
