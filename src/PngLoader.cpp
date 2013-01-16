/*
 * PngLoader.cpp
 *
 *  Created on: 2 janv. 2013
 *      Author: nathan*/


#include "PngLoader.h"

PngLoader::PngLoader() {
	// TODO Auto-generated constructor stub

}

PngLoader::~PngLoader() {
	// TODO Auto-generated destructor stub
}

void PngLoader::GetPNGtextureInfo (int color_type, MTEX *texinfo)
{
        switch (color_type) {
        case PNG_COLOR_TYPE_GRAY:
                texinfo->format = GL_LUMINANCE;
                texinfo->internalFormat = 1;
                break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
                texinfo->format = GL_LUMINANCE_ALPHA;
                texinfo->internalFormat = 2;
                break;

        case PNG_COLOR_TYPE_RGB:
                texinfo->format = GL_RGB;
                texinfo->internalFormat = 3;
                break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
                texinfo->format = GL_RGBA;
                texinfo->internalFormat = 4;
                break;

        default:
                /* Badness */
                break;
        }
}


int PngLoader::ReadPNGFromFile (MTEX *texinfo)
{
        png_byte magic[8];
        png_structp png_ptr;
        png_infop info_ptr;
        int bit_depth, color_type;
        FILE *fp = NULL;
        png_bytep *row_pointers = NULL;
        int i;

        /* open image file */
        fp = fopen (texinfo->filename, "rb");
        if (!fp) {
                printf( "error: couldn't open \"%s\"!\n", texinfo->filename);
				system("PAUSE");
                return -1;
        }

        /* read magic number */
        fread (magic, 1, sizeof (magic), fp);

        /* check for valid magic number */
        if (!png_check_sig (magic, sizeof (magic))) {
                printf( "error: \"%s\" is not a valid PNG image!\n",
                        texinfo->filename);
                fclose (fp);
				system("PAUSE");
                return -1;
        }

        /* create a png read struct */
        png_ptr = png_create_read_struct
                  (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr) {
                fclose (fp);
                return -1;
        }

        /* create a png info struct */
        info_ptr = png_create_info_struct (png_ptr);
        if (!info_ptr) {
                fclose (fp);
                png_destroy_read_struct (&png_ptr, NULL, NULL);
                return -1;
        }

        /* initialize the setjmp for returning properly after a libpng
           error occured */
        if (setjmp (png_jmpbuf (png_ptr))) {
                fclose (fp);
                png_destroy_read_struct (&png_ptr, &info_ptr, NULL);

                if (row_pointers)
                        free (row_pointers);

                /*if (texinfo)
                {
                if (texinfo->texels)
                free (texinfo->texels);

                free (texinfo);
                }*/

                return -1;
        }

        /* setup libpng for using standard C fread() function
           with our FILE pointer */
        png_init_io (png_ptr, fp);

        /* tell libpng that we have already read the magic number */
        png_set_sig_bytes (png_ptr, sizeof (magic));

        /* read png info */
        png_read_info (png_ptr, info_ptr);

        /* get some usefull information from header */
        bit_depth = png_get_bit_depth (png_ptr, info_ptr);
        color_type = png_get_color_type (png_ptr, info_ptr);

        /* convert index color images to RGB images */
        if (color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_palette_to_rgb (png_ptr);

        /* convert 1-2-4 bits grayscale images to 8 bits
           grayscale. */
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                png_set_expand_gray_1_2_4_to_8 (png_ptr);

        if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha (png_ptr);

        if (bit_depth == 16)
                png_set_strip_16 (png_ptr);
        else if (bit_depth < 8)
                png_set_packing (png_ptr);

        /* update info structure to apply transformations */
        png_read_update_info (png_ptr, info_ptr);

        /* retrieve updated information */
        png_get_IHDR (png_ptr, info_ptr,
                      (png_uint_32*)(&texinfo->width),
                      (png_uint_32*)(&texinfo->height),
                      &bit_depth, &color_type,
                      NULL, NULL, NULL);

        /* get image format and components per pixel */
        GetPNGtextureInfo (color_type, texinfo);

        /* we can now allocate memory for storing pixel data */
        texinfo->texels = (GLubyte *)malloc (sizeof (GLubyte) * texinfo->width
                                             * texinfo->height * texinfo->internalFormat);

        /* setup a pointer array.  Each one points at the begening of a row. */
        row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * texinfo->height);

        for (i = 0; i < texinfo->height; ++i) {
                row_pointers[i] = (png_bytep)(texinfo->texels +
                                              ((texinfo->height - (i + 1)) * texinfo->width * texinfo->internalFormat));
        }

        /* read pixel data using row pointers */
        png_read_image (png_ptr, row_pointers);

        /* finish decompression and release memory */
        png_read_end (png_ptr, NULL);
        png_destroy_read_struct (&png_ptr, &info_ptr, NULL);

        /* we don't need row pointers anymore */
        free (row_pointers);

        fclose (fp);
        return 0;
}
