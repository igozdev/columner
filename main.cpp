#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include <string>

void generate_column_image(
	const int resx, const int resy,
	const int margin_left, const int margin_top,
	const int num_maj, const int num_mid, const int num_min, const int maj_len, const int mid_len, const int min_len, const int stride,
	const int num_vert, const int stride_vert,
	const int col_maj, const int col_mid, const int col_min, const int col_vert,
	const std::string& path)
{
	std::vector<unsigned char> pixels(resx * resy * 3, 255);
	auto get_pixel = [&pixels, resx, resy](const int x, const int y) -> unsigned char* {
			return pixels.data() + (x * 3 + resx * y * 3);
		};
	const int horz_len = stride_vert * num_vert + 1;

	enum { min, mid, maj, done } state;
	auto count = [&state, num_min, num_mid, num_maj]() -> void {
			static int count_min = 0;
			static int count_mid = 0;
			static int count_maj = 0;
			
			if (count_maj == num_maj) {
				state = done;
			}
			else if (count_mid == num_mid && count_min == num_min) {
				state = maj;
				count_mid = 0;
				count_min = 0;
				count_maj++;
			}
			else if (count_min == num_min) {
				state = mid;
				count_min = 0;
				count_mid++;
			}
			else {
				state = min;
				count_min++;
			}
		};
	
	for (int k = 1; k < maj_len + 1; k++)
	{
		get_pixel(margin_left - k, margin_top)[0] = 0;
		get_pixel(margin_left - k, margin_top)[1] = 0;
		get_pixel(margin_left - k, margin_top)[2] = 0;
	}
	for (int k = 1; k < horz_len; k++) // 
	{
		get_pixel(margin_left + k, margin_top)[0] = col_maj;
		get_pixel(margin_left + k, margin_top)[1] = col_maj;
		get_pixel(margin_left + k, margin_top)[2] = col_maj;
	}

	int y_end = 0;
	for (int y = margin_top + 1; y < resy; y += stride, count())
	{
		int color;
		int max;
		switch (state)
		{
		case min:
			max = min_len;
			color = col_min;
			break;
		case mid:
			max = mid_len;
			color = col_mid;
			break;
		case maj:
			max = maj_len;
			color = col_maj;
			break;
		case done:
			y_end = y - stride;
			goto l_out;
		default:
			continue;
		}
		
		for (int k = 1; k < max + 1; k++)
		{
			get_pixel(margin_left - k, y)[0] = 0;
			get_pixel(margin_left - k, y)[1] = 0;
			get_pixel(margin_left - k, y)[2] = 0;
		}
		for (int k = 1; k < horz_len; k++) // 
		{
			get_pixel(margin_left + k, y)[0] = color;
			get_pixel(margin_left + k, y)[1] = color;
			get_pixel(margin_left + k, y)[2] = color;
		}
	}
l_out:

	for (int y = margin_top; y < y_end + 1; y++)
	{
		get_pixel(margin_left, y)[0] = 0;
		get_pixel(margin_left, y)[1] = 0;
		get_pixel(margin_left, y)[2] = 0;
	}

	for (int cx = 1; cx < num_vert + 1; cx++)
	{
		int x = margin_left + stride_vert * cx;
		for (int y = y_end - 1; y > margin_top; y--)
		{
			get_pixel(x, y)[0] = col_vert;
			get_pixel(x, y)[1] = col_vert;
			get_pixel(x, y)[2] = col_vert;
		}
	}
	for (int x = margin_left; x < horz_len + margin_left; x++)
	{
		get_pixel(x, y_end)[0] = 0;
		get_pixel(x, y_end)[1] = 0;
		get_pixel(x, y_end)[2] = 0;
	}

	stbi_write_png(path.c_str(), resx, resy, 3, pixels.data(), resx * 3);
}

int main(int argc, char** argv)
{
	if (argc != 19) {
		return -1;
	}
	const int resx = std::stoi(argv[1]);
	const int resy = std::stoi(argv[2]);
	const int margin_left = std::stoi(argv[3]);
	const int margin_top = std::stoi(argv[4]);
	const int num_maj = std::stoi(argv[5]);
	const int num_mid = std::stoi(argv[6]);
	const int num_min = std::stoi(argv[7]);
	const int maj_len = std::stoi(argv[8]);
	const int mid_len = std::stoi(argv[9]);
	const int min_len = std::stoi(argv[10]);
	const int stride = std::stoi(argv[11]);
	const int num_vert = std::stoi(argv[12]);
	const int stride_vert = std::stoi(argv[13]);
	const int col_maj = std::stoi(argv[14]);
	const int col_mid = std::stoi(argv[15]);
	const int col_min = std::stoi(argv[16]);
	const int col_vert = std::stoi(argv[17]);
	const std::string path = argv[18];

	generate_column_image(
		resx, resy,
		margin_left, margin_top,
		num_maj, num_mid, num_min, maj_len, mid_len, min_len, stride,
		num_vert, stride_vert,
		col_maj, col_mid, col_min, col_vert,
		path);
}