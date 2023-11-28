#ifndef BMP_H
#define BMP_H

/**
 * @brief This function saves an 8-bit color bitmap image.
 * 
 * @param[in] array - array of pixels, each pixel is represented by 1 byte
 * @param[in] width - width of the image
 * @param[in] height - height of the image
 * @param[in] filename - name of the file
 * 
 * @return void
 */
void save_8bit_color_bitmap(unsigned char *array, unsigned int width, unsigned int height, const char *filename);

#endif /* BMP_H */