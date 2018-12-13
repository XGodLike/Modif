#ifndef _VXIOBJECT_HEADER_FILE_
#define _VXIOBJECT_HEADER_FILE_

#ifdef __cplusplus
extern "C" {
#endif
 __declspec(dllexport) const char* execute(const char * src);
 __declspec(dllexport) void release(const char * dst);

#ifdef __cplusplus
}
#endif

#endif
