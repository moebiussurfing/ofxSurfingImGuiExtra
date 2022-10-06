//- Common Code For All Addons needed just to ease inclusion as separate files in user code ----------------------
#include <imgui.h>
#undef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui_user.h>
//-----------------------------------------------------------------------------------------------------------------

#include "imgui_helper.h"
#include <errno.h>
#include <mutex>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>	// ShellExecuteA(...) - Shell32.lib
#include <objbase.h>    // CoInitializeEx(...)  - ole32.lib
#include <psapi.h> 
#if IMGUI_RENDERING_DX11
struct IUnknown;
#include <d3d11.h>
#elif IMGUI_RENDERING_DX9
#include <d3d9.h>
#endif
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#define PATH_SEP '\\'
#define PATH_SETTINGS "\\AppData\\Roaming\\"
#else //_WIN32
#include <unistd.h>
#include <stdlib.h> // system
#include <pwd.h>
#include <sys/stat.h>
#include <sys/resource.h>
#define PATH_SEP '/'
#endif //_WIN32

#if defined(__APPLE__)
#define PATH_SETTINGS "/Library/Application Support/"
#include <mach/task.h>
#include <mach/mach_init.h>
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#define PATH_SETTINGS "/.config/"
#endif

#if defined(__EMSCRIPTEN__)
#define IMGUI_IMPL_OPENGL_ES2               // Emscripten    -> GL ES 2, "#version 100"
#endif

#include <vector>
#include <algorithm>

#if IMGUI_VULKAN_SHADER
#include "ImVulkanShader.h"
#endif

#if IMGUI_RENDERING_MATAL
#ifdef IMGUI_OPENGL
#undef IMGUI_OPENGL
#define IMGUI_OPENGL 0
#endif
#endif

#if IMGUI_OPENGL
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#if IMGUI_RENDERING_GL3
#include <imgui_impl_opengl3.h>
#elif IMGUI_RENDERING_GL2
#include <imgui_impl_opengl2.h>
#endif
#endif

#if !defined(alloca)
#	if defined(__GLIBC__) || defined(__sun) || defined(__APPLE__) || defined(__NEWLIB__)
#		include <alloca.h>     // alloca (glibc uses <alloca.h>. Note that Cygwin may have _WIN32 defined, so the order matters here)
#	elif defined(_WIN32)
#       include <malloc.h>     // alloca
#       if !defined(alloca)
#           define alloca _alloca  // for clang with MS Codegen
#       endif //alloca
#   elif defined(__GLIBC__) || defined(__sun)
#       include <alloca.h>     // alloca
#   else
#       include <stdlib.h>     // alloca
#   endif
#endif //alloca

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || \
	defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(_MSC_VER)
	#define stat _stat
	#define stricmp _stricmp
	#include <cctype>
	// this option need c++17
	// Modify By Dicky
		#include <Windows.h>
		#include <dirent_portable.h> // directly open the dirent file attached to this lib
	// Modify By Dicky end
	#define PATH_SEP '\\'
	#ifndef PATH_MAX
		#define PATH_MAX 260
	#endif // PATH_MAX
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__DragonFly__) || \
	defined(__NetBSD__) || defined(__APPLE__) || defined (__EMSCRIPTEN__)
	#define stricmp strcasecmp
	#include <sys/types.h>
	// this option need c++17
	#ifndef USE_STD_FILESYSTEM
		#include <dirent.h> 
	#endif // USE_STD_FILESYSTEM
	#define PATH_SEP '/'
#endif

#if IMGUI_RENDERING_VULKAN
#include <imgui_impl_vulkan.h>
#endif

#if IMGUI_RENDERING_VULKAN
struct ImTexture
{
    ImTextureVk TextureID = nullptr;
    int     Width     = 0;
    int     Height    = 0;
    double  TimeStamp = NAN;
};
#elif IMGUI_RENDERING_DX11
#include <imgui_impl_dx11.h>
struct ImTexture
{
    ID3D11ShaderResourceView * TextureID = nullptr;
    int    Width     = 0;
    int    Height    = 0;
    double  TimeStamp = NAN;
};
#elif IMGUI_RENDERING_DX9
#include <imgui_impl_dx9.h>
struct ImTexture
{
    LPDIRECT3DTEXTURE9 TextureID = nullptr;
    int    Width     = 0;
    int    Height    = 0;
    double  TimeStamp = NAN;
};
#elif IMGUI_OPENGL
struct ImTexture
{
    GLuint TextureID = 0;
    int    Width     = 0;
    int    Height    = 0;
    double  TimeStamp = NAN;
};
#else
struct ImTexture
{
    int    TextureID = -1;
    int    Width     = 0;
    int    Height    = 0;
    double  TimeStamp = NAN;
};
#endif

namespace ImGui {

// ImGui Info
void ShowImGuiInfo()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Text("define: __cplusplus = %d", (int)__cplusplus);
    ImGui::Separator();
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FILE_FUNCTIONS
    ImGui::Text("define: IMGUI_DISABLE_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
    ImGui::Text("define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
    ImGui::Text("define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
    ImGui::Text("define: _WIN32");
#endif
#ifdef _WIN64
    ImGui::Text("define: _WIN64");
#endif
#ifdef __linux__
    ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
    ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
    ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef _MSVC_LANG
    ImGui::Text("define: _MSVC_LANG=%d", (int)_MSVC_LANG);
#endif
#ifdef __MINGW32__
    ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
    ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
    ImGui::Text("define: __GNUC__ = %d", (int)__GNUC__);
#endif
#ifdef __clang_version__
    ImGui::Text("define: __clang_version__ = %s", __clang_version__);
#endif
    ImGui::Separator();
    ImGui::Text("Backend Platform Name: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
    ImGui::Text("Backend Renderer Name: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
#if IMGUI_RENDERING_VULKAN
    ImGui::Text("Backend GPU: %s", ImGui_ImplVulkan_GetDeviceName().c_str());
    ImGui::Text("Backend Vulkan API: %s", ImGui_ImplVulkan_GetApiVersion().c_str());
    ImGui::Text("Backend Vulkan Drv: %s", ImGui_ImplVulkan_GetDrvVersion().c_str());
    ImGui::Separator();
#elif IMGUI_OPENGL
#if IMGUI_RENDERING_GL3
    ImGui::Text("Gl Loader: %s", ImGui_ImplOpenGL3_GLLoaderName().c_str());
    ImGui::Text("GL Version: %s", ImGui_ImplOpenGL3_GetVerion().c_str());
#elif IMGUI_RENDERING_GL2
    ImGui::Text("Gl Loader: %s", ImGui_ImplOpenGL2_GLLoaderName().c_str());
    ImGui::Text("GL Version: %s", ImGui_ImplOpenGL2_GetVerion().c_str());
#endif
#endif
    ImGui::Text("Flash Timer: %.1f", io.ConfigMemoryCompactTimer >= 0.0f ? io.ConfigMemoryCompactTimer : 0);
    ImGui::Separator();
    ImGui::Text("Fonts: %d fonts", io.Fonts->Fonts.Size);
    ImGui::Text("Texure Size: %d x %d", io.Fonts->TexWidth, io.Fonts->TexHeight); 
    ImGui::Text("Display Size: %.2f x %.2f", io.DisplaySize.x, io.DisplaySize.y);
    ImGui::Text("Display Framebuffer Scale: %.2f %.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
}
// Image Load
static std::vector<ImTexture> g_Textures;
std::mutex g_tex_mutex;

void ImGenerateOrUpdateTexture(ImTextureID& imtexid,int width,int height,int channels,size_t offset,const unsigned char* pixels,bool useMipmapsIfPossible,bool wraps,bool wrapt,bool minFilterNearest,bool magFilterNearest,bool is_vulkan)
{
    IM_ASSERT(pixels);
    IM_ASSERT(channels>0 && channels<=4);
#if IMGUI_RENDERING_VULKAN
    if (imtexid == 0)
    {
        // TODO::Dicky Need deal with 3 channels Image(link RGB / BGR)
        g_tex_mutex.lock();
        g_Textures.resize(g_Textures.size() + 1);
        ImTexture& texture = g_Textures.back();
        if (is_vulkan)
            texture.TextureID = (ImTextureVk)ImGui_ImplVulkan_CreateTexture((VkBuffer)pixels, offset, width, height);
        else
            texture.TextureID = (ImTextureVk)ImGui_ImplVulkan_CreateTexture(pixels, width, height);
        if (!texture.TextureID)
        {
            g_Textures.pop_back();
            g_tex_mutex.unlock();
            return;
        }
        texture.Width  = width;
        texture.Height = height;
        imtexid = texture.TextureID;
        g_tex_mutex.unlock();
        return;
    }
    if (is_vulkan)
        ImGui_ImplVulkan_UpdateTexture(imtexid, (VkBuffer)pixels, offset);
    else
        ImGui_ImplVulkan_UpdateTexture(imtexid, pixels);
#elif IMGUI_RENDERING_DX11
    auto textureID = (ID3D11ShaderResourceView *)imtexid;
    if (textureID)
    {
        textureID->Release();
        textureID = nullptr;
    }
    imtexid = ImCreateTexture(pixels, width, height);
#elif IMGUI_RENDERING_DX9
    LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)ImGui_ImplDX9_GetDevice();
    if (!pd3dDevice) return;
    LPDIRECT3DTEXTURE9& texid = reinterpret_cast<LPDIRECT3DTEXTURE9&>(imtexid);
    if (texid==0 && pd3dDevice->CreateTexture(width, height, useMipmapsIfPossible ? 0 : 1, 0, channels==1 ? D3DFMT_A8 : channels==2 ? D3DFMT_A8L8 : channels==3 ? D3DFMT_R8G8B8 : D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texid, NULL) < 0) return;

    D3DLOCKED_RECT tex_locked_rect;
    if (texid->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK) {texid->Release();texid=0;return;}
    if (channels==3 || channels==4) {
        unsigned char* pw;
        const unsigned char* ppxl = pixels;
        for (int y = 0; y < height; y++)    {
            pw = (unsigned char *)tex_locked_rect.pBits + tex_locked_rect.Pitch * y;  // each row has Pitch bytes
            ppxl = &pixels[y*width*channels];
            for( int x = 0; x < width; x++ )
            {
                *pw++ = ppxl[2];
                *pw++ = ppxl[1];
                *pw++ = ppxl[0];
                if (channels==4) *pw++ = ppxl[3];
                ppxl+=channels;
            }
        }
    }
    else {
        for (int y = 0; y < height; y++)    {
            memcpy((unsigned char *)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width * channels) * y, (width * channels));
        }
    }
    texid->UnlockRect(0);
#elif IMGUI_OPENGL
    glEnable(GL_TEXTURE_2D);
    GLint last_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLuint& texid = reinterpret_cast<GLuint&>(imtexid);
    if (texid==0) 
    {
        glGenTextures(1, &texid);
        g_tex_mutex.lock();
        g_Textures.resize(g_Textures.size() + 1);
        ImTexture& texture = g_Textures.back();
        texture.TextureID = texid;
        texture.Width  = width;
        texture.Height = height;
        g_tex_mutex.unlock();
    }

    glBindTexture(GL_TEXTURE_2D, texid);

    GLenum clampEnum = 0x2900;    // 0x2900 -> GL_CLAMP; 0x812F -> GL_CLAMP_TO_EDGE
#   ifndef GL_CLAMP
#       ifdef GL_CLAMP_TO_EDGE
        clampEnum = GL_CLAMP_TO_EDGE;
#       else //GL_CLAMP_TO_EDGE
        clampEnum = 0x812F;
#       endif // GL_CLAMP_TO_EDGE
#   else //GL_CLAMP
    clampEnum = GL_CLAMP;
#   endif //GL_CLAMP

    unsigned char* potImageBuffer = NULL;

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps ? GL_REPEAT : clampEnum);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt ? GL_REPEAT : clampEnum);
    //const GLfloat borderColor[]={0.f,0.f,0.f,1.f};glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);
    if (magFilterNearest) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (useMipmapsIfPossible)   {
#       ifdef NO_IMGUI_OPENGL_GLGENERATEMIPMAP
#           ifndef GL_GENERATE_MIPMAP
#               define GL_GENERATE_MIPMAP 0x8191
#           endif //GL_GENERATE_MIPMAP
        // I guess this is compilable, even if it's not supported:
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);    // This call must be done before glTexImage2D(...) // GL_GENERATE_MIPMAP can't be used with NPOT if there are not supported by the hardware of GL_ARB_texture_non_power_of_two.
#       endif //NO_IMGUI_OPENGL_GLGENERATEMIPMAP
    }
    if (minFilterNearest) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, useMipmapsIfPossible ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST);
    else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, useMipmapsIfPossible ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    GLenum luminanceAlphaEnum = 0x190A; // 0x190A -> GL_LUMINANCE_ALPHA [Note that we're FORCING this definition even if when it's not defined! What should we use for 2 channels?]
    GLenum compressedLuminanceAlphaEnum = 0x84EB; // 0x84EB -> GL_COMPRESSED_LUMINANCE_ALPHA [Note that we're FORCING this definition even if when it's not defined! What should we use for 2 channels?]
#   ifdef GL_LUMINANCE_ALPHA
    luminanceAlphaEnum = GL_LUMINANCE_ALPHA;
#   endif //GL_LUMINANCE_ALPHA
#   ifdef GL_COMPRESSED_LUMINANCE_ALPHA
    compressedLuminanceAlphaEnum = GL_COMPRESSED_LUMINANCE_ALPHA;
#   endif //GL_COMPRESSED_LUMINANCE_ALPHA

#   ifdef IMIMPL_USE_ARB_TEXTURE_SWIZZLE_TO_SAVE_FONT_TEXTURE_MEMORY
    if (&imtexid==&gImImplPrivateParams.fontTex && channels==1) {
        GLint swizzleMask[] = {GL_ONE, GL_ONE, GL_ONE, GL_ALPHA};
        glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        //printf("IMIMPL_USE_ARB_TEXTURE_SWIZZLE_TO_SAVE_FONT_TEXTURE_MEMORY used.\n");
    }
#   endif //IMIMPL_USE_ARB_TEXTURE_SWIZZLE_TO_SAVE_FONT_TEXTURE_MEMORY

    GLenum ifmt = channels==1 ? GL_ALPHA : channels==2 ? luminanceAlphaEnum : channels==3 ? GL_RGB : GL_RGBA;  // channels == 1 could be GL_LUMINANCE, GL_ALPHA, GL_RED ...
    GLenum fmt = ifmt;
#   ifdef IMIMPL_USE_ARB_TEXTURE_COMPRESSION_TO_COMPRESS_FONT_TEXTURE
    if (&imtexid==&gImImplPrivateParams.fontTex)    {
        ifmt = channels==1 ? GL_COMPRESSED_ALPHA : channels==2 ? compressedLuminanceAlphaEnum : channels==3 ? GL_COMPRESSED_RGB : GL_COMPRESSED_RGBA;  // channels == 1 could be GL_COMPRESSED_LUMINANCE, GL_COMPRESSED_ALPHA, GL_COMPRESSED_RED ...
    }
#   endif //IMIMPL_USE_ARB_TEXTURE_COMPRESSION_TO_COMPRESS_FONT_TEXTURE

#if IMGUI_VULKAN_SHADER
    if (is_vulkan)
    {
        // TODO::Dicky need more good method from vk memory to gl
    }
    else
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, ifmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, potImageBuffer ? potImageBuffer : pixels);

#   ifdef IMIMPL_USE_ARB_TEXTURE_COMPRESSION_TO_COMPRESS_FONT_TEXTURE
    if (&imtexid==&gImImplPrivateParams.fontTex)    {
        GLint compressed = GL_FALSE;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compressed);
        if (compressed==GL_FALSE)
            printf("Font texture compressed = %s\n",compressed==GL_TRUE?"true":"false");
    }
#   endif //IMIMPL_USE_ARB_TEXTURE_COMPRESSION_TO_COMPRESS_FONT_TEXTURE

    if (potImageBuffer) {STBI_FREE(potImageBuffer);potImageBuffer=NULL;}

#   ifndef NO_IMGUI_OPENGL_GLGENERATEMIPMAP
    if (useMipmapsIfPossible) glGenerateMipmap(GL_TEXTURE_2D);
#   endif //NO_IMGUI_OPENGL_GLGENERATEMIPMAP
    glBindTexture(GL_TEXTURE_2D, last_texture);
#endif
}

ImTextureID ImCreateTexture(const void* data, int width, int height, double time_stamp)
{
#if IMGUI_RENDERING_VULKAN
    g_tex_mutex.lock();
    g_Textures.resize(g_Textures.size() + 1);
    ImTexture& texture = g_Textures.back();
    texture.TextureID = (ImTextureVk)ImGui_ImplVulkan_CreateTexture(data, width, height);
    if (!texture.TextureID)
    {
        g_Textures.pop_back();
        g_tex_mutex.unlock();
        return (ImTextureID)nullptr;
    }
    texture.Width  = width;
    texture.Height = height;
    texture.TimeStamp = time_stamp;
    g_tex_mutex.unlock();
    return (ImTextureID)texture.TextureID;
#elif IMGUI_RENDERING_DX11
    ID3D11Device* pd3dDevice = (ID3D11Device*)ImGui_ImplDX11_GetDevice();
    if (!pd3dDevice)
        return nullptr;
    g_tex_mutex.lock();
    g_Textures.resize(g_Textures.size() + 1);
    ImTexture& texture = g_Textures.back();

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D *pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    //ID3D11ShaderResourceView * texture = nullptr;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &texture.TextureID);
    pTexture->Release();
    texture.Width  = width;
    texture.Height = height;
    texture.TimeStamp = time_stamp;
    g_tex_mutex.unlock();
    return (ImTextureID)texture.TextureID;
#elif IMGUI_RENDERING_DX9
    LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)ImGui_ImplDX9_GetDevice();
    if (!pd3dDevice)
        return nullptr;
    g_tex_mutex.lock();
    g_Textures.resize(g_Textures.size() + 1);
    ImTexture& texture = g_Textures.back();
    if (pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture.TextureID, NULL) < 0)
    {
        g_tex_mutex.unlock();
        return nullptr;
    }
    D3DLOCKED_RECT tex_locked_rect;
    int bytes_per_pixel = 4;
    if (texture.TextureID->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
    {
        g_tex_mutex.unlock();
        return nullptr;
    }
    for (int y = 0; y < height; y++)
        memcpy((unsigned char*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, (unsigned char* )data + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
    texture.TextureID->UnlockRect(0);
    texture.Width  = width;
    texture.Height = height;
    texture.TimeStamp = time_stamp;
    g_tex_mutex.unlock();
    return (ImTextureID)texture.TextureID;
#elif IMGUI_OPENGL
    g_tex_mutex.lock();
    g_Textures.resize(g_Textures.size() + 1);
    ImTexture& texture = g_Textures.back();

    // Upload texture to graphics system
    GLint last_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGenTextures(1, &texture.TextureID);
    glBindTexture(GL_TEXTURE_2D, texture.TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, last_texture);

    texture.Width  = width;
    texture.Height = height;
    texture.TimeStamp = time_stamp;
    g_tex_mutex.unlock();
    return reinterpret_cast<ImTextureID>(static_cast<intptr_t>(texture.TextureID));
#else
    return nullptr;
#endif
}

static std::vector<ImTexture>::iterator ImFindTexture(ImTextureID texture)
{
#if IMGUI_RENDERING_VULKAN
    auto textureID = reinterpret_cast<ImTextureVk>(texture);
#elif IMGUI_RENDERING_DX11
    auto textureID = (ID3D11ShaderResourceView *)texture;
#elif IMGUI_RENDERING_DX9
    auto textureID = reinterpret_cast<LPDIRECT3DTEXTURE9>(texture);
#elif IMGUI_OPENGL
    auto textureID = static_cast<GLuint>(reinterpret_cast<intptr_t>(texture));
#else
    int textureID = -1;
#endif
    return std::find_if(g_Textures.begin(), g_Textures.end(), [textureID](ImTexture& texture)
    {
        return texture.TextureID == textureID;
    });
}

void ImDestroyTexture(ImTextureID texture)
{
    g_tex_mutex.lock();
    auto textureIt = ImFindTexture(texture);
    if (textureIt == g_Textures.end())
    {
        g_tex_mutex.unlock();
        return;
    }
#if IMGUI_RENDERING_VULKAN
    if (textureIt->TextureID)
    {
        ImGui_ImplVulkan_DestroyTexture(&textureIt->TextureID);
        textureIt->TextureID = nullptr;
    }
#elif IMGUI_RENDERING_DX11
    if (textureIt->TextureID)
    {
        textureIt->TextureID->Release();
        textureIt->TextureID = nullptr;
    }
#elif IMGUI_RENDERING_DX9
    if (textureIt->TextureID)
    {
        textureIt->TextureID->Release();
        textureIt->TextureID = nullptr;
    }
#elif IMGUI_OPENGL
    if (textureIt->TextureID)
    {
        glDeleteTextures(1, &textureIt->TextureID);
        textureIt->TextureID = 0;
    }
#endif
    g_Textures.erase(textureIt);
    g_tex_mutex.unlock();
}

int ImGetTextureWidth(ImTextureID texture)
{
    auto textureIt = ImFindTexture(texture);
    if (textureIt != g_Textures.end())
        return textureIt->Width;
    return 0;
}

int ImGetTextureHeight(ImTextureID texture)
{
    auto textureIt = ImFindTexture(texture);
    if (textureIt != g_Textures.end())
        return textureIt->Height;
    return 0;
}

double ImGetTextureTimeStamp(ImTextureID texture)
{
    auto textureIt = ImFindTexture(texture);
    if (textureIt != g_Textures.end())
        return textureIt->TimeStamp;
    return NAN;
}

ImTextureID ImLoadTexture(const char* path)
{
    int width = 0, height = 0, component = 0;
    if (auto data = stbi_load(path, &width, &height, &component, 4))
    {
        auto texture = ImCreateTexture(data, width, height);
        stbi_image_free(data);
        return texture;
    }
    else
        return nullptr;
}

bool ImTextureToFile(ImTextureID texture, std::string path)
{
    auto textureIt = ImFindTexture(texture);
    if (textureIt == g_Textures.end())
        return false;
#if IMGUI_RENDERING_VULKAN
    if (textureIt->TextureID)
    {
        ImGui_ImplVulkan_SaveTexture(textureIt->TextureID, path);
        return true;
    }
#endif
    return false;
}

void ImMatToTexture(ImGui::ImMat mat, ImTextureID& texture)
{
    if (mat.empty())
        return;
    if (mat.device == ImDataDevice::IM_DD_CPU)
    {
        ImGui::ImGenerateOrUpdateTexture(texture, mat.w, mat.h, mat.c, (const unsigned char *)mat.data);
    }
#if IMGUI_VULKAN_SHADER
    if (mat.device == ImDataDevice::IM_DD_VULKAN)
    {
        ImGui::VkMat vkmat = mat;
#if IMGUI_RENDERING_VULKAN
        ImGui::ImGenerateOrUpdateTexture(texture, vkmat.w, vkmat.h, vkmat.c, vkmat.buffer_offset(), (const unsigned char *)vkmat.buffer());
#else
        ImGui::ImMat cpu_mat;
        ImGui::ImVulkanVkMatToImMat(vkmat, cpu_mat);
        ImGui::ImGenerateOrUpdateTexture(texture, cpu_mat.w, cpu_mat.h, cpu_mat.c, (const unsigned char *)cpu_mat.data);
#endif
    }
#endif
}

bool OpenWithDefaultApplication(const char* url,bool exploreModeForWindowsOS)	
{
#       ifdef _WIN32
            //CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);  // Needed ??? Well, let's suppose the user initializes it himself for now"
            return ((size_t)ShellExecuteA( NULL, exploreModeForWindowsOS ? "explore" : "open", url, "", ".", SW_SHOWNORMAL ))>32;
#       else //_WIN32
            if (exploreModeForWindowsOS) exploreModeForWindowsOS = false;   // No warnings
            char tmp[4096];
            const char* openPrograms[]={"xdg-open","gnome-open"};	// Not sure what can I append here for MacOS

            static int openProgramIndex=-2;
            if (openProgramIndex==-2)   {
                openProgramIndex=-1;
                for (size_t i=0,sz=sizeof(openPrograms)/sizeof(openPrograms[0]);i<sz;i++) {
                    strcpy(tmp,"/usr/bin/");	// Well, we should check all the folders inside $PATH... and we ASSUME that /usr/bin IS inside $PATH (see below)
                    strcat(tmp,openPrograms[i]);
                    FILE* fd = (FILE *)ImFileOpen(tmp,"r");
                    if (fd) {
                        fclose(fd);
                        openProgramIndex = (int)i;
                        //printf(stderr,"found %s\n",tmp);
                        break;
                    }
                }
            }

            // Note that here we strip the prefix "/usr/bin" and just use openPrograms[openProgramsIndex].
            // Also note that if nothing has been found we use "xdg-open" (that might still work if it exists in $PATH, but not in /usr/bin).
            strcpy(tmp,openPrograms[openProgramIndex<0?0:openProgramIndex]);

            strcat(tmp," \"");
            strcat(tmp,url);
            strcat(tmp,"\"");
            return system(tmp)==0;
#       endif //_WIN32
}

void CloseAllPopupMenus()   {
    ImGuiContext& g = *GImGui;
    while (g.OpenPopupStack.size() > 0) g.OpenPopupStack.pop_back();
}

// Posted by Omar in one post. It might turn useful...
bool IsItemActiveLastFrame()    {
    ImGuiContext& g = *GImGui;
    if (g.ActiveIdPreviousFrame)
        return g.ActiveIdPreviousFrame== g.LastItemData.ID;
    return false;
}
bool IsItemJustReleased()   {
    return IsItemActiveLastFrame() && !ImGui::IsItemActive();
}
bool IsItemDisabled()    {
    ImGuiContext& g = *GImGui;
    return (g.CurrentItemFlags & ImGuiItemFlags_Disabled) == ImGuiItemFlags_Disabled;
}

void ShowTooltipOnHoverV(const char* fmt, va_list args)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextV(fmt, args);
        ImGui::EndTooltip();
    }
}

void ShowTooltipOnHover(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ShowTooltipOnHoverV(fmt, args);
    va_end(args);
}

void Debug_DrawItemRect(const ImVec4& col)
{
    auto drawList = ImGui::GetWindowDrawList();
    auto itemMin = ImGui::GetItemRectMin();
    auto itemMax = ImGui::GetItemRectMax();
    drawList->AddRect(itemMin, itemMax, ImColor(col));
}

const ImFont *GetFont(int fntIndex) {return (fntIndex>=0 && fntIndex<ImGui::GetIO().Fonts->Fonts.size()) ? ImGui::GetIO().Fonts->Fonts[fntIndex] : NULL;}
void PushFont(int fntIndex)    {
    IM_ASSERT(fntIndex>=0 && fntIndex<ImGui::GetIO().Fonts->Fonts.size());
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fntIndex]);
}
void TextColoredV(int fntIndex, const ImVec4 &col, const char *fmt, va_list args) {
    ImGui::PushFont(fntIndex);
    ImGui::TextColoredV(col,fmt, args);
    ImGui::PopFont();
}
void TextColored(int fntIndex, const ImVec4 &col, const char *fmt,...)  {
    va_list args;
    va_start(args, fmt);
    TextColoredV(fntIndex,col, fmt, args);
    va_end(args);
}
void TextV(int fntIndex, const char *fmt, va_list args) {
    if (ImGui::GetCurrentWindow()->SkipItems) return;

    ImGuiContext& g = *GImGui;
    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    ImGui::PushFont(fntIndex);
    TextUnformatted(text, text_end);
    ImGui::PopFont();
}
void Text(int fntIndex, const char *fmt,...)    {
    va_list args;
    va_start(args, fmt);
    TextV(fntIndex,fmt, args);
    va_end(args);
}

void TextComplex(const char * str, float scale, ImVec4 text_color, float outline_w, ImVec4 outline_color, ImVec2 shadow_offset, ImVec4 shadow_color) {
    ImGui::SetWindowFontScale(scale);
    ImGui::PushStyleVar(ImGuiStyleVar_TexGlyphOutlineWidth, outline_w);
    ImGui::PushStyleVar(ImGuiStyleVar_TexGlyphShadowOffset, shadow_offset);
    ImGui::PushStyleColor(ImGuiCol_Text, text_color);
    ImGui::PushStyleColor(ImGuiCol_TexGlyphOutline, outline_color);
    ImGui::PushStyleColor(ImGuiCol_TexGlyphShadow, shadow_color);
    ImGui::TextUnformatted(str);
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    ImGui::SetWindowFontScale(1.0);
}

bool GetTexCoordsFromGlyph(unsigned short glyph, ImVec2 &uv0, ImVec2 &uv1) {
    if (!GImGui->Font) return false;
    const ImFontGlyph* g = GImGui->Font->FindGlyph(glyph);
    if (g)  {
        uv0.x = g->U0; uv0.y = g->V0;
        uv1.x = g->U1; uv1.y = g->V1;
        return true;
    }
    return false;
}
float CalcMainMenuHeight()  {
    // Warning: according to https://github.com/ocornut/imgui/issues/252 this approach can fail [Better call ImGui::GetWindowSize().y from inside the menu and store the result somewhere]
    if (GImGui->FontBaseSize>0) return GImGui->FontBaseSize + GImGui->Style.FramePadding.y * 2.0f;
    else {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        ImFont* font = ImGui::GetFont();
        if (!font) {
            if (io.Fonts->Fonts.size()>0) font = io.Fonts->Fonts[0];
            else return (14)+style.FramePadding.y * 2.0f;
        }
        return (io.FontGlobalScale * font->Scale * font->FontSize) + style.FramePadding.y * 2.0f;
    }
}

// These two methods are inspired by imguidock.cpp
void PutInBackground(const char* optionalRootWindowName)  {
    ImGuiWindow* w = optionalRootWindowName ? FindWindowByName(optionalRootWindowName) : GetCurrentWindow();
    if (!w) return;
    ImGuiContext& g = *GImGui;
    if (g.Windows[0] == w) return;
    const int isz = g.Windows.Size;
    for (int i = 0; i < isz; i++)  {
        if (g.Windows[i] == w)  {
            for (int j = i; j > 0; --j) g.Windows[j] = g.Windows[j-1];  // shifts [0,j-1] to [1,j]
            g.Windows[0] = w;
            break;
        }
    }
}
void PutInForeground(const char* optionalRootWindowName)  {
    ImGuiWindow* w = optionalRootWindowName ? FindWindowByName(optionalRootWindowName) : GetCurrentWindow();
    if (!w) return;
    ImGuiContext& g = *GImGui;
    const int iszMinusOne = g.Windows.Size - 1;
    if (iszMinusOne<0 || g.Windows[iszMinusOne] == w) return;
    for (int i = iszMinusOne; i >= 0; --i)  {
        if (g.Windows[i] == w)  {
            for (int j = i; j < iszMinusOne; j++) g.Windows[j] = g.Windows[j+1];  // shifts [i+1,iszMinusOne] to [i,iszMinusOne-1]
            g.Windows[iszMinusOne] = w;
            break;
        }
    }
}

ScopedItemWidth::ScopedItemWidth(float width)
{
    ImGui::PushItemWidth(width);
}

ScopedItemWidth::~ScopedItemWidth()
{
    Release();
}

void ScopedItemWidth::Release()
{
    if (m_IsDone)
        return;

    ImGui::PopItemWidth();

    m_IsDone = true;
}

ScopedDisableItem::ScopedDisableItem(bool disable, float disabledAlpha)
    : m_Disable(disable)
{
    if (!m_Disable)
        return;

    ImGuiContext& g = *GImGui;
    auto wasDisabled = (g.CurrentItemFlags & ImGuiItemFlags_Disabled) == ImGuiItemFlags_Disabled;

    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);

    auto& stale = ImGui::GetStyle();
    m_LastAlpha = stale.Alpha;

    // Don't override alpha if we're already in disabled context.
    if (!wasDisabled)
        stale.Alpha = disabledAlpha;
}

ScopedDisableItem::~ScopedDisableItem()
{
    Release();
}

void ScopedDisableItem::Release()
{
    if (!m_Disable)
        return;

    auto& stale = ImGui::GetStyle();
    stale.Alpha = m_LastAlpha;

    ImGui::PopItemFlag();

    m_Disable = false;
}

ScopedSuspendLayout::ScopedSuspendLayout()
{
    m_Window = ImGui::GetCurrentWindow();
    m_CursorPos = m_Window->DC.CursorPos;
    m_CursorPosPrevLine = m_Window->DC.CursorPosPrevLine;
    m_CursorMaxPos = m_Window->DC.CursorMaxPos;
    m_CurrLineSize = m_Window->DC.CurrLineSize;
    m_PrevLineSize = m_Window->DC.PrevLineSize;
    m_CurrLineTextBaseOffset = m_Window->DC.CurrLineTextBaseOffset;
    m_PrevLineTextBaseOffset = m_Window->DC.PrevLineTextBaseOffset;
}

ScopedSuspendLayout::~ScopedSuspendLayout()
{
    Release();
}

void ScopedSuspendLayout::Release()
{
    if (m_Window == nullptr)
        return;

    m_Window->DC.CursorPos = m_CursorPos;
    m_Window->DC.CursorPosPrevLine = m_CursorPosPrevLine;
    m_Window->DC.CursorMaxPos = m_CursorMaxPos;
    m_Window->DC.CurrLineSize = m_CurrLineSize;
    m_Window->DC.PrevLineSize = m_PrevLineSize;
    m_Window->DC.CurrLineTextBaseOffset = m_CurrLineTextBaseOffset;
    m_Window->DC.PrevLineTextBaseOffset = m_PrevLineTextBaseOffset;

    m_Window = nullptr;
}

ItemBackgroundRenderer::ItemBackgroundRenderer(OnDrawCallback onDrawBackground)
    : m_OnDrawBackground(std::move(onDrawBackground))
{
    m_DrawList = ImGui::GetWindowDrawList();
    m_Splitter.Split(m_DrawList, 2);
    m_Splitter.SetCurrentChannel(m_DrawList, 1);
}

ItemBackgroundRenderer::~ItemBackgroundRenderer()
{
    Commit();
}

void ItemBackgroundRenderer::Commit()
{
    if (m_Splitter._Current == 0)
        return;

    m_Splitter.SetCurrentChannel(m_DrawList, 0);

    if (m_OnDrawBackground)
        m_OnDrawBackground(m_DrawList);

    m_Splitter.Merge(m_DrawList);
}

void ItemBackgroundRenderer::Discard()
{
    if (m_Splitter._Current == 1)
        m_Splitter.Merge(m_DrawList);
}

StorageHandler<MostRecentlyUsedList::Settings> MostRecentlyUsedList::s_Storage;


void MostRecentlyUsedList::Install(ImGuiContext* context)
{
    context->SettingsHandlers.push_back(s_Storage.MakeHandler("MostRecentlyUsedList"));

    s_Storage.ReadLine = [](ImGuiContext*, Settings* entry, const char* line)
    {
        const char* lineEnd = line + strlen(line);

        auto parseListEntry = [lineEnd](const char* line, int& index) -> const char*
        {
            char* indexEnd = nullptr;
            errno = 0;
            index = strtol(line, &indexEnd, 10);
            if (errno == ERANGE)
                return nullptr;
            if (indexEnd >= lineEnd)
                return nullptr;
            if (*indexEnd != '=')
                return nullptr;
            return indexEnd + 1;
        };


        int index = 0;
        if (auto path = parseListEntry(line, index))
        {
            if (static_cast<int>(entry->m_List.size()) <= index)
                entry->m_List.resize(index + 1);
            entry->m_List[index] = path;
        }
    };

    s_Storage.WriteAll = [](ImGuiContext*, ImGuiTextBuffer* out_buf, const StorageHandler<Settings>::Storage& storage)
    {
        for (auto& entry : storage)
        {
            out_buf->appendf("[%s][%s]\n", "MostRecentlyUsedList", entry.first.c_str());
            int index = 0;
            for (auto& value : entry.second->m_List)
                out_buf->appendf("%d=%s\n", index++, value.c_str());
            out_buf->append("\n");
        }
    };
}

MostRecentlyUsedList::MostRecentlyUsedList(const char* id, int capacity /*= 10*/)
    : m_ID(id)
    , m_Capacity(capacity)
    , m_List(s_Storage.FindOrCreate(id)->m_List)
{
}

void MostRecentlyUsedList::Add(const std::string& item)
{
    Add(item.c_str());
}

void MostRecentlyUsedList::Add(const char* item)
{
    auto itemIt = std::find(m_List.begin(), m_List.end(), item);
    if (itemIt != m_List.end())
    {
        // Item is already on the list. Rotate list to move it to the
        // first place.
        std::rotate(m_List.begin(), itemIt, itemIt + 1);
    }
    else
    {
        // Push new item to the back, rotate list to move it to the front,
        // pop back last element if we're over capacity.
        m_List.push_back(item);
        std::rotate(m_List.begin(), m_List.end() - 1, m_List.end());
        if (static_cast<int>(m_List.size()) > m_Capacity)
            m_List.pop_back();
    }

    PushToStorage();

    ImGui::MarkIniSettingsDirty();
}

void MostRecentlyUsedList::Clear()
{
    if (m_List.empty())
        return;

    m_List.resize(0);

    PushToStorage();

    ImGui::MarkIniSettingsDirty();
}

const std::vector<std::string>& MostRecentlyUsedList::GetList() const
{
    return m_List;
}

int MostRecentlyUsedList::Size() const
{
    return static_cast<int>(m_List.size());
}

void MostRecentlyUsedList::PullFromStorage()
{
    if (auto settings = s_Storage.Find(m_ID.c_str()))
        m_List = settings->m_List;
}

void MostRecentlyUsedList::PushToStorage()
{
    auto settings = s_Storage.FindOrCreate(m_ID.c_str());
    settings->m_List = m_List;
}

void Grid::Begin(const char* id, int columns, float width)
{
    Begin(ImGui::GetID(id), columns, width);
}

void Grid::Begin(ImU32 id, int columns, float width)
{
    m_CursorPos = ImGui::GetCursorScreenPos();

    ImGui::PushID(id);
    m_Columns = ImMax(1, columns);
    m_Storage = ImGui::GetStateStorage();

    for (int i = 0; i < columns; ++i)
    {
        ImGui::PushID(ColumnSeed());
        m_Storage->SetFloat(ImGui::GetID("MaximumColumnWidthAcc"), -1.0f);
        ImGui::PopID();
    }

    m_ColumnAlignment = 0.0f;
    m_MinimumWidth = width;

    ImGui::BeginGroup();

    EnterCell(0, 0);
}

void Grid::NextColumn()
{
    LeaveCell();

    int nextColumn = m_Column + 1;
    int nextRow    = 0;
    if (nextColumn > m_Columns)
    {
        nextColumn -= m_Columns;
        nextRow    += 1;
    }

    auto cursorPos = m_CursorPos;
    for (int i = 0; i < nextColumn; ++i)
    {
        ImGui::PushID(ColumnSeed(i));
        auto maximumColumnWidth = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidth"), -1.0f);
        ImGui::PopID();

        if (maximumColumnWidth > 0.0f)
            cursorPos.x += maximumColumnWidth + ImGui::GetStyle().ItemSpacing.x;
    }

    ImGui::SetCursorScreenPos(cursorPos);

    EnterCell(nextColumn, nextRow);
}

void Grid::NextRow()
{
    LeaveCell();

    auto cursorPos = ImGui::GetCursorScreenPos();
    cursorPos.x = m_CursorPos.x;
    for (int i = 0; i < m_Column; ++i)
    {
        ImGui::PushID(ColumnSeed(i));
        auto maximumColumnWidth = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidth"), -1.0f);
        ImGui::PopID();

        if (maximumColumnWidth > 0.0f)
            cursorPos.x += maximumColumnWidth + ImGui::GetStyle().ItemSpacing.x;
    }

    ImGui::SetCursorScreenPos(cursorPos);

    EnterCell(m_Column, m_Row + 1);
}

void Grid::EnterCell(int column, int row)
{
    m_Column = column;
    m_Row    = row;

    ImGui::PushID(ColumnSeed());
    m_MaximumColumnWidthAcc = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidthAcc"), -1.0f);
    auto maximumColumnWidth = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidth"), -1.0f);
    ImGui::PopID();

    ImGui::PushID(Seed());
    auto lastCellWidth = m_Storage->GetFloat(ImGui::GetID("LastCellWidth"), -1.0f);

    if (maximumColumnWidth >= 0.0f && lastCellWidth >= 0.0f)
    {
        auto freeSpace = maximumColumnWidth - lastCellWidth;

        auto offset = ImFloor(m_ColumnAlignment * freeSpace);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
        ImGui::Dummy(ImVec2(offset, 0.0f));
        ImGui::SameLine(0.0f, 0.0f);
        ImGui::PopStyleVar();
    }

    ImGui::BeginGroup();
}

void Grid::LeaveCell()
{
    ImGui::EndGroup();

    auto itemSize = ImGui::GetItemRectSize();
    m_Storage->SetFloat(ImGui::GetID("LastCellWidth"), itemSize.x);
    ImGui::PopID();

    m_MaximumColumnWidthAcc = ImMax(m_MaximumColumnWidthAcc, itemSize.x);
    ImGui::PushID(ColumnSeed());
    m_Storage->SetFloat(ImGui::GetID("MaximumColumnWidthAcc"), m_MaximumColumnWidthAcc);
    ImGui::PopID();
}

void Grid::SetColumnAlignment(float alignment)
{
    alignment = ImClamp(alignment, 0.0f, 1.0f);
    m_ColumnAlignment = alignment;
}

void Grid::End()
{
    LeaveCell();

    ImGui::EndGroup();

    float totalWidth = 0.0f;
    for (int i = 0; i < m_Columns; ++i)
    {
        ImGui::PushID(ColumnSeed(i));
        auto currentMaxCellWidth = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidthAcc"), -1.0f);
        totalWidth += currentMaxCellWidth;
        m_Storage->SetFloat(ImGui::GetID("MaximumColumnWidth"), currentMaxCellWidth);
        ImGui::PopID();
    }

    if (totalWidth < m_MinimumWidth)
    {
        auto spaceToDivide = m_MinimumWidth - totalWidth;
        auto spacePerColumn = ImCeil(spaceToDivide / m_Columns);

        for (int i = 0; i < m_Columns; ++i)
        {
            ImGui::PushID(ColumnSeed(i));
            auto columnWidth = m_Storage->GetFloat(ImGui::GetID("MaximumColumnWidth"), -1.0f);
            columnWidth += spacePerColumn;
            m_Storage->SetFloat(ImGui::GetID("MaximumColumnWidth"), columnWidth);
            ImGui::PopID();

            spaceToDivide -= spacePerColumn;
            if (spaceToDivide < 0)
                spacePerColumn += spaceToDivide;
        }
    }

    ImGui::PopID();
}
} // namespace Imgui

#include <stdio.h>  // FILE
namespace ImGuiHelper   {

static const char* FieldTypeNames[ImGui::FT_COUNT+1] = {"INT","UNSIGNED","FLOAT","DOUBLE","STRING","ENUM","BOOL","COLOR","TEXTLINE","CUSTOM","COUNT"};
static const char* FieldTypeFormats[ImGui::FT_COUNT]={"%d","%u","%f","%f","%s","%d","%d","%f","%s","%s"};
static const char* FieldTypeFormatsWithCustomPrecision[ImGui::FT_COUNT]={"%.*d","%*u","%.*f","%.*f","%*s","%*d","%*d","%.*f","%*s","%*s"};

void Deserializer::clear() {
    if (f_data) ImGui::MemFree(f_data);
    f_data = NULL;f_size=0;
}
bool Deserializer::loadFromFile(const char *filename) {
    clear();
    if (!filename) return false;
    FILE* f;
    if ((f = (FILE *)ImFileOpen(filename, "rt")) == NULL) return false;
    if (fseek(f, 0, SEEK_END))  {
        fclose(f);
        return false;
    }
    const long f_size_signed = ftell(f);
    if (f_size_signed == -1)    {
        fclose(f);
        return false;
    }
    f_size = (size_t)f_size_signed;
    if (fseek(f, 0, SEEK_SET))  {
        fclose(f);
        return false;
    }
    f_data = (char*)ImGui::MemAlloc(f_size+1);
    f_size = fread(f_data, 1, f_size, f); // Text conversion alter read size so let's not be fussy about return value
    fclose(f);
    if (f_size == 0)    {
        clear();
        return false;
    }
    f_data[f_size] = 0;
    ++f_size;
    return true;
}
bool Deserializer::allocate(size_t sizeToAllocate, const char *optionalTextToCopy, size_t optionalTextToCopySize)    {
    clear();
    if (sizeToAllocate==0) return false;
    f_size = sizeToAllocate;
    f_data = (char*)ImGui::MemAlloc(f_size);
    if (!f_data) {clear();return false;}
    if (optionalTextToCopy && optionalTextToCopySize>0) memcpy(f_data,optionalTextToCopy,optionalTextToCopySize>f_size ? f_size:optionalTextToCopySize);
    return true;
}
Deserializer::Deserializer(const char *filename) : f_data(NULL),f_size(0) {
    if (filename) loadFromFile(filename);
}
Deserializer::Deserializer(const char *text, size_t textSizeInBytes) : f_data(NULL),f_size(0) {
    allocate(textSizeInBytes,text,textSizeInBytes);
}

const char* Deserializer::parse(Deserializer::ParseCallback cb, void *userPtr, const char *optionalBufferStart) const {
    if (!cb || !f_data || f_size==0) return NULL;
    //------------------------------------------------
    // Parse file in memory
    char name[128];name[0]='\0';
    char typeName[32];char format[32]="";bool quitParsing = false;
    char charBuffer[sizeof(double)*10];void* voidBuffer = (void*) &charBuffer[0];
    static char textBuffer[2050];
    const char* varName = NULL;int numArrayElements = 0;FieldType ft = ImGui::FT_COUNT;
    const char* buf_end = f_data + f_size-1;
    for (const char* line_start = optionalBufferStart ? optionalBufferStart : f_data; line_start < buf_end; )
    {
        const char* line_end = line_start;
        while (line_end < buf_end && *line_end != '\n' && *line_end != '\r') line_end++;

        if (name[0]=='\0' && line_start[0] == '[' && line_end > line_start && line_end[-1] == ']')
        {
            ImFormatString(name, IM_ARRAYSIZE(name), "%.*s", (int)(line_end-line_start-2), line_start+1);
            //fprintf(stderr,"name: %s\n",name);  // dbg

            // Here we have something like: FLOAT-4:VariableName
            // We have to split into FLOAT 4 VariableName
            varName = NULL;numArrayElements = 0;ft = ImGui::FT_COUNT;format[0]='\0';
            const char* colonCh = strchr(name,':');
            const char* minusCh = strchr(name,'-');
            if (!colonCh) {
                fprintf(stderr,"ImGuiHelper::Deserializer::parse(...) warning (skipping line with no semicolon). name: %s\n",name);  // dbg
                name[0]='\0';
            }
            else {
                ptrdiff_t diff = 0,diff2 = 0;
                if (!minusCh || (minusCh-colonCh)>0)  {diff = (colonCh-name);numArrayElements=1;}
                else {
                    diff = (minusCh-name);
                    diff2 = colonCh-minusCh;
                    if (diff2>1 && diff2<7)    {
                        static char buff[8];
                        strncpy(&buff[0],(const char*) &minusCh[1],diff2);buff[diff2-1]='\0';
                        sscanf(buff,"%d",&numArrayElements);
                        //fprintf(stderr,"WARN: %s\n",buff);
                    }
                    else if (diff>0) numArrayElements = ((char)name[diff+1]-(char)'0');  // TODO: FT_STRING needs multibytes -> rewrite!
                }
                if (diff>0) {
                    const size_t len = (size_t)(diff>31?31:diff);
                    strncpy(typeName,name,len);typeName[len]='\0';

                    for (int t=0;t<=ImGui::FT_COUNT;t++) {
                        if (strcmp(typeName,FieldTypeNames[t])==0)  {
                            ft = (FieldType) t;break;
                        }
                    }
                    varName = ++colonCh;

                    const bool isTextOrCustomType = ft==ImGui::FT_STRING || ft==ImGui::FT_TEXTLINE  || ft==ImGui::FT_CUSTOM;
                    if (ft==ImGui::FT_COUNT || numArrayElements<1 || (numArrayElements>4 && !isTextOrCustomType))   {
                        fprintf(stderr,"ImGuiHelper::Deserializer::parse(...) Error (wrong type detected): line:%s type:%d numArrayElements:%d varName:%s typeName:%s\n",name,(int)ft,numArrayElements,varName,typeName);
                        varName=NULL;
                    }
                    else {

                        if (ft==ImGui::FT_STRING && varName && varName[0]!='\0')  {
                            if (numArrayElements==1 && (!minusCh || (minusCh-colonCh)>0)) {
                                numArrayElements=0;   // NEW! To handle blank strings ""
                            }
                            //Process soon here, as the string can be multiline
                            line_start = ++line_end;
                            //--------------------------------------------------------
                            int cnt = 0;
                            while (line_end < buf_end && cnt++ < numArrayElements-1) ++line_end;
                            textBuffer[0]=textBuffer[2049]='\0';
                            const int maxLen = numArrayElements>0 ? (cnt>2049?2049:cnt) : 0;
                            strncpy(textBuffer,line_start,maxLen+1);
                            textBuffer[maxLen]='\0';
                            quitParsing = cb(ft,numArrayElements,(void*)textBuffer,varName,userPtr);
                            //fprintf(stderr,"Deserializer::parse(...) value:\"%s\" to type:%d numArrayElements:%d varName:%s maxLen:%d\n",textBuffer,(int)ft,numArrayElements,varName,maxLen);  // dbg


                            //else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
                            //--------------------------------------------------------
                            ft = ImGui::FT_COUNT;name[0]='\0';varName=NULL; // mandatory                            

                        }
                        else if (!isTextOrCustomType) {
                            format[0]='\0';
                            for (int t=0;t<numArrayElements;t++) {
                                if (t>0) strcat(format," ");
                                strcat(format,FieldTypeFormats[ft]);
                            }
                            // DBG:
                            //fprintf(stderr,"Deserializer::parse(...) DBG: line:%s type:%d numArrayElements:%d varName:%s format:%s\n",name,(int)ft,numArrayElements,varName,format);  // dbg
                        }
                    }
                }
            }
        }
        else if (varName && varName[0]!='\0')
        {
            switch (ft) {
            case ImGui::FT_FLOAT:
            case ImGui::FT_COLOR:
            {
                float* p = (float*) voidBuffer;
                if ( (numArrayElements==1 && sscanf(line_start, format, p)==numArrayElements) ||
                     (numArrayElements==2 && sscanf(line_start, format, &p[0],&p[1])==numArrayElements) ||
                     (numArrayElements==3 && sscanf(line_start, format, &p[0],&p[1],&p[2])==numArrayElements) ||
                     (numArrayElements==4 && sscanf(line_start, format, &p[0],&p[1],&p[2],&p[3])==numArrayElements))
                     quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);
                else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            }
            break;
            case ImGui::FT_DOUBLE:  {
                double* p = (double*) voidBuffer;
                if ( (numArrayElements==1 && sscanf(line_start, format, p)==numArrayElements) ||
                     (numArrayElements==2 && sscanf(line_start, format, &p[0],&p[1])==numArrayElements) ||
                     (numArrayElements==3 && sscanf(line_start, format, &p[0],&p[1],&p[2])==numArrayElements) ||
                     (numArrayElements==4 && sscanf(line_start, format, &p[0],&p[1],&p[2],&p[3])==numArrayElements))
                     quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);
                else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            }
            break;
            case ImGui::FT_INT:
            case ImGui::FT_ENUM:
            {
                int* p = (int*) voidBuffer;
                if ( (numArrayElements==1 && sscanf(line_start, format, p)==numArrayElements) ||
                     (numArrayElements==2 && sscanf(line_start, format, &p[0],&p[1])==numArrayElements) ||
                     (numArrayElements==3 && sscanf(line_start, format, &p[0],&p[1],&p[2])==numArrayElements) ||
                     (numArrayElements==4 && sscanf(line_start, format, &p[0],&p[1],&p[2],&p[3])==numArrayElements))
                     quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);
                else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            }
            break;
            case ImGui::FT_BOOL:
            {
                bool* p = (bool*) voidBuffer;
                int tmp[4];
                if ( (numArrayElements==1 && sscanf(line_start, format, &tmp[0])==numArrayElements) ||
                     (numArrayElements==2 && sscanf(line_start, format, &tmp[0],&tmp[1])==numArrayElements) ||
                     (numArrayElements==3 && sscanf(line_start, format, &tmp[0],&tmp[1],&tmp[2])==numArrayElements) ||
                     (numArrayElements==4 && sscanf(line_start, format, &tmp[0],&tmp[1],&tmp[2],&tmp[3])==numArrayElements))    {
                     for (int i=0;i<numArrayElements;i++) p[i] = tmp[i];
                     quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);
                }
                else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            }
            break;
            case ImGui::FT_UNSIGNED:  {
                unsigned* p = (unsigned*) voidBuffer;
                if ( (numArrayElements==1 && sscanf(line_start, format, p)==numArrayElements) ||
                     (numArrayElements==2 && sscanf(line_start, format, &p[0],&p[1])==numArrayElements) ||
                     (numArrayElements==3 && sscanf(line_start, format, &p[0],&p[1],&p[2])==numArrayElements) ||
                     (numArrayElements==4 && sscanf(line_start, format, &p[0],&p[1],&p[2],&p[3])==numArrayElements))
                     quitParsing = cb(ft,numArrayElements,voidBuffer,varName,userPtr);
                else fprintf(stderr,"Deserializer::parse(...) Error converting value:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            }
            break;
            case ImGui::FT_CUSTOM:
            case ImGui::FT_TEXTLINE:
            {
                // A similiar code can be used to parse "numArrayElements" line of text
                for (int i=0;i<numArrayElements;i++)    {
                    textBuffer[0]=textBuffer[2049]='\0';
                    const int maxLen = (line_end-line_start)>2049?2049:(line_end-line_start);
                    if (maxLen<=0) break;
                    strncpy(textBuffer,line_start,maxLen+1);textBuffer[maxLen]='\0';
                    quitParsing = cb(ft,i,(void*)textBuffer,varName,userPtr);

                    //fprintf(stderr,"%d) \"%s\"\n",i,textBuffer);  // Dbg

                    if (quitParsing) break;
                    line_start = line_end+1;
                    line_end = line_start;
                    if (line_end == buf_end) break;
                    while (line_end < buf_end && *line_end != '\n' && *line_end != '\r') line_end++;
                }
            }
            break;
            default:
            fprintf(stderr,"Deserializer::parse(...) Warning missing value type:\"%s\" to type:%d numArrayElements:%d varName:%s\n",line_start,(int)ft,numArrayElements,varName);  // dbg
            break;
            }
            //---------------------------------------------------------------------------------
            name[0]='\0';varName=NULL; // mandatory
        }

        line_start = line_end+1;

        if (quitParsing) return line_start;
    }

    //------------------------------------------------
    return buf_end;
}

bool GetFileContent(const char *filePath, ImVector<char> &contentOut, bool clearContentOutBeforeUsage, const char *modes, bool appendTrailingZeroIfModesIsNotBinary)   {
    ImVector<char>& f_data = contentOut;
    if (clearContentOutBeforeUsage) f_data.clear();
//----------------------------------------------------
    if (!filePath) return false;
    const bool appendTrailingZero = appendTrailingZeroIfModesIsNotBinary && modes && strlen(modes)>0 && modes[strlen(modes)-1]!='b';
    FILE* f;
    if ((f = (FILE *)ImFileOpen(filePath, modes)) == NULL) return false;
    if (fseek(f, 0, SEEK_END))  {
        fclose(f);
        return false;
    }
    const long f_size_signed = ftell(f);
    if (f_size_signed == -1)    {
        fclose(f);
        return false;
    }
    size_t f_size = (size_t)f_size_signed;
    if (fseek(f, 0, SEEK_SET))  {
        fclose(f);
        return false;
    }
    f_data.resize(f_size+(appendTrailingZero?1:0));
    const size_t f_size_read = f_size>0 ? fread(&f_data[0], 1, f_size, f) : 0;
    fclose(f);
    if (f_size_read == 0 || f_size_read!=f_size)    return false;
    if (appendTrailingZero) f_data[f_size] = '\0';
//----------------------------------------------------
    return true;
}

bool SetFileContent(const char *filePath, const unsigned char* content, int contentSize,const char* modes)	{
    if (!filePath || !content) return false;
    FILE* f;
    if ((f = (FILE *)ImFileOpen(filePath, modes)) == NULL) return false;
    fwrite(content, contentSize, 1, f);
    fclose(f);f=NULL;
    return true;
}

class ISerializable {
public:
    ISerializable() {}
    virtual ~ISerializable() {}
    virtual void close()=0;
    virtual bool isValid() const=0;
    virtual int print(const char* fmt, ...)=0;
    virtual int getTypeID() const=0;
};
class SerializeToFile : public ISerializable {
public:
    SerializeToFile(const char* filename) : f(NULL) {
        saveToFile(filename);
    }
    SerializeToFile() : f(NULL) {}
    ~SerializeToFile() {close();}
    bool saveToFile(const char* filename) {
        close();
        f = (FILE *)ImFileOpen(filename,"w");
        return (f);
    }
    void close() {if (f) fclose(f);f=NULL;}
    bool isValid() const {return (f);}
    int print(const char* fmt, ...) {
        va_list args;va_start(args, fmt);
        const int rv = vfprintf(f,fmt,args);
        va_end(args);
        return rv;
    }
    int getTypeID() const {return 0;}
protected:
    FILE* f;
};
class SerializeToBuffer : public ISerializable {
public:
    SerializeToBuffer(int initialCapacity=2048) {b.reserve(initialCapacity);b.resize(1);b[0]='\0';}
    ~SerializeToBuffer() {close();}
    bool saveToFile(const char* filename) {
        if (!isValid()) return false;
        return SetFileContent(filename,(unsigned char*)&b[0],b.size(),"w");
    }
    void close() {b.clear();ImVector<char> o;b.swap(o);b.resize(1);b[0]='\0';}
    bool isValid() const {return b.size()>0;}
    int print(const char* fmt, ...) {
        va_list args,args2;
        va_start(args, fmt);
        va_copy(args2,args);                                    // since C99 (MANDATORY! otherwise we must reuse va_start(args2,fmt): slow)
        const int additionalSize = vsnprintf(NULL,0,fmt,args);  // since C99
        va_end(args);
        //IM_ASSERT(additionalSize>0);

        const int startSz = b.size();
        b.resize(startSz+additionalSize);
        const int rv = vsprintf(&b[startSz-1],fmt,args2);
        va_end(args2);
        //IM_ASSERT(additionalSize==rv);
        //IM_ASSERT(v[startSz+additionalSize-1]=='\0');

        return rv;
    }
    inline const char* getBuffer() const {return b.size()>0 ? &b[0] : NULL;}
    inline int getBufferSize() const {return b.size();}
    int getTypeID() const {return 1;}
protected:
    ImVector<char> b;
};
const char* Serializer::getBuffer() const   {
    return (f && f->getTypeID()==1 && f->isValid()) ? static_cast<SerializeToBuffer*>(f)->getBuffer() : NULL;
}
int Serializer::getBufferSize() const {
    return (f && f->getTypeID()==1 && f->isValid()) ? static_cast<SerializeToBuffer*>(f)->getBufferSize() : 0;
}
bool Serializer::WriteBufferToFile(const char* filename,const char* buffer,int bufferSize)   {
    if (!buffer) return false;
    FILE* f = (FILE *)ImFileOpen(filename,"w");
    if (!f) return false;
    fwrite((void*) buffer,bufferSize,1,f);
    fclose(f);
    return true;
}

void Serializer::clear() {if (f) {f->close();}}
Serializer::Serializer(const char *filename) {
    f=(SerializeToFile*) ImGui::MemAlloc(sizeof(SerializeToFile));
    IM_PLACEMENT_NEW((SerializeToFile*)f) SerializeToFile(filename);
}
Serializer::Serializer(int memoryBufferCapacity) {
    f=(SerializeToBuffer*) ImGui::MemAlloc(sizeof(SerializeToBuffer));
    IM_PLACEMENT_NEW((SerializeToBuffer*)f) SerializeToBuffer(memoryBufferCapacity);
}
Serializer::~Serializer() {
    if (f) {
        f->~ISerializable();
        ImGui::MemFree(f);
        f=NULL;
    }
}
template <typename T> inline static bool SaveTemplate(ISerializable* f,FieldType ft, const T* pValue, const char* name, int numArrayElements=1, int prec=-1)   {
    if (!f || ft==ImGui::FT_COUNT  || ft==ImGui::FT_CUSTOM || numArrayElements<0 || numArrayElements>4 || !pValue || !name || name[0]=='\0') return false;
    // name
    f->print( "[%s",FieldTypeNames[ft]);
    if (numArrayElements==0) numArrayElements=1;
    if (numArrayElements>1) f->print( "-%d",numArrayElements);
    f->print( ":%s]\n",name);
    // value
    const char* precision = FieldTypeFormatsWithCustomPrecision[ft];
    for (int t=0;t<numArrayElements;t++) {
        if (t>0) f->print(" ");
        f->print(precision,prec,pValue[t]);
    }
    f->print("\n\n");
    return true;
}
bool Serializer::save(FieldType ft, const float* pValue, const char* name, int numArrayElements,  int prec)   {
    IM_ASSERT(ft==ImGui::FT_FLOAT || ft==ImGui::FT_COLOR);
    return SaveTemplate<float>(f,ft,pValue,name,numArrayElements,prec);
}
bool Serializer::save(const double* pValue,const char* name,int numArrayElements, int prec)   {
    return SaveTemplate<double>(f,ImGui::FT_DOUBLE,pValue,name,numArrayElements,prec);
}
bool Serializer::save(const bool* pValue,const char* name,int numArrayElements)   {
    if (!pValue || numArrayElements<0 || numArrayElements>4) return false;
    static int tmp[4];
    for (int i=0;i<numArrayElements;i++) tmp[i] = pValue[i] ? 1 : 0;
    return SaveTemplate<int>(f,ImGui::FT_BOOL,tmp,name,numArrayElements);
}
bool Serializer::save(FieldType ft,const int* pValue,const char* name,int numArrayElements, int prec) {
    IM_ASSERT(ft==ImGui::FT_INT || ft==ImGui::FT_BOOL || ft==ImGui::FT_ENUM);
    if (prec==0) prec=-1;
    return SaveTemplate<int>(f,ft,pValue,name,numArrayElements,prec);
}
bool Serializer::save(const unsigned* pValue,const char* name,int numArrayElements, int prec) {
    if (prec==0) prec=-1;
    return SaveTemplate<unsigned>(f,ImGui::FT_UNSIGNED,pValue,name,numArrayElements,prec);
}
bool Serializer::save(const char* pValue,const char* name,int pValueSize)    {
    FieldType ft = ImGui::FT_STRING;
    int numArrayElements = pValueSize;
    if (!f || ft==ImGui::FT_COUNT || !pValue || !name || name[0]=='\0') return false;
    numArrayElements = pValueSize;
    pValueSize=(int)strlen(pValue);if (numArrayElements>pValueSize || numArrayElements<=0) numArrayElements=pValueSize;
    if (numArrayElements<0) numArrayElements=0;

    // name
    f->print( "[%s",FieldTypeNames[ft]);
    if (numArrayElements==0) numArrayElements=1;
    if (numArrayElements>1) f->print( "-%d",numArrayElements);
    f->print( ":%s]\n",name);
    // value
    f->print("%s\n\n",pValue);
    return true;
}
bool Serializer::saveTextLines(const char* pValue,const char* name)   {
    FieldType ft = ImGui::FT_TEXTLINE;
    if (!f || ft==ImGui::FT_COUNT || !pValue || !name || name[0]=='\0') return false;
    const char *tmp;const char *start = pValue;
    int left = strlen(pValue);int numArrayElements =0;  // numLines
    bool endsWithNewLine = pValue[left-1]=='\n';
    while ((tmp=strchr(start, '\n'))) {
        ++numArrayElements;
        left-=tmp-start-1;
        start = ++tmp;  // to skip '\n'
    }
    if (left>0) ++numArrayElements;
    if (numArrayElements==0) return false;

    // name
    f->print( "[%s",FieldTypeNames[ft]);
    if (numArrayElements==0) numArrayElements=1;
    if (numArrayElements>1) f->print( "-%d",numArrayElements);
    f->print( ":%s]\n",name);
    // value
    f->print("%s",pValue);
    if (!endsWithNewLine)  f->print("\n");
    f->print("\n");
    return true;
}
bool Serializer::saveTextLines(int numValues,bool (*items_getter)(void* data, int idx, const char** out_text),void* data,const char* name)  {
    FieldType ft = ImGui::FT_TEXTLINE;
    if (!items_getter || !f || ft==ImGui::FT_COUNT || numValues<=0 || !name || name[0]=='\0') return false;
    int numArrayElements =numValues;  // numLines

    // name
    f->print( "[%s",FieldTypeNames[ft]);
    if (numArrayElements==0) numArrayElements=1;
    if (numArrayElements>1) f->print( "-%d",numArrayElements);
    f->print( ":%s]\n",name);

    // value
    const char* text=NULL;int len=0;
    for (int i=0;i<numArrayElements;i++)    {
        if (items_getter(data,i,&text)) {
            f->print("%s",text);
            if (len<=0 || text[len-1]!='\n')  f->print("\n");
        }
        else f->print("\n");
    }
    f->print("\n");
    return true;
}
bool Serializer::saveCustomFieldTypeHeader(const char* name, int numTextLines) {
    // name
    f->print( "[%s",FieldTypeNames[ImGui::FT_CUSTOM]);
    if (numTextLines==0) numTextLines=1;
    if (numTextLines>1) f->print( "-%d",numTextLines);
    f->print( ":%s]\n",name);
    return true;
}

void StringSet(char *&destText, const char *text, bool allowNullDestText) {
    if (destText) {ImGui::MemFree(destText);destText=NULL;}
    const char e = '\0';
    if (!text && !allowNullDestText) text=&e;
    if (text)  {
        const int sz = strlen(text);
        destText = (char*) ImGui::MemAlloc(sz+1);strcpy(destText,text);
    }
}
void StringAppend(char *&destText, const char *textToAppend, bool allowNullDestText, bool prependLineFeedIfDestTextIsNotEmpty, bool mustAppendLineFeed) {
    const int textToAppendSz = textToAppend ? strlen(textToAppend) : 0;
    if (textToAppendSz==0) {
        if (!destText && !allowNullDestText) {destText = (char*) ImGui::MemAlloc(1);strcpy(destText,"");}
        return;
    }
    const int destTextSz = destText ? strlen(destText) : 0;
    const bool mustPrependLF = prependLineFeedIfDestTextIsNotEmpty && (destTextSz>0);
    const bool mustAppendLF = mustAppendLineFeed;// && (destText);
    const int totalTextSz = textToAppendSz + destTextSz + (mustPrependLF?1:0) + (mustAppendLF?1:0);
    ImVector<char> totalText;totalText.resize(totalTextSz+1);
    totalText[0]='\0';
    if (destText) {
        strcpy(&totalText[0],destText);
        ImGui::MemFree(destText);destText=NULL;
    }
    if (mustPrependLF) strcat(&totalText[0],"\n");
    strcat(&totalText[0],textToAppend);
    if (mustAppendLF) strcat(&totalText[0],"\n");
    destText = (char*) ImGui::MemAlloc(totalTextSz+1);strcpy(destText,&totalText[0]);
}

int StringAppend(ImVector<char>& v,const char* fmt, ...) {
    IM_ASSERT(v.size()>0 && v[v.size()-1]=='\0');
    va_list args,args2;

    va_start(args, fmt);
    va_copy(args2,args);                                    // since C99 (MANDATORY! otherwise we must reuse va_start(args2,fmt): slow)
    const int additionalSize = vsnprintf(NULL,0,fmt,args);  // since C99
    va_end(args);

    const int startSz = v.size();
    v.resize(startSz+additionalSize);
    const int rv = vsprintf(&v[startSz-1],fmt,args2);
    va_end(args2);

    return rv;
}

// ImGui Theme Editor
static ImVec4 base = ImVec4(0.502f, 0.075f, 0.256f, 1.0f);
static ImVec4 bg   = ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
static ImVec4 text = ImVec4(0.860f, 0.930f, 0.890f, 1.0f);
static float high_val = 0.8f;
static float mid_val = 0.5f;
static float low_val = 0.3f;
static float window_offset = -0.2f;
inline ImVec4 make_high(float alpha) 
{
    ImVec4 res(0, 0, 0, alpha);
    ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
    res.z = high_val;
    ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
    return res;
}

inline ImVec4 make_mid(float alpha) 
{
    ImVec4 res(0, 0, 0, alpha);
    ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
    res.z = mid_val;
    ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
    return res;
}

inline ImVec4 make_low(float alpha) 
{
    ImVec4 res(0, 0, 0, alpha);
    ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
    res.z = low_val;
    ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
    return res;
}

inline ImVec4 make_bg(float alpha, float offset = 0.f) 
{
    ImVec4 res(0, 0, 0, alpha);
    ImGui::ColorConvertRGBtoHSV(bg.x, bg.y, bg.z, res.x, res.y, res.z);
    res.z += offset;
    ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
    return res;
}

inline ImVec4 make_text(float alpha) 
{
    return ImVec4(text.x, text.y, text.z, alpha);
}

void ThemeGenerator(const char* name, bool* p_open, ImGuiWindowFlags flags) 
{
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin(name, p_open, flags);
    ImGui::ColorEdit3("base", (float*) &base, ImGuiColorEditFlags_PickerHueWheel);
    ImGui::ColorEdit3("bg", (float*) &bg, ImGuiColorEditFlags_PickerHueWheel);
    ImGui::ColorEdit3("text", (float*) &text, ImGuiColorEditFlags_PickerHueWheel);
    ImGui::SliderFloat("high", &high_val, 0, 1);
    ImGui::SliderFloat("mid", &mid_val, 0, 1);
    ImGui::SliderFloat("low", &low_val, 0, 1);
    ImGui::SliderFloat("window", &window_offset, -0.4f, 0.4f);

    ImGuiStyle &style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Text]                  = make_text(0.78f);
    style.Colors[ImGuiCol_TextDisabled]          = make_text(0.28f);
    style.Colors[ImGuiCol_WindowBg]              = make_bg(1.00f, window_offset);
    style.Colors[ImGuiCol_ChildBg]               = make_bg(0.58f);
    style.Colors[ImGuiCol_PopupBg]               = make_bg(0.9f);
    style.Colors[ImGuiCol_Border]                = make_bg(0.6f, -0.05f);
    style.Colors[ImGuiCol_BorderShadow]          = make_bg(0.0f, 0.0f);
    style.Colors[ImGuiCol_FrameBg]               = make_bg(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = make_mid(0.78f);
    style.Colors[ImGuiCol_FrameBgActive]         = make_mid(1.00f);
    style.Colors[ImGuiCol_TitleBg]               = make_low(1.00f);
    style.Colors[ImGuiCol_TitleBgActive]         = make_high(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = make_bg(0.75f);
    style.Colors[ImGuiCol_MenuBarBg]             = make_bg(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]           = make_bg(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = make_low(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = make_mid(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = make_mid(1.00f);
    style.Colors[ImGuiCol_CheckMark]             = make_high(1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = make_bg(1.0f, .1f);
    style.Colors[ImGuiCol_SliderGrabActive]      = make_high(1.0f);
    style.Colors[ImGuiCol_Button]                = make_bg(1.0f, .2f);
    style.Colors[ImGuiCol_ButtonHovered]         = make_mid(1.00f);
    style.Colors[ImGuiCol_ButtonActive]          = make_high(1.00f);
    style.Colors[ImGuiCol_Header]                = make_mid(0.76f);
    style.Colors[ImGuiCol_HeaderHovered]         = make_mid(0.86f);
    style.Colors[ImGuiCol_HeaderActive]          = make_high(1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = make_mid(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]      = make_mid(1.00f);
    style.Colors[ImGuiCol_PlotLines]             = make_text(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = make_mid(1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = make_text(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = make_mid(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = make_mid(0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = make_bg(0.73f);
    style.Colors[ImGuiCol_Tab]                   = make_bg(0.40f);
    style.Colors[ImGuiCol_TabHovered]            = make_high(1.00f);
    style.Colors[ImGuiCol_TabActive]             = make_mid(1.00f);
    style.Colors[ImGuiCol_TabUnfocused]          = make_bg(0.40f);
    style.Colors[ImGuiCol_TabUnfocusedActive]    = make_bg(0.70f);
    //style.Colors[ImGuiCol_PlotLines]             = 
    //style.Colors[ImGuiCol_PlotLinesHovered]      = 
    //style.Colors[ImGuiCol_PlotHistogram]         = 
    //style.Colors[ImGuiCol_PlotHistogramHovered]  = 
    //style.Colors[ImGuiCol_TableHeaderBg]         = 
    //style.Colors[ImGuiCol_TableBorderStrong]     = 
    //style.Colors[ImGuiCol_TableBorderLight]      = 
    //style.Colors[ImGuiCol_TableRowBg]            = 
    //style.Colors[ImGuiCol_TableRowBgAlt]         = 
    //style.Colors[ImGuiCol_TextSelectedBg]        = 
    //style.Colors[ImGuiCol_DragDropTarget]        = 
    //style.Colors[ImGuiCol_NavHighlight]          = 
    //style.Colors[ImGuiCol_NavWindowingHighlight] =
    //style.Colors[ImGuiCol_NavWindowingDimBg]     = 
    //style.Colors[ImGuiCol_ModalWindowDimBg]      = 
    //style.Colors[ImGuiCol_TexGlyphShadow]        = 
    //style.Colors[ImGuiCol_TexGlyphOutline]       = 

    if (ImGui::Button("Export")) 
    {
        ImGui::LogToTTY();
        ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;\n");
        for (int i = 0; i < ImGuiCol_COUNT; i++) 
        {
            const ImVec4& col = style.Colors[i];
            const char* name = ImGui::GetStyleColorName(i);
            ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);\n",
                            name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
        }
        ImGui::LogFinish();
    }
    ImGui::End();
}

// System Toolkit
bool file_exists(const std::string& path)
{
    if (path.empty())
        return false;

    return access(path.c_str(), R_OK) == 0;
}

std::string path_filename(const std::string& path)
{
    return path.substr(0, path.find_last_of(PATH_SEP) + 1);
}

std::string date_time_string()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    tm* datetime = localtime(&t);

    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << std::to_string(datetime->tm_year + 1900);
    oss << std::setw(2) << std::setfill('0') << std::to_string(datetime->tm_mon + 1);
    oss << std::setw(2) << std::setfill('0') << std::to_string(datetime->tm_mday );
    oss << std::setw(2) << std::setfill('0') << std::to_string(datetime->tm_hour );
    oss << std::setw(2) << std::setfill('0') << std::to_string(datetime->tm_min );
    oss << std::setw(2) << std::setfill('0') << std::to_string(datetime->tm_sec );
    oss << std::setw(3) << std::setfill('0') << std::to_string(millis);

    // fixed length string (17 chars) YYYYMMDDHHmmssiii
    return oss.str();
}

std::string username()
{
    std::string userName;
#ifdef _WIN32
    CHAR cUserNameBuffer[256];
    DWORD dwUserNameSize = 256;
    if(GetUserName(cUserNameBuffer, &dwUserNameSize))
    {
        userName = std::string(cUserNameBuffer);
    }
#else
    // try the system user info
    struct passwd* pwd = getpwuid(getuid());
    if (pwd)
        userName = std::string(pwd->pw_name);
    else
        // try the $USER environment variable
        userName = std::string(getenv("USER"));
#endif
    return userName;
}

std::string home_path()
{
    std::string homePath;
#ifdef _WIN32
    std::string homeDrive = std::string(getenv("HOMEDRIVE"));
    homePath = homeDrive + std::string(getenv("HOMEPATH"));
#else
    // try the system user info
    // NB: avoids depending on changes of the $HOME env. variable
    struct passwd* pwd = getpwuid(getuid());
    if (pwd)
        homePath = std::string(pwd->pw_dir);
    else
        // try the $HOME environment variable
        homePath = std::string(getenv("HOME"));
#endif
    return homePath + PATH_SEP;
}

bool create_directory(const std::string& path)
{
#ifdef _WIN32
    return !mkdir(path.c_str()) || errno == EEXIST;
#else
    return !mkdir(path.c_str(), 0755) || errno == EEXIST;
#endif
}

std::string settings_path(std::string app_name)
{
    // start from home folder
    // NB: use the env.variable $HOME to allow system to specify
    // another directory (e.g. inside a snap)
#ifdef _WIN32
    std::string home(getenv("HOMEPATH"));
#else
    std::string home(getenv("HOME"));
#endif
    // 2. try to access user settings folder
    std::string settingspath = home + PATH_SETTINGS;
    if (file_exists(settingspath)) {
        // good, we have a place to put the settings file
        // settings should be in 'app_name' subfolder
        settingspath += app_name;

        // 3. create the vmix subfolder in settings folder if not existing already
        if ( !file_exists(settingspath)) {
            if ( !create_directory(settingspath) )
                // fallback to home if settings path cannot be created
                settingspath = home;
        }
        return settingspath + PATH_SEP;
    }
    else {
        // fallback to home if settings path does not exists
        return home + PATH_SEP;
    }
}

std::string temp_path()
{
    std::string temp;
#ifdef _WIN32
    const char *tmpdir = getenv("TEMP");
#else
    const char *tmpdir = getenv("TMPDIR");
#endif
    if (tmpdir)
        temp = std::string(tmpdir);
    else
        temp = std::string( P_tmpdir );

    temp += PATH_SEP;
    return temp;
}

std::string cwd_path()
{
    char mCwdPath[PATH_MAX] = {0};

    if (getcwd(mCwdPath, sizeof(mCwdPath)) != NULL)
        return std::string(mCwdPath) + PATH_SEP;
    else
        return std::string();
}

std::string exec_path()
{
    std::string path = std::string(); 
    // Preallocate PATH_MAX (e.g., 4096) characters and hope the executable path isn't longer (including null byte)
    char exePath[PATH_MAX];
#if defined(__linux__)
    // Return written bytes, indicating if memory was sufficient
    int len = readlink("/proc/self/exe", exePath, PATH_MAX);
    if (len <= 0 || len == PATH_MAX) // memory not sufficient or general error occured
        return path;
    path = path_filename(std::string(exePath));
#elif defined(_WIN32)
    // Return written bytes, indicating if memory was sufficient
    unsigned int len = GetModuleFileNameA(GetModuleHandleA(0x0), exePath, MAX_PATH);
    if (len == 0) // memory not sufficient or general error occured
        return path;
    path = path_filename(std::string(exePath));
#elif defined(__APPLE__)
    unsigned int len = (unsigned int)PATH_MAX;
    // Obtain executable path to canonical path, return zero on success
    if (_NSGetExecutablePath(exePath, &len) == 0)
    {
        // Convert executable path to canonical path, return null pointer on error
        char * realPath = realpath(exePath, 0x0);
        if (realPath == 0x0)
            return path;
        path = path_filename(std::string(realPath));
        free(realPath);
    }
    else // len is initialized with the required number of bytes (including zero byte)
    {
        char * intermediatePath = (char *)malloc(sizeof(char) * len);
        // Convert executable path to canonical path, return null pointer on error
        if (_NSGetExecutablePath(intermediatePath, &len) != 0)
        {
            free(intermediatePath);
            return path;
        }
        char * realPath = realpath(intermediatePath, 0x0);
        free(intermediatePath);
        // Check if conversion to canonical path succeeded
        if (realPath == 0x0)
            return path;
        path = path_filename(std::string(realPath));
        free(realPath);
    }
#endif
    return path;
}

void execute(const std::string& command)
{
    int ignored __attribute__((unused));
#ifdef _WIN32
    ShellExecuteA( nullptr, nullptr, command.c_str(), nullptr, nullptr, 0 );
#elif defined(__APPLE__)
    (void) system( command.c_str() );
#else
    ignored = system( command.c_str() );
#endif
}

size_t memory_usage()
{
#if defined(__linux__)
    // Grabbing info directly from the /proc pseudo-filesystem.  Reading from
    // /proc/self/statm gives info on your own process, as one line of
    // numbers that are: virtual mem program size, resident set size,
    // shared pages, text/code, data/stack, library, dirty pages.  The
    // mem sizes should all be multiplied by the page size.
    size_t size = 0;
    FILE *file = fopen("/proc/self/statm", "r");
    if (file) {
        unsigned long m = 0;
        int ret = 0, ret2 = 0;
        ret = fscanf (file, "%lu", &m);  // virtual mem program size,
        ret2 = fscanf (file, "%lu", &m);  // resident set size,
        fclose (file);
        if (ret>0 && ret2>0)
            size = (size_t)m * getpagesize();
    }
    return size;

#elif defined(__APPLE__)
    // Inspired from
    // http://miknight.blogspot.com/2005/11/resident-set-size-in-mac-os-x.html
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    task_info(current_task(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count);
    return t_info.resident_size;

#elif defined(_WIN32)
    // According to MSDN...
    PROCESS_MEMORY_COUNTERS counters;
    if (GetProcessMemoryInfo (GetCurrentProcess(), &counters, sizeof (counters)))
        return counters.PagefileUsage;
    else return 0;

#else
    return 0;
#endif
}

size_t memory_max_usage()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS counters;
    if (GetProcessMemoryInfo (GetCurrentProcess(), &counters, sizeof (counters)))
        return counters.PeakPagefileUsage;
    else return 0;
#else
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    return 1024 * r_usage.ru_maxrss;
#endif
}

} //namespace ImGuiHelper

namespace base64 
{
// Decoder here
	extern "C"
	{
		typedef enum {step_a, step_b, step_c, step_d} base64_decodestep;
		typedef struct {base64_decodestep step;char plainchar;} base64_decodestate;

inline int base64_decode_value(char value_in)	{
	static const char decoding[] = {62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-2,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
	static const char decoding_size = sizeof(decoding);
	value_in -= 43;
	if (value_in < 0 || value_in > decoding_size) return -1;
	return decoding[(int)value_in];
}
inline void base64_init_decodestate(base64_decodestate* state_in)	{
	state_in->step = step_a;
	state_in->plainchar = 0;
}
inline int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state_in)	{
	const char* codechar = code_in;
	char* plainchar = plaintext_out;
	char fragment;
	
	*plainchar = state_in->plainchar;
	
	switch (state_in->step)
	{
		while (1)
		{
	case step_a:
			do {
				if (codechar == code_in+length_in)
				{
					state_in->step = step_a;
					state_in->plainchar = *plainchar;
					return plainchar - plaintext_out;
				}
				fragment = (char)base64_decode_value(*codechar++);
			} while (fragment < 0);
			*plainchar    = (fragment & 0x03f) << 2;
	case step_b:
			do {
				if (codechar == code_in+length_in)
				{
					state_in->step = step_b;
					state_in->plainchar = *plainchar;
					return plainchar - plaintext_out;
				}
				fragment = (char)base64_decode_value(*codechar++);
			} while (fragment < 0);
			*plainchar++ |= (fragment & 0x030) >> 4;
			*plainchar    = (fragment & 0x00f) << 4;
	case step_c:
			do {
				if (codechar == code_in+length_in)
				{
					state_in->step = step_c;
					state_in->plainchar = *plainchar;
					return plainchar - plaintext_out;
				}
				fragment = (char)base64_decode_value(*codechar++);
			} while (fragment < 0);
			*plainchar++ |= (fragment & 0x03c) >> 2;
			*plainchar    = (fragment & 0x003) << 6;
	case step_d:
			do {
				if (codechar == code_in+length_in)
				{
					state_in->step = step_d;
					state_in->plainchar = *plainchar;
					return plainchar - plaintext_out;
				}
				fragment = (char)base64_decode_value(*codechar++);
			} while (fragment < 0);
			*plainchar++   |= (fragment & 0x03f);
		}
	}
	/* control should not reach here */
	return plainchar - plaintext_out;
}
	}	// extern "C"
	struct decoder
	{
		base64_decodestate _state;
		int _buffersize;
		
		decoder(int buffersize_in = 4096) : _buffersize(buffersize_in) {}
		int decode(char value_in) {return base64_decode_value(value_in);}
		int decode(const char* code_in, const int length_in, char* plaintext_out)	{return base64_decode_block(code_in, length_in, plaintext_out, &_state);}
	};

// Encoder Here
	extern "C" {
		typedef enum {step_A, step_B, step_C} base64_encodestep;
		typedef struct {base64_encodestep step;char result;int stepcount;} base64_encodestate;

const int CHARS_PER_LINE = 2147483647;//72; // This was hard coded to 72 originally. But here we add '\n' at a later step. So we use MAX_INT here.
inline void base64_init_encodestate(base64_encodestate* state_in)	{
	state_in->step = step_A;
	state_in->result = 0;
	state_in->stepcount = 0;
}
inline char base64_encode_value(char value_in)	{
	static const char* encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	if (value_in > 63) return '=';
	return encoding[(int)value_in];
}
inline int base64_encode_block(const char* plaintext_in, int length_in, char* code_out, base64_encodestate* state_in)	{
	const char* plainchar = plaintext_in;
	const char* const plaintextend = plaintext_in + length_in;
	char* codechar = code_out;
    char result = '\0';
    char fragment = '\0';
	
	result = state_in->result;
	
	switch (state_in->step)
	{
		while (1)
		{
	case step_A:
			if (plainchar == plaintextend)
			{
				state_in->result = result;
				state_in->step = step_A;
				return codechar - code_out;
			}
			fragment = *plainchar++;
			result = (fragment & 0x0fc) >> 2;
			*codechar++ = base64_encode_value(result);
			result = (fragment & 0x003) << 4;
	case step_B:
			if (plainchar == plaintextend)
			{
				state_in->result = result;
				state_in->step = step_B;
				return codechar - code_out;
			}
			fragment = *plainchar++;
			result |= (fragment & 0x0f0) >> 4;
			*codechar++ = base64_encode_value(result);
			result = (fragment & 0x00f) << 2;
	case step_C:
			if (plainchar == plaintextend)
			{
				state_in->result = result;
				state_in->step = step_C;
				return codechar - code_out;
			}
			fragment = *plainchar++;
			result |= (fragment & 0x0c0) >> 6;
			*codechar++ = base64_encode_value(result);
			result  = (fragment & 0x03f) >> 0;
			*codechar++ = base64_encode_value(result);
			
			++(state_in->stepcount);
			if (state_in->stepcount == CHARS_PER_LINE/4)
			{
				*codechar++ = '\n';
				state_in->stepcount = 0;
			}
		}
	}
	/* control should not reach here */
	return codechar - code_out;
}

inline int base64_encode_blockend(char* code_out, base64_encodestate* state_in)	{
	char* codechar = code_out;
	
	switch (state_in->step)
	{
	case step_B:
		*codechar++ = base64_encode_value(state_in->result);
		*codechar++ = '=';
		*codechar++ = '=';
		break;
	case step_C:
		*codechar++ = base64_encode_value(state_in->result);
		*codechar++ = '=';
		break;
	case step_A:
		break;
	}
	*codechar++ = '\n';
	
	return codechar - code_out;
}	
	} // extern "C"
	struct encoder
	{
		base64_encodestate _state;
		int _buffersize;
		
		encoder(int buffersize_in = 4096)
		: _buffersize(buffersize_in)
		{}
		int encode(char value_in)
		{
			return base64_encode_value(value_in);
		}
		int encode(const char* code_in, const int length_in, char* plaintext_out)
		{
			return base64_encode_block(code_in, length_in, plaintext_out, &_state);
		}
		int encode_end(char* plaintext_out)
		{
			return base64_encode_blockend(plaintext_out, &_state);
		}
	};
} // namespace base64

namespace ImGui {
namespace Stringifier {
template <typename VectorChar> static bool Base64Decode(const char* input,VectorChar& output)
{
    output.clear();if (!input) return false;
    const int N = 4096;
    base64::decoder d(N);
    base64_init_decodestate(&d._state);

    int outputStart=0,outputlength = 0;
    int codelength = strlen(input);
    const char* pIn = input;
    int stepCodeLength = 0;
    do
    {
        output.resize(outputStart+N);
        stepCodeLength = codelength>=N?N:codelength;
        outputlength = d.decode(pIn, stepCodeLength, &output[outputStart]);
        outputStart+=outputlength;
        pIn+=stepCodeLength;
        codelength-=stepCodeLength;
    }
    while (codelength>0);

    output.resize(outputStart);
    //
    base64_init_decodestate(&d._state);
    return true;
}

template <typename VectorChar> static bool Base64Encode(const char* input,int inputSize,VectorChar& output)
{
	output.clear();if (!input || inputSize==0) return false;

    const int N=4096;
    base64::encoder e(N);
    base64_init_encodestate(&e._state);

    int outputStart=0,outputlength = 0;
    int codelength = inputSize;
    const char* pIn = input;
    int stepCodeLength = 0;

    do
    {
        output.resize(outputStart+2*N);
        stepCodeLength = codelength>=N?N:codelength;
        outputlength = e.encode(pIn, stepCodeLength,&output[outputStart]);
        outputStart+=outputlength;
        pIn+=stepCodeLength;
        codelength-=stepCodeLength;
    }
    while (codelength>0);

    output.resize(outputStart+2*N);
    outputlength = e.encode_end(&output[outputStart]);
    outputStart+=outputlength;
    output.resize(outputStart);
    //
    base64_init_encodestate(&e._state);

	return true;
}
inline static unsigned int Decode85Byte(char c)   { return c >= '\\' ? c-36 : c-35; }
static void Decode85(const unsigned char* src, unsigned char* dst)
{
    while (*src)
    {
        unsigned int tmp = Decode85Byte(src[0]) + 85*(Decode85Byte(src[1]) + 85*(Decode85Byte(src[2]) + 85*(Decode85Byte(src[3]) + 85*Decode85Byte(src[4]))));
        dst[0] = ((tmp >> 0) & 0xFF); dst[1] = ((tmp >> 8) & 0xFF); dst[2] = ((tmp >> 16) & 0xFF); dst[3] = ((tmp >> 24) & 0xFF);   // We can't assume little-endianness.
        src += 5;
        dst += 4;
    }
}
template <typename VectorChar> static bool Base85Decode(const char* input,VectorChar& output)
{
	output.clear();if (!input) return false;
	const int outputSize = (((int)strlen(input) + 4) / 5) * 4;
	output.resize(outputSize);
    Decode85((const unsigned char*)input,(unsigned char*)&output[0]);
    return true;
}

inline static char Encode85Byte(unsigned int x)
{
    x = (x % 85) + 35;
    return (x>='\\') ? x+1 : x;
}
template <typename VectorChar> static bool Base85Encode(const char* input,int inputSize,VectorChar& output,bool outputStringifiedMode,int numCharsPerLineInStringifiedMode=112)	
{
    // Adapted from binary_to_compressed_c(...) inside imgui_draw.cpp
    output.clear();if (!input || inputSize==0) return false;
    output.reserve((int)((float)inputSize*1.3f));
    if (numCharsPerLineInStringifiedMode<=12) numCharsPerLineInStringifiedMode = 12;
    if (outputStringifiedMode) output.push_back('"');
    char prev_c = 0;int cnt=0;
    for (int src_i = 0; src_i < inputSize; src_i += 4)
    {
        unsigned int d = *(unsigned int*)(input + src_i);
        for (unsigned int n5 = 0; n5 < 5; n5++, d /= 85)
        {
            char c = Encode85Byte(d);
            if (outputStringifiedMode && c == '?' && prev_c == '?') output.push_back('\\');	// This is made a little more complicated by the fact that ??X sequences are interpreted as trigraphs by old C/C++ compilers. So we need to escape pairs of ??.
            output.push_back(c);
            prev_c = c;
        }
        cnt+=4;
        if (outputStringifiedMode && cnt>=numCharsPerLineInStringifiedMode)
        {
            output.push_back('"');
            output.push_back('	');
            output.push_back('\\');
            //output.push_back(' ');
            output.push_back('\n');
            output.push_back('"');
            cnt=0;
        }
    }
    // End
    if (outputStringifiedMode)
    {
        output.push_back('"');
        output.push_back(';');
        output.push_back('\n');
        output.push_back('\n');
    }
    output.push_back('\0');	// End character

    return true;
}
} // namespace Stringifier

bool Base64Encode(const char* input,int inputSize,ImVector<char>& output,bool stringifiedMode,int numCharsPerLineInStringifiedMode)
{
    if (!stringifiedMode) return Stringifier::Base64Encode<ImVector<char> >(input,inputSize,output);
    else
    {
        ImVector<char> output1;
        if (!Stringifier::Base64Encode<ImVector<char> >(input,inputSize,output1)) {output.clear();return false;}
        if (output1.size()==0) {output.clear();return false;}
        if (!ImGui::TextStringify(&output1[0],output,numCharsPerLineInStringifiedMode,output1.size()-1)) {output.clear();return false;}
    }
    return true;
}

bool Base64Decode(const char* input,ImVector<char>& output)
{
    return Stringifier::Base64Decode<ImVector<char> >(input,output);
}

bool Base85Encode(const char* input,int inputSize,ImVector<char>& output,bool stringifiedMode,int numCharsPerLineInStringifiedMode)
{
    return Stringifier::Base85Encode<ImVector<char> >(input,inputSize,output,stringifiedMode,numCharsPerLineInStringifiedMode);
}

bool Base85Decode(const char* input,ImVector<char>& output)
{
    return Stringifier::Base85Decode<ImVector<char> >(input,output);
}

bool BinaryStringify(const char* input, int inputSize, ImVector<char>& output, int numInputBytesPerLineInStringifiedMode,bool serializeUnsignedBytes)
{
    output.clear();
    if (!input || inputSize<=0) return false;
    ImGuiTextBuffer b;
    b.clear();
    b.Buf.reserve(inputSize*7.5f);
    // -----------------------------------------------------------
    if (serializeUnsignedBytes)
    {
        b.appendf("{%d",(int) (*((unsigned char*) &input[0])));  // start byte
        int cnt=1;
        for (int i=1;i<inputSize;i++)
        {
            if (cnt++>=numInputBytesPerLineInStringifiedMode) {cnt=0;b.appendf("\n");}
            b.appendf(",%d",(int) (*((unsigned char*) &input[i])));
        }
    }
    else
    {
        b.appendf("{%d",(int)input[0]);  // start byte
        int cnt=1;
        for (int i=1;i<inputSize;i++)
        {
            if (cnt++>=numInputBytesPerLineInStringifiedMode) {cnt=0;b.appendf("\n");}
            b.appendf(",%d",(int)input[i]);
        }
    }
    b.appendf("};\n");
    //-------------------------------------------------------------
    b.Buf.swap(output);
    return true;
}

bool TextStringify(const char* input, ImVector<char>& output, int numCharsPerLineInStringifiedMode, int inputSize, bool noBackslashAtLineEnds)
{
    output.clear();if (!input) return false;
    if (inputSize<=0) inputSize=strlen(input);
    output.reserve(inputSize*1.25f);
    // --------------------------------------------------------------
    output.push_back('"');
    char c='\n';int cnt=0;bool endFile = false;
    for (int i=0;i<inputSize;i++)
    {
        c = input[i];
        switch (c)
        {
        case '\\':
            output.push_back('\\');
            output.push_back('\\');
            break;
        case '"':
            output.push_back('\\');
            output.push_back('"');
            break;
        case '\r':
        case '\n':
            //---------------------
            output.push_back('\\');
            output.push_back(c=='\n' ? 'n' : 'r');
            if (numCharsPerLineInStringifiedMode<=0)
            {
                // Break at newline to ease reading:
                output.push_back('"');                
                if (i==inputSize-1)
                {
                    endFile = true;
                    if (!noBackslashAtLineEnds) output.push_back(';');
                    output.push_back('\n');
                }
                else
                {
                    if (!noBackslashAtLineEnds)
                    {
                        output.push_back('\t');
                        output.push_back('\\');
                    }
                    output.push_back('\n');
                    output.push_back('"');
                }
                cnt = 0;
                //--------------------
            }
            //--------------------
            break;
        default:
            output.push_back(c);
            if (++cnt>=numCharsPerLineInStringifiedMode && numCharsPerLineInStringifiedMode>0)
            {
                //---------------------
                //output.push_back('\\');
                //output.push_back('n');
                output.push_back('"');

                if (i==inputSize-1)
                {
                    endFile = true;
                    if (!noBackslashAtLineEnds) output.push_back(';');
                    output.push_back('\n');
                }
                else
                {
                    if (!noBackslashAtLineEnds)
                    {
                        output.push_back('\t');
                        output.push_back('\\');
                    }
                    output.push_back('\n');
                    output.push_back('"');
                }
                cnt = 0;
                //--------------------
            }
            break;
        }
    }

    if (!endFile)
    {
        output.push_back('"');
        if (!noBackslashAtLineEnds) output.push_back(';');
        output.push_back('\n');
        //--------------------
    }

    output.push_back('\0');	// End character
    //-------------------------------------------------------------
    return true;
}
} // namespace ImGui

#ifdef IMGUI_USE_ZLIB	// requires linking to library -lZlib
#include <zlib.h>
namespace ImGui {
bool GzDecompressFromFile(const char* filePath,ImVector<char>& rv,bool clearRvBeforeUsage)   {
    if (clearRvBeforeUsage) rv.clear();
    ImVector<char> f_data;
    if (!ImGuiHelper::GetFileContent(filePath,f_data,true,"rb",false)) return false;
    //----------------------------------------------------
    return GzDecompressFromMemory(&f_data[0],f_data.size(),rv,clearRvBeforeUsage);
    //----------------------------------------------------
}
bool GzBase64DecompressFromFile(const char* filePath,ImVector<char>& rv)    {
    ImVector<char> f_data;
    if (!ImGuiHelper::GetFileContent(filePath,f_data,true,"r",true)) return false;
    return ImGui::GzBase64DecompressFromMemory(&f_data[0],rv);
}
bool GzBase85DecompressFromFile(const char* filePath,ImVector<char>& rv)    {
    ImVector<char> f_data;
    if (!ImGuiHelper::GetFileContent(filePath,f_data,true,"r",true)) return false;
    return ImGui::GzBase85DecompressFromMemory(&f_data[0],rv);
}

bool GzDecompressFromMemory(const char* memoryBuffer,int memoryBufferSize,ImVector<char>& rv,bool clearRvBeforeUsage)    {
    if (clearRvBeforeUsage) rv.clear();
    const int startRv = rv.size();

    if (memoryBufferSize == 0  || !memoryBuffer) return false;
    const int memoryChunk = memoryBufferSize > (16*1024) ? (16*1024) : memoryBufferSize;
    rv.resize(startRv+memoryChunk);  // we start using the memoryChunk length

    z_stream myZStream;
    myZStream.next_in = (Bytef *) memoryBuffer;
    myZStream.avail_in = memoryBufferSize;
    myZStream.total_out = 0;
    myZStream.zalloc = Z_NULL;
    myZStream.zfree = Z_NULL;

    bool done = false;
    if (inflateInit2(&myZStream, (16+MAX_WBITS)) == Z_OK) {
        int err = Z_OK;
        while (!done) {
            if (myZStream.total_out >= (uLong)(rv.size()-startRv)) rv.resize(rv.size()+memoryChunk);    // not enough space: we add the memoryChunk each step

            myZStream.next_out = (Bytef *) (&rv[startRv] + myZStream.total_out);
            myZStream.avail_out = rv.size() - startRv - myZStream.total_out;

            if ((err = inflate (&myZStream, Z_SYNC_FLUSH))==Z_STREAM_END) done = true;
            else if (err != Z_OK)  break;
        }
        if ((err=inflateEnd(&myZStream))!= Z_OK) done = false;
    }
    rv.resize(startRv+(done ? myZStream.total_out : 0));

    return done;
}
bool GzCompressFromMemory(const char* memoryBuffer,int memoryBufferSize,ImVector<char>& rv,bool clearRvBeforeUsage)  {
    if (clearRvBeforeUsage) rv.clear();
    const int startRv = rv.size();

    if (memoryBufferSize == 0  || !memoryBuffer) return false;
    const int memoryChunk = memoryBufferSize/3 > (16*1024) ? (16*1024) : memoryBufferSize/3;
    rv.resize(startRv+memoryChunk);  // we start using the memoryChunk length

    z_stream myZStream;
    myZStream.next_in =  (Bytef *) memoryBuffer;
    myZStream.avail_in = memoryBufferSize;
    myZStream.total_out = 0;
    myZStream.zalloc = Z_NULL;
    myZStream.zfree = Z_NULL;

    bool done = false;
    if (deflateInit2(&myZStream,Z_BEST_COMPRESSION,Z_DEFLATED,(16+MAX_WBITS),8,Z_DEFAULT_STRATEGY) == Z_OK) {
        int err = Z_OK;
        while (!done) {
            if (myZStream.total_out >= (uLong)(rv.size()-startRv)) rv.resize(rv.size()+memoryChunk);    // not enough space: we add the full memoryChunk each step

            myZStream.next_out = (Bytef *) (&rv[startRv] + myZStream.total_out);
            myZStream.avail_out = rv.size() - startRv - myZStream.total_out;

            if ((err = deflate (&myZStream, Z_FINISH))==Z_STREAM_END) done = true;
            else if (err != Z_OK)  break;
        }
        if ((err=deflateEnd(&myZStream))!= Z_OK) done=false;
    }
    rv.resize(startRv+(done ? myZStream.total_out : 0));

    return done;
}

bool GzBase64DecompressFromMemory(const char* input,ImVector<char>& rv) {
    rv.clear();ImVector<char> v;
    if (ImGui::Base64Decode(input,v)) return false;
    if (v.size()==0) return false;
    return GzDecompressFromMemory(&v[0],v.size(),rv);
}
bool GzBase85DecompressFromMemory(const char* input,ImVector<char>& rv) {
    rv.clear();ImVector<char> v;
    if (ImGui::Base85Decode(input,v)) return false;
    if (v.size()==0) return false;
    return GzDecompressFromMemory(&v[0],v.size(),rv);
}
bool GzBase64CompressFromMemory(const char* input,int inputSize,ImVector<char>& output,bool stringifiedMode,int numCharsPerLineInStringifiedMode)   {
    output.clear();ImVector<char> output1;
    if (!ImGui::GzCompressFromMemory(input,inputSize,output1)) return false;
    return ImGui::Base64Encode(&output1[0],output1.size(),output,stringifiedMode,numCharsPerLineInStringifiedMode);
}
bool GzBase85CompressFromMemory(const char* input,int inputSize,ImVector<char>& output,bool stringifiedMode,int numCharsPerLineInStringifiedMode) {
    output.clear();ImVector<char> output1;
    if (!ImGui::GzCompressFromMemory(input,inputSize,output1)) return false;
    return ImGui::Base85Encode(&output1[0],output1.size(),output,stringifiedMode,numCharsPerLineInStringifiedMode);
}
} // namespace ImGui
#endif //IMGUI_USE_ZLIB

namespace ImGui
{
// Two methods that fill rv and return true on success
bool Base64DecodeFromFile(const char* filePath,ImVector<char>& rv)  {
    ImVector<char> f_data;
    if (!ImGuiHelper::GetFileContent(filePath,f_data,true,"r",true)) return false;
    return ImGui::Base64Decode(&f_data[0],rv);
}
bool Base85DecodeFromFile(const char* filePath,ImVector<char>& rv)  {
    ImVector<char> f_data;
    if (!ImGuiHelper::GetFileContent(filePath,f_data,true,"r",true)) return false;
    return ImGui::Base85Decode(&f_data[0],rv);
}

// Generate color
void RandomColor(ImVec4& color, float alpha)
{
    alpha = ImClamp(alpha, 0.0f, 1.0f);
    int r = std::rand() % 255;
    int g = std::rand() % 255;
    int b = std::rand() % 255;
    color = ImVec4(r / 255.0, g / 255.0, b / 255.0, alpha);
}

void RandomColor(ImU32& color, float alpha)
{
    alpha = ImClamp(alpha, 0.0f, 1.0f);
    int r = std::rand() % 255;
    int g = std::rand() % 255;
    int b = std::rand() % 255;
    color = IM_COL32(r, g, b, (int)(alpha * 255.f));
}

} // namespace ImGui

namespace ImGui
{
// FFT 1D
inline void swap(float* a, float* b)
{
	float t = *a;
	*a = *b;
	*b = t;
}

inline float sqr(float arg)
{
	return arg * arg;
}

void ImFFT(float* data, int N,  bool forward)
{
	int n = N << 1;
	int i, j, m, mmax;

	/* bit reversal section */

	j = 0;
	for (i = 0; i < n; i += 2) 
	{
		if (j > i) 
		{
			swap (&data[j], &data[i]);
			swap (&data[j + 1], &data[i + 1]);
		}
		m = N;
		while (m >= 2 && j >= m) 
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}

	/* Daniel-Lanczos section */

	float theta, wr, wpr, wpi, wi, wtemp;
	float tempr, tempi;
	for (mmax = 2; n > mmax;) 
	{
		int istep = mmax << 1;
		theta = (forward ? 1 : -1) * (2.0 * M_PI / mmax);
		wpr = -2.0 * sqr (sin (0.5 * theta));
		wpi = sin (theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 0; m < mmax; m += 2) 
		{
			for (i = m; i < n; i += istep) 
			{
				j = i + mmax;
				tempr = wr * data[j] - wi * data[j + 1];
				tempi = wr * data[j + 1] + wi * data[j];
				data[j] = data[i] - tempr;
				data[j + 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpr + wtemp * wpi + wi;
		}
		mmax = istep;
	}

	/* normalisation section */
	const float tmp = 1.0 / sqrt ((float)N);
	for (i = 0; i < n; i++)
		data[i] *= tmp;
}

void ImRFFT(float* data, int N,  bool forward)
{
	/* main section */
	int k;
	float c1 = 0.5, c2;
	float theta = M_PI / (float) (N >> 1);

	if (forward) 
	{
		c2 = -0.5;
		ImFFT(data, N >> 1, forward);
	} 
	else 
	{
		c2 = +0.5;
		theta = -theta;
	}

	float wpr = -2.0 * sqr (sin (0.5 * theta));
	float wpi = sin (theta);
	float wr = 1.0 + wpr;
	float wi = wpi;
	float wtemp;

	int i, i1, i2, i3, i4;
	float h1r, h1i, h2r, h2i;
	for (i = 1; i < N >> 2; i++) 
	{
		i1 = i + i;
		i2 = i1 + 1;
		i3 = N - i1;
		i4 = i3 + 1;
		h1r = c1 * (data[i1] + data[i3]);
		h1i = c1 * (data[i2] - data[i4]);
		h2r = -c2 * (data[i2] + data[i4]);
		h2i = c2 * (data[i1] - data[i3]);
		data[i1] = h1r + wr * h2r - wi * h2i;
		data[i2] = h1i + wr * h2i + wi * h2r;
		data[i3] = h1r - wr * h2r + wi * h2i;
		data[i4] = -h1i + wr * h2i + wi * h2r;
		wr = (wtemp = wr) * wpr - wi * wpi + wr;
		wi = wi * wpr + wtemp * wpi + wi;
	}

	if (forward) 
	{
		data[0] = (h1r = data[0]) + data[1];
		data[1] = h1r - data[1];
	}
	else 
	{
		data[0] = c1 * ((h1r = data[0]) + data[1]);
		data[1] = c1 * (h1r - data[1]);
		ImFFT(data, N >> 1, forward);
	}

	/* normalisation section */
	//const float tmp = forward ? M_SQRT1_2 : M_SQRT2;
	//for (k = 0; k < N; k++)
	//	data[k] *= tmp;
}

void ImRFFT(float* in, float* out, int N,  bool forward)
{
    memcpy(out, in, sizeof(float) * N);
    ImRFFT(out, N, forward);
}

int ImReComposeDB(float * in, float * out, int samples, bool inverse)
{
	int i,max = 0;
	float zero_db,db,max_db = -FLT_MAX;
	float amplitude;
    int N = samples >> 1;
	zero_db = - 20 * log10((float)(1<<15));
	for (i = 0; i < N + 1; i++)
	{
		if (i != 0/* && i != N*/)
		{
			amplitude = sqrt(sqr(in[2 * i]) + sqr(in[2 * i + 1]));
		}
		else
		{
			amplitude = 1.0f / (1<<15);
		}
		db = 20 * log10(amplitude) - (inverse ? zero_db : 0);
		out[i] = db;
		if (db > max_db)
		{
			max_db = db;
			max = i;
		}
	}
	return max;
}

int ImReComposeAmplitude(float * in, float * out, int samples)
{
	int i,max = 0;
	float tmp,dmax = 0;
	for (i = 0; i < (samples >> 1) + 1; i++)
	{
		if (i != 0/* && i != (samples >> 1)*/)
		{
			tmp = sqrt(sqr(in[2 * i]) + sqr(in[2 * i + 1]));
		}
		else
		{
			tmp = 0;//sqr(in[i == 0 ? 0 : 1]);
		}
		out[i] = tmp;
		if (tmp > dmax)
		{
			dmax = tmp;
			max = i;
		}
	}
	return max;
}

int ImReComposePhase(float * in, float * out, int samples)
{
    for (int i = 0; i < (samples >> 1) + 1; i++)
	{
        float hAngle = 0;
        float dx = in[2 * i];
        float dy = in[2 * i + 1];
        hAngle = atan2(dy, dx);
        hAngle = 180.f * hAngle / M_PI;
        out[i] = hAngle;
    }
	return 0;
}

int ImReComposeDBShort(float * in, float * out, int samples, bool inverse)
{
	int i,j;
	int n_sample;
	int start_sample;
	float zero_db;
	float tmp;
	static unsigned int freq_table[21] = {0,1,2,3,4,5,6,7,8,11,15,20,
		27,36,47,62,82,107,141,184,255}; //fft_number

	zero_db = - 20 * log10((float)(1<<15));

	for (i = 0; i< 20; i++)
	{
		start_sample = freq_table[i] * (samples / 256);
		n_sample = (freq_table[i + 1] - freq_table[i])  * (samples / 256);
		tmp=0;
		for (j = start_sample; j < start_sample + n_sample; j++)
		{
			tmp += 2 * sqr(in[j]);
		}
		
		tmp /= (float)n_sample;
		out[i] = 20.0 * log10(tmp) - (inverse ? zero_db : 0);
	}
	return 20;
}

int ImReComposeDBLong(float * in, float * out, int samples, bool inverse)
{
	int i,j;
	int n_sample;
	int start_sample;
	float zero_db;
	float tmp;
	static unsigned int freq_table[77] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,
		19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
		35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,
		52,53,54,55,56,57,58,61,66,71,76,81,87,93,100,107,
		114,122,131,140,150,161,172,184,255}; //fft_number

	zero_db = - 20 * log10((float)(1<<15));

	for (i = 0; i< 76; i++)
	{
		start_sample = freq_table[i] * (samples / 256);
		n_sample = (freq_table[i + 1] - freq_table[i]) * (samples / 256);
		tmp=0;
		for (j = start_sample; j < start_sample + n_sample; j++)
		{
			tmp += 2 * sqr(in[j]);
		}
		
		tmp /= (float)n_sample;
		out[i] = 20.0 * log10(tmp) - (inverse ? zero_db : 0);
	}
	return 76;
}

float ImDoDecibel(float * in, int samples, bool inverse)
{
	int i;
	float db,zero_db;
	float tmp;
	zero_db = - 20 * log10((float)(1<<15));
	tmp = 0;
	for (i = 0; i < (samples >> 1) + 1; i++)
	{
		if (i != 0 && i != (samples >> 1))
		{
			tmp += 2 * (sqr(in[2 * i]) + sqr(in[2 * i+1]));
		}
		else
		{
			tmp += sqr(in[i == 0 ? 0 : 1]);
		}
	}
	tmp /= (float)samples;
	db = 20 * log10(tmp) - (inverse ? zero_db : 0);
	return db;
}

struct HannWindow
{
    inline HannWindow(int _frame_size, int _shift_size)
    {
        float tmp = 0;
        shift_size = _shift_size;
        frame_size = _frame_size;
        hann = new float[frame_size];
        for (int i = 0; i < frame_size; i++) hann[i] = 0.5 * (1.0 - cos(2.0 * M_PI * (i / (float)frame_size)));
        for (int i = 0; i < frame_size; i++) tmp += hann[i] * hann[i];
        tmp /= shift_size;
        tmp = std::sqrt(tmp);
        for (int i = 0; i < frame_size; i++) hann[i] /= tmp;
    }
    inline ~HannWindow() { delete[] hann; };
    inline void Process(float * buffer) { for (int i = 0; i < frame_size; i++) buffer[i] *= hann[i]; }

private:
    float *hann {nullptr};
    int shift_size;
    int frame_size;
};

struct Overlap
{
public:
    inline Overlap(uint32_t _frame_size, uint32_t _shift_size)
    {
        frame_size = _frame_size;
        shift_size = _shift_size;
        buf_offset = 0;
        num_block = frame_size / shift_size;
        output = new float[shift_size];
        buf = new float[frame_size];
        memset(buf, 0, frame_size * sizeof(float));
    }
    inline ~Overlap() { delete[] buf; delete[] output; };
    inline float *overlap(float *in)
    {
        // Shift
        for (int i = 0; i < static_cast<int>(frame_size - shift_size); i++) buf[i] = buf[i + shift_size];
        // Emptying Last Block
        memset(buf + shift_size * (num_block - 1), 0, sizeof(float) * shift_size);
        // Sum
        for (int i = 0; i < static_cast<int>(frame_size); i++) buf[i] += in[i];
        // Distribution for float format
        for (int i = 0; i < static_cast<int>(shift_size); i++) output[i] = static_cast<float>(buf[i]);
        return output;
    }

private:
    uint32_t frame_size;
    uint32_t shift_size;
    uint32_t num_block;
    uint32_t buf_offset;
    float *output;
    float *buf;
};

ImSTFT::ImSTFT(int frame_, int shift_)
{
    frame_size = frame_;
    shift_size = shift_;
    overlap_size = frame_size - shift_size;
    hannwin = new HannWindow(frame_size, shift_size);
    overlap = new Overlap(frame_size, shift_size);
    buf = new float[frame_size];
    memset(buf, 0, sizeof(float) * frame_size);
}

ImSTFT::~ImSTFT()
{ 
    delete (HannWindow*)hannwin; 
    delete (Overlap*)overlap; 
    delete[] buf;
};

void ImSTFT::stft(float* in, float* out)
{
    /*** Shfit & Copy***/
    for (int i = 0; i < overlap_size; i++) buf[i] = buf[i + shift_size];
    for (int i = 0; i < shift_size; i++) buf[overlap_size + i] = static_cast<float>(in[i]);
    memcpy(out, buf, sizeof(float) * frame_size);
    /*** Window ***/
    ((HannWindow*)hannwin)->Process(out);
    /*** FFT ***/
    ImGui::ImRFFT(out, frame_size, true);
}

void ImSTFT::istft(float* in, float* out)
{
    /*** iFFT ***/
    ImGui::ImRFFT(in, frame_size, false);
    /*** Window ***/
    ((HannWindow*)hannwin)->Process(in);
    /*** Output ***/
    memcpy(out, ((Overlap*)overlap)->overlap(in), sizeof(float) * shift_size);
}
} // namespace ImGui

//-----------------------------------------------------------------------------
// BanchMark utils
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else // _WIN32
#include <sys/time.h>
#endif // _WIN32
#include <thread>

double ImGui::get_current_time()
{
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);
    return (double)pc.QuadPart / ((double)freq.QuadPart + 1e-10);
#else  // _WIN32
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
#endif // _WIN32
}

uint32_t ImGui::get_current_time_msec()
{
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);
    return pc.QuadPart * 1000.0 / freq.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint32_t)tv.tv_sec * 1000 + (uint32_t)tv.tv_usec / 1000);
#endif
}

uint64_t ImGui::get_current_time_usec()
{
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);
    return pc.QuadPart * 1000000.0 / freq.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec);
#endif
}

void ImGui::sleep(float seconds)
{
    IM_ASSERT(seconds >= 0 && !isinf(seconds));
    const int waiting_time_ms = seconds * 1000;
    if (waiting_time_ms == 0)
        std::this_thread::yield();
    else
        std::this_thread::sleep_for(std::chrono::milliseconds(waiting_time_ms));
}

void ImGui::sleep(int ms_seconds)
{
    IM_ASSERT(ms_seconds >= 0);
    if (ms_seconds == 0)
        std::this_thread::yield();
    else
        std::this_thread::sleep_for(std::chrono::milliseconds(ms_seconds));
}

// Power Save utils
double ImGui::GetEventWaitingTime()
{
    ImGuiContext& g = *GImGui;
    if (g.IO.ConfigFlags & ImGuiConfigFlags_EnableLowRefreshMode)
    {
        double current_time = get_current_time();
        double deltaTime = g.WallClock > 0 ? current_time - g.WallClock : g.MaxWaitBeforeNextFrame;
        double delta = g.MaxWaitBeforeNextFrame - deltaTime;
        return ImMax(0.0, delta);
    }

    if ((g.IO.ConfigFlags & ImGuiConfigFlags_EnablePowerSavingMode) && g.IO.FrameCountSinceLastInput > 2)
        return ImMax(0.0, g.MaxWaitBeforeNextFrame);

    return 0.0;
}

void ImGui::SetMaxWaitBeforeNextFrame(double time)
{
    ImGuiContext& g = *GImGui;

    g.MaxWaitBeforeNextFrame = ImMin(g.MaxWaitBeforeNextFrame, time);
}

// Kalman class
ImGui::ImKalman::ImKalman(int state_size,int mea_size)
{
    transitionMatrix.create_type(state_size, state_size, IM_DT_FLOAT32);
    measurementMatrix.create_type(state_size, mea_size, IM_DT_FLOAT32);
    processNoiseCov.create_type(state_size, state_size, IM_DT_FLOAT32);
    measurementNoiseCov.create_type(mea_size, mea_size, IM_DT_FLOAT32);
    errorCovPre.create_type(state_size, state_size, IM_DT_FLOAT32);
    errorCovPost.create_type(state_size, state_size, IM_DT_FLOAT32);
    statePost.create_type(1, state_size, IM_DT_FLOAT32);
    statePre.create_type(1, state_size, IM_DT_FLOAT32);
    K.create_type(mea_size, state_size, IM_DT_FLOAT32);

    measurementMatrix.eye(1.f);     // 观测矩阵的初始化
    processNoiseCov.eye(1e-5);      // 模型本身噪声协方差矩阵初始化
    measurementNoiseCov.eye(1e-1);  // 测量噪声的协方差矩阵初始化
    errorCovPost.eye(1.f);          // 转移噪声修正矩阵初始化
    statePost.randn(0.f, 5.0f);     // kalaman状态估计修正矩阵初始化
    transitionMatrix.eye(1.f);      // 状态转移矩阵/增益矩阵的初始化
    for (int x = 0; x < state_size; x++)
    {
        for (int y = 0; y < state_size; y++)
        {
            if (x > y && (x - state_size / 2 == y || y + state_size / 2 == x))
                transitionMatrix.at<float>(x, y) = 1.f;
        }
    }
}

void ImGui::ImKalman::covariance(float noise_covariance, float measurement_noise_covariance)
{
    processNoiseCov.eye(noise_covariance);
    measurementNoiseCov.eye(measurement_noise_covariance);
}

ImGui::ImMat& ImGui::ImKalman::predicted()
{
    statePre    = transitionMatrix * statePost;
    errorCovPre = transitionMatrix * errorCovPost * transitionMatrix.t() + processNoiseCov;
    return statePost;
}

void ImGui::ImKalman::update(ImMat& Y)
{
    K            = errorCovPre * measurementMatrix.t() * ((measurementMatrix * errorCovPre * measurementMatrix.t() + measurementNoiseCov).inv<float>());
    statePost    = statePre    + K * (Y - measurementMatrix * statePre);
    errorCovPost = errorCovPre - K * measurementMatrix * errorCovPre;
}

// warp Affine help
static inline int LU(float* A, size_t astep, int m, float* b, size_t bstep, int n, float eps)
{
    int i, j, k, p = 1;
    for( i = 0; i < m; i++ )
    {
        k = i;

        for( j = i+1; j < m; j++ )
            if( std::abs(A[j*astep + i]) > std::abs(A[k*astep + i]) )
                k = j;

        if( std::abs(A[k*astep + i]) < eps )
            return 0;

        if( k != i )
        {
            for( j = i; j < m; j++ )
                std::swap(A[i*astep + j], A[k*astep + j]);
            if( b )
                for( j = 0; j < n; j++ )
                    std::swap(b[i*bstep + j], b[k*bstep + j]);
            p = -p;
        }

        float d = -1/A[i*astep + i];

        for( j = i+1; j < m; j++ )
        {
            float alpha = A[j*astep + i]*d;

            for( k = i+1; k < m; k++ )
                A[j*astep + k] += alpha*A[i*astep + k];

            if( b )
                for( k = 0; k < n; k++ )
                    b[j*bstep + k] += alpha*b[i*bstep + k];
        }
    }

    if( b )
    {
        for( i = m-1; i >= 0; i-- )
            for( j = 0; j < n; j++ )
            {
                float s = b[i*bstep + j];
                for( k = i+1; k < m; k++ )
                    s -= A[i*astep + k]*b[k*bstep + j];
                b[i*bstep + j] = s/A[i*astep + i];
            }
    }

    return p;
}

static bool solve(const ImGui::ImMat& src, const ImGui::ImMat& src2, ImGui::ImMat& dst)
{
    // Gaussian elimination with the optimal pivot element chosen.
    bool result = true;
    IM_ASSERT(src.type == src2.type);
    int m = src.h, m_ = m, n = src.w, nb = src2.w;
    IM_ASSERT(m >= n); // The function can not solve under-determined linear systems
    dst.clone_from(src2);
    result = LU((float*)src.data, src.w, n, (float*)dst.data, dst.w, nb, FLT_EPSILON * 10) != 0;
    return result;
}

ImGui::ImMat ImGui::getPerspectiveTransform(const ImVec2 src[], const ImVec2 dst[])
{
    float a[8][8], b[8];
    for (int i = 0; i < 4; ++i)
    {
        a[i][0] = a[i + 4][3] = src[i].x;
        a[i][1] = a[i + 4][4] = src[i].y;
        a[i][2] = a[i + 4][5] = 1;
        a[i][3] = a[i][4] = a[i][5] =
        a[i + 4][0] = a[i + 4][1] = a[i + 4][2] = 0;
        a[i][6] = -src[i].x * dst[i].x;
        a[i][7] = -src[i].y * dst[i].x;
        a[i + 4][6] = -src[i].x * dst[i].y;
        a[i + 4][7] = -src[i].y * dst[i].y;
        b[i] = dst[i].x;
        b[i + 4] = dst[i].y;
    }
    ImGui::ImMat A, B;
    A.create_type(8, 8, a, IM_DT_FLOAT32);
    B.create_type(1, 8, b, IM_DT_FLOAT32);
    ImGui::ImMat M, X;
    M.create_type(3, 3, IM_DT_FLOAT32);
    solve(A, B, X);
    memcpy(M.data, X.data, sizeof(float) * X.total());
    M.at<float>(2, 2) = 1.f;
    return M;
}

ImGui::ImMat ImGui::getAffineTransform(const ImVec2 src[], const ImVec2 dst[])
{
    float a[6*6], b[6];
    for( int i = 0; i < 3; i++ )
    {
        int j = i * 12;
        int k = i * 12 + 6;
        a[j] = a[k + 3] = src[i].x;
        a[j + 1] = a[k + 4] = src[i].y;
        a[j + 2] = a[k + 5] = 1;
        a[j + 3] = a[j + 4] = a[j + 5] = 0;
        a[k] = a[k + 1] = a[k + 2] = 0;
        b[i * 2] = dst[i].x;
        b[i * 2 + 1] = dst[i].y;
    }
    ImGui::ImMat A, B;
    A.create_type(6, 6, a, IM_DT_FLOAT32);
    B.create_type(1, 6, b, IM_DT_FLOAT32);
    ImGui::ImMat M, X;
    M.create_type(3, 2, IM_DT_FLOAT32);
    solve(A, B, X);
    memcpy(M.data, X.data, sizeof(float) * X.total());
    return M;
}