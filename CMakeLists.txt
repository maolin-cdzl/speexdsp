CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(speexdsp)

set(SIZE16 "int16_t")
set(USIZE16 "uint16_t")
set(SIZE32 "int32_t")
set(USIZE32 "uint32_t")

configure_file(include/speex/speexdsp_config_types.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/speex/speexdsp_config_types.h)

set(HEADERS 
	include/speex/speexdsp_config_types.h
	include/speex/speex_buffer.h
	include/speex/speexdsp_types.h
	include/speex/speex_echo.h
	include/speex/speex_jitter.h
	include/speex/speex_preprocess.h
	include/speex/speex_resampler.h)

set(PRIVATE_HEADERS
	libspeexdsp/arch.h
	libspeexdsp/fixed_generic.h
	libspeexdsp/fixed_arm4.h
	libspeexdsp/kiss_fft.h
	libspeexdsp/math_approx.h
	libspeexdsp/resample_sse.h
	libspeexdsp/stack_alloc.h
	libspeexdsp/bfin.h
	libspeexdsp/fftwrap.h
	libspeexdsp/fixed_arm5e.h
	libspeexdsp/pseudofloat.h
	libspeexdsp/vorbis_psy.h
	libspeexdsp/kiss_fftr.h
	libspeexdsp/fixed_bfin.h
	libspeexdsp/misc_bfin.h
	libspeexdsp/filterbank.h
	libspeexdsp/fixed_debug.h
	libspeexdsp/_kiss_fft_guts.h
	libspeexdsp/Makefile.am
	libspeexdsp/os_support.h
	libspeexdsp/resample_neon.h
	libspeexdsp/smallft.h
)

set(SOURCES
	libspeexdsp/fftwrap.c
	libspeexdsp/preprocess.c
	libspeexdsp/jitter.c
	libspeexdsp/kiss_fftr.c
	libspeexdsp/mdf.c
	libspeexdsp/scal.c
	libspeexdsp/buffer.c
	libspeexdsp/filterbank.c
	libspeexdsp/kiss_fft.c
	libspeexdsp/resample.c
	libspeexdsp/smallft.c
)

set(TEST_SOURCES
	libspeexdsp/testecho.c
	libspeexdsp/testjitter.c
	libspeexdsp/testdenoise.c
	libspeexdsp/testresample.c
)


add_library(speexdsp STATIC ${SOURCES} ${HEADERS} ${PRIVATE_HEADERS})

target_include_directories(speexdsp
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libspeexdsp
	)

if( ANDROID )
	target_compile_definitions(speexdsp
		PRIVATE HAVE_CONFIG_H HAVE_STDINT_H HAVE_INTTYPES_H HAVE_SYS_TYPES_H FIXED_POINT=1 _USE_NEON=1 USE_KISS_FFT=1
	)
else()
	target_compile_definitions(speexdsp
		PRIVATE HAVE_STDINT_H HAVE_INTTYPES_H HAVE_SYS_TYPES_H FIXED_POINT=1
	)
endif( ANDROID )


