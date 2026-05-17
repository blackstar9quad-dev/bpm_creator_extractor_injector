#ifdef BMP_COMPONENT_H
#define BMP_COMPONENT_H

#pragma pack(push,1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bmp_file{
	struct bmp_fileheader ;
	struct bmp_infoheader ;
	struct pixel_pallet color_pallet[]
	struct bmp_pixeldata ; 
};

struct bmp_fileheader{
	uint16_t bmp_signature ;
	uint32_t bmp_filesize ;
	uint32_t bmp_reserved ;
	uint32_t bmp_pixeloffset ;
};

struct pixel_pallet{
	uint8_t red ;
	uint8_t green ;
	uint8_t blue ;
	uint8_t alpha ;
};

struct bmp_infoheader{
	uint32_t dib_size ;
	uint32_t image_width ;
	uint32_t image_height ;
	uint16_t bmp_planes;
	uint16_t bmp_bitdepth;
	uint32_t bmp_compression ;
	uint32_t image_size ;
	uint32_t bmp_xppm;
	uint32_t bmp_yppm;
	uint32_t bmp_colorused;
	uint32_t bmp_colorimportant ; 
};

struct pixel_rgb_value{
	uint8_t red ; 
	uint8_t green ;
	uint8_t blue ;
};

pixel_rgb_value *pixel_data;

uint8_t *user_pixel_data;

struct bmp_pixeldata{
	uint8_t *pixel_data;
};

#pragma pack(pop)

#endif

