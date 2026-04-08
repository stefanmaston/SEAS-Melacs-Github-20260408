#include <stdlib.h>
#include "Utils.h"
#include "STBImage.h"


/******************************************************************************
 * Convert the pixel depth to 16-bits and write the output to a C data file
 ******************************************************************************/
static unsigned Direct(unsigned value, int straightbits) {
	if(!straightbits) {
		value = 
			value >>  7 & 0x0101U |
			value >>  5 & 0x0202U |
			value >>  3 & 0x0404U |
			value >>  1 & 0x0808U |
			value <<  1 & 0x1010U |
			value <<  3 & 0x2020U |
			value <<  5 & 0x4040U |
			value <<  7 & 0x8080U;
	}
	return value;
}

static void Convert(FILE *output, const unsigned char *input, unsigned xres,
	unsigned yres, const char *name, int straightbits) {
	unsigned x, y;
	const char *prefix;
	unsigned column;

	fprintf (
		output,
		"/* %ux%u (%u bytes) */\n"
		"const rom unsigned char %s[] =\n"
		"{\n"
		"\t0x%02X, 0x%02X, 0x%02X",
		xres, yres, 3 + xres * yres * 2,
		name,
		xres & 0xFF, xres >> 8, yres
	);

	prefix = ",\n\t";
	column = 0;

	for(y = 0; y < yres; ++y) {
		for(x = 0; x < xres; ++x) {
			unsigned pixel;

			unsigned r = *input++ >> 3;
			unsigned g = *input++ >> 2;
			unsigned b = *input++ >> 3;

			pixel = r << 11 | g << 5 | b << 0;
			pixel = Direct(pixel, straightbits);

			fprintf (
				output,
				"%s0x%02X, 0x%02X",
				prefix,
				pixel >> 8,
				pixel & 0xFF
			);

			if(++column % 6)
				prefix = ", ";
			else
				prefix = ",\n\t";
		}
	}

	fprintf (
		output,
		"\n"
		"};"
	);
}


/******************************************************************************
 * Parse the command line and safe-guard the conversion
 ******************************************************************************/
int DECL_VARARGS main(int argc, char *argv[]) {
	volatile int status = EXIT_FAILURE;

	if(argc != 3) {
		fprintf(stderr, "syntax: %s {image} {straightbits}\n", argv[0]);
	} else {
		// Load the image
		int xres, yres;
		char *path = argv[1];
		int straightbits = atoi(argv[2]);
		unsigned char *pixels = stbi_load(path, &xres, &yres, NULL, 3);

		if(!pixels)
			fprintf(stderr, "error: cannot load image '%s': %s\n",
				path, stbi_failure_reason());
		else {
			// Create output file
			char name[FILENAME_MAX];
			char outpath[FILENAME_MAX];

			PathOf(path, name, sizeof name);
			safe_snprintf(outpath, sizeof outpath, "%s%s.c", path, name);

			if(freopen(outpath, "w", stdout)) {
				// Finally perform the actual conversion
				Convert(stdout, pixels, xres, yres, name, straightbits);

				if(!ferror(stdout))
					status = EXIT_SUCCESS;
			}

			free(pixels);
		}
	}

	return status;
}