//
// Created by adun on 2017. 11. 20..
//

#include <GL/glut.h>     // ¶Ç´Â <GL/feeeglut.h> 
#include <string>
#include "FreeImage.h"

        static BYTE* load_image(const char* fileName, GLsizei* width, GLsizei* height, unsigned int* bits)
        {
            FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

            FIBITMAP* dib = nullptr;

            fif = FreeImage_GetFileType(fileName, 0);

            if (fif == FIF_UNKNOWN)
                fif = FreeImage_GetFIFFromFilename(fileName);

            if (fif == FIF_UNKNOWN)
                return nullptr;

            if (FreeImage_FIFSupportsReading(fif))
                dib = FreeImage_Load(fif, fileName);

            if (!dib)
            {
                
                return nullptr;
            }

            BYTE* pixels = FreeImage_GetBits(dib);

            *width  = FreeImage_GetWidth(dib);

            *height = FreeImage_GetHeight(dib);

            *bits   = FreeImage_GetBPP(dib);

            int size = *width * *height * (*bits / 8);

            BYTE* result = new BYTE[size];

            memcpy(result, pixels, size);

            FreeImage_Unload(dib);


            return result;
        }
