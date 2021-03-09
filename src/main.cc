#include "tgaimage.h"
#include <stdlib.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

// 这种方法会造成在较大的x或者y值欠采样
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
// 	for (int x = x0; x <= x1; x++) {
// 		float t = (x - x0) / (float)(x1 - x0);
// 		int y = y0 * (1. - t) + y1 * t;
// 		image.set(x, y, color);
// 	} 
// }

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {   // 从左到右
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int x = x0; x < x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		if (steep) {
			image.set(y, x, color);
		} else {
			image.set(x, y, color);
		}
	}
}

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {   // 从左到右
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = std::abs(dy / float(dx));
	float error = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		} else {
			image.set(x, y, color);
		}
		error += derror;
		if (error >.5) {
			y += (y1 > y0 ? 1 : -1);
			error -= 1.;
		}
	}
}

int main() {
	TGAImage image(100, 100, TGAImage::RGB);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	image.write_tga_file("output.tga");
	return 0;
}
