#ifndef SPEEXDSP_CONFIG_H
#define SPEEXDSP_CONFIG_H

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#define EXPORT	DLL_PUBLIC

#ifdef __GNUC__
	#define ASM_MACRO		__asm__
	#define VOLATILE_MACRO	__volatile__
#else
	#define ASM_MACRO		asm
	#define VOLATILE_MACRO	volatile
#endif

#include <stddef.h>

extern void* hal_malloc(size_t size);
extern void* hal_calloc(size_t nmemb,size_t size);
extern void* hal_realloc(void* ptr,size_t size);
extern void hal_free(void* ptr);

#define OVERRIDE_SPEEX_ALLOC
static inline void* speex_alloc(int size) {
	return hal_calloc(size,1);
}

#define OVERRIDE_SPEEX_ALLOC_SCRATCH
static inline void *speex_alloc_scratch (int size) {
   /* Scratch space doesn't need to be cleared */
   return hal_malloc(size);
}

#define OVERRIDE_SPEEX_REALLOC
static inline void *speex_realloc (void *ptr, int size) {
	return hal_realloc(ptr,size);
}

#define OVERRIDE_SPEEX_FREE
static inline void speex_free (void *ptr) {
	hal_free(ptr);
}

#define OVERRIDE_SPEEX_FREE_SCRATCH
static inline void speex_free_scratch (void *ptr) {
	hal_free(ptr);
}

#endif
