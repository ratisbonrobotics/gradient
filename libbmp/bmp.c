#include "bmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static void save_8bit_color_bitmap_internal(unsigned char *data, unsigned int width, unsigned int height, const char *filename, bool use_rle)
{
    // Initialize a 14-byte array to hold the BMP file header.
    uint8_t header[14] = {
        'B', 'M',   // BMP signature
        0, 0, 0, 0, // Placeholder for file size, filled in later
        0, 0,       // Reserved field, always set to 0
        0, 0,       // Reserved field, always set to 0
        0, 0, 0, 0  // Offset from beginning of file to the pixel array
    };

    // Initialize a 40-byte array for the BMP info header.
    uint8_t info_header[40] = {
        40, 0, 0, 0, // The size of this header (40 bytes)
        0, 0, 0, 0,  // Image width, filled in later
        0, 0, 0, 0,  // Image height, filled in later
        1, 0,        // Number of color planes (always 1)
        8, 0,        // Bits per pixel (8 for 256 colors)
        0, 0, 0, 0,  // No compression as the default
        0, 0, 0, 0,  // Placeholder for image size, filled in later
        0, 0, 0, 0,  // Horizontal resolution, not significant
        0, 0, 0, 0,  // Vertical resolution, not significant
        0, 0, 0, 0,  // Number of colors in palette (0 means 2^8)
        0, 0, 0, 0   // Number of "important" colors, 0 when every color is important
    };

    // Set compression mode: 0 for no compression, 1 for RLE 8-bit
    info_header[16] = use_rle ? 1 : 0;

    // Calculate the padded row size in bytes.
    unsigned int row_size = (width + 3) & (~((unsigned int)3)); // Align to 4 bytes

    // Calculate the total image data size in bytes.
    unsigned int image_size = row_size * height;

    // Calculate the overall file size.
    unsigned int file_size = 1078 + image_size;

    // Update the file size, image width, and height in the header.
    header[2] = (uint8_t)(file_size);
    header[3] = (uint8_t)(file_size >> 8);
    header[4] = (uint8_t)(file_size >> 16);
    header[5] = (uint8_t)(file_size >> 24);

    info_header[4] = (uint8_t)(width);
    info_header[5] = (uint8_t)(width >> 8);
    info_header[8] = (uint8_t)(height);
    info_header[9] = (uint8_t)(height >> 8);

    // Offset where the pixel array (data) starts, 1078 bytes from the start of the file.
    header[10] = (uint8_t)(1078);
    header[11] = (uint8_t)(1078 >> 8);
    header[12] = (uint8_t)(1078 >> 16);
    header[13] = (uint8_t)(1078 >> 24);

    // Update the image size in the info header.
    info_header[20] = (uint8_t)(image_size);
    info_header[21] = (uint8_t)(image_size >> 8);
    info_header[22] = (uint8_t)(image_size >> 16);
    info_header[23] = (uint8_t)(image_size >> 24);

    // Initialize 256-color table (4 bytes per color: B, G, R, 0)
    uint8_t colorTable[1024]; // 256 colors * 4 bytes/color = 1024 bytes

    for (unsigned int i = 0; i < 256; i++)
    {
        unsigned int idx = i * 4;

        if (i <= 85)
        {
            // Red gradient from dark to bright
            colorTable[idx] = 0;
            colorTable[idx + 1] = 0;
            colorTable[idx + 2] = (uint8_t)(i * 3); // Scale up to use full 0-255 range
        }
        else if (i <= 170)
        {
            // Green gradient from dark to bright
            colorTable[idx] = 0;
            colorTable[idx + 1] = (uint8_t)((i - 85) * 3); // Scale up
            colorTable[idx + 2] = 0;
        }
        else if (i < 255)
        {
            // Blue gradient from dark to bright
            colorTable[idx] = (uint8_t)((i - 170) * 3); // Scale up
            colorTable[idx + 1] = 0;
            colorTable[idx + 2] = 0;
        }
        else
        {
            // 255 is white
            colorTable[idx] = 255;
            colorTable[idx + 1] = 255;
            colorTable[idx + 2] = 255;
        }
        colorTable[idx + 3] = 0; // Alpha channel, unused in most BMPs
    }

    // Open a binary file for writing.
    FILE *file = fopen(filename, "wb");

    // Check if the file was successfully created.
    if (!file)
        return;

    // Write the 14-byte file header to the file.
    (void)fwrite(header, 1, 14, file);

    // Write the 40-byte info header to the file.
    (void)fwrite(info_header, 1, 40, file);

    // Write the 1024-byte color table to the file.
    (void)fwrite(colorTable, 1, 1024, file);

    // Write the pixel data
    if (use_rle)
    {
        // Begin RLE compression and writing pixel data
        for (unsigned int y = height; y != 0; y--)
        {
            unsigned int x = 0;
            while (x < width)
            {
                unsigned char pixel = data[(y - 1) * width + x];
                unsigned char runLength = 1;

                // Count how many consecutive pixels are the same color
                while (x + runLength < width && runLength < 255 && data[(y - 1) * width + x + runLength] == pixel)
                {
                    runLength++;
                }

                // Write the run length and pixel value to the file
                (void)fwrite(&runLength, 1, 1, file);
                (void)fwrite(&pixel, 1, 1, file);

                x += runLength;
            }

            // Write the End-of-Line RLE codes
            unsigned char endOfLine[2] = {0, 0};
            (void)fwrite(&endOfLine, 1, 2, file);
        }

        // Write the End-of-Bitmap RLE codes
        unsigned char endOfBitmap[2] = {0, 1};
        (void)fwrite(&endOfBitmap, 1, 2, file);
    }
    else
    {
        // Write the raw pixel data.
        for (unsigned int y = height; y != 0; y--)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                (void)fwrite(&data[(y - 1) * width + x], 1, 1, file);
            }
            // Padding for 4-byte alignment.
            for (unsigned int x = width; x < row_size; x++)
            {
                uint8_t padding = 0;
                (void)fwrite(&padding, 1, 1, file);
            }
        }
    }

    // Close the file to finalize writing.
    (void)fclose(file);
}

void save_8bit_color_bitmap(unsigned char *data, unsigned int width, unsigned int height, const char *filename)
{
    // Calculate average run length
    int run_count = 1;       // Counter for each run
    int total_runs = 0;      // Total number of runs
    double total_length = 0; // Sum of all run lengths

    for (unsigned int i = 1; i < width * height; ++i)
    {
        if (data[i] == data[i - 1])
        {
            run_count++;
        }
        else
        {
            total_length += run_count;
            total_runs++;
            run_count = 1; // Reset for the next run
        }
    }

    // Add the last run
    total_length += run_count;
    total_runs++;

    // Calculate the average run length
    double average_run_length = total_length / total_runs;

    // Use RLE if the average run length is at least 2
    save_8bit_color_bitmap_internal(data, width, height, filename, (average_run_length >= 2.0));
}
