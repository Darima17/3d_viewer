/*****************************************************************************
gif_err.c - handle error reporting for the GIF library.
****************************************************************************/

#include <stdio.h>

#include "gif_lib.h"
#include "gif_lib_private.h"

/*****************************************************************************
 Return a string description of  the last GIF error
*****************************************************************************/
char *
GifErrorString(int ErrorCode)
{
    char *Err;

    switch (ErrorCode) {
      case E_GIF_ERR_OPEN_FAILED:
        Err = (char*)"Failed to open given file";
        break;
      case E_GIF_ERR_WRITE_FAILED:
        Err = (char*)"Failed to write to given file";
        break;
      case E_GIF_ERR_HAS_SCRN_DSCR:
        Err = (char*)"Screen descriptor has already been set";
        break;
      case E_GIF_ERR_HAS_IMAG_DSCR:
        Err = (char*)"Image descriptor is still active";
        break;
      case E_GIF_ERR_NO_COLOR_MAP:
        Err = (char*)"Neither global nor local color map";
        break;
      case E_GIF_ERR_DATA_TOO_BIG:
        Err = (char*)"Number of pixels bigger than width * height";
        break;
      case E_GIF_ERR_NOT_ENOUGH_MEM:
        Err = (char*)"Failed to allocate required memory";
        break;
      case E_GIF_ERR_DISK_IS_FULL:
        Err = (char*)"Write failed (disk full?)";
        break;
      case E_GIF_ERR_CLOSE_FAILED:
        Err = (char*)"Failed to close given file";
        break;
      case E_GIF_ERR_NOT_WRITEABLE:
        Err = (char*)"Given file was not opened for write";
        break;
      case D_GIF_ERR_OPEN_FAILED:
        Err = (char*)"Failed to open given file";
        break;
      case D_GIF_ERR_READ_FAILED:
        Err = (char*)"Failed to read from given file";
        break;
      case D_GIF_ERR_NOT_GIF_FILE:
        Err = (char*)"Data is not in GIF format";
        break;
      case D_GIF_ERR_NO_SCRN_DSCR:
        Err = (char*)"No screen descriptor detected";
        break;
      case D_GIF_ERR_NO_IMAG_DSCR:
        Err = (char*)"No Image Descriptor detected";
        break;
      case D_GIF_ERR_NO_COLOR_MAP:
        Err = (char*)"Neither global nor local color map";
        break;
      case D_GIF_ERR_WRONG_RECORD:
        Err = (char*)"Wrong record type detected";
        break;
      case D_GIF_ERR_DATA_TOO_BIG:
        Err = (char*)"Number of pixels bigger than width * height";
        break;
      case D_GIF_ERR_NOT_ENOUGH_MEM:
        Err = (char*)"Failed to allocate required memory";
        break;
      case D_GIF_ERR_CLOSE_FAILED:
        Err = (char*)"Failed to close given file";
        break;
      case D_GIF_ERR_NOT_READABLE:
        Err = (char*)"Given file was not opened for read";
        break;
      case D_GIF_ERR_IMAGE_DEFECT:
        Err = (char*)"Image is defective, decoding aborted";
        break;
      case D_GIF_ERR_EOF_TOO_SOON:
        Err = (char*)"Image EOF detected before image complete";
        break;
      default:
        Err = NULL;
        break;
    }
    return Err;
}

/* end */