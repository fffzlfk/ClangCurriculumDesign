#include <math.h>
#include <stdio.h>
#include <Windows.h>

int main(int argc, char *argv[]) {
    // 获取命令行参数
    FILE *src_file = fopen(argv[1], "rb");
    if (src_file == NULL) return -1;

    BITMAPFILEHEADER file_head;
    fread(&file_head, sizeof(BITMAPFILEHEADER), 1, src_file);
    BITMAPINFOHEADER info_head;
    fread(&info_head, sizeof(BITMAPINFOHEADER), 1, src_file);

    int width = info_head.biWidth;
    int height = info_head.biHeight;
    int bi_count = info_head.biBitCount;

    RGBQUAD *color_table = new RGBQUAD[256];
    fread(color_table, sizeof(RGBQUAD), 256, src_file);

    int line_byte = (width * bi_count / 8 + 3) / 4 * 4;
    unsigned char *origin_buf = new unsigned char[line_byte * height];
    fread(origin_buf, line_byte * height, 1, src_file);

    fclose(src_file);

    // 缩放大小
    double scale = atoi(argv[2]) / 100.0;

    // 缩放后的图片大小
    int new_width = round(width * scale);
    int new_height = round(height * scale);
    int new_line_byte = (new_width * bi_count / 8 + 3) / 4 * 4;

    unsigned char *res_buf = new unsigned char[new_line_byte * new_height];
    for (int i = 0; i < new_height; i++)
        for (int j = 0; j < new_width; j++) {
            unsigned char *p = (unsigned char *)(res_buf + new_line_byte * i + j);
            (*p) = 255;
        }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            int x = round(scale * j);
            int y = round(scale * i);
            unsigned char *p1 = (unsigned char *)(origin_buf + i * line_byte + j);
            unsigned char *p2 = (unsigned char *)(res_buf + y * new_line_byte + x);
            (*p2) = (*p1);
        }

    FILE *out_file = fopen(argv[3], "wb");
    if (out_file == NULL) return -1;

    // 新位图头
    BITMAPFILEHEADER res_file_head;
    res_file_head.bfOffBits = 14 + 40 + 1024;
    res_file_head.bfReserved1 = 0;
    res_file_head.bfReserved2 = 0;
    res_file_head.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                           1024 + new_line_byte * new_height;
    res_file_head.bfType = 0x4D42;
    fwrite(&res_file_head, sizeof(res_file_head), 1, out_file);

    BITMAPINFOHEADER res_info_head;
    res_info_head.biBitCount = bi_count;
    res_info_head.biClrImportant = 0;
    res_info_head.biClrUsed = 0;
    res_info_head.biCompression = 0;
    res_info_head.biHeight = new_height;
    res_info_head.biPlanes = 1;
    res_info_head.biSize = 40;
    res_info_head.biSizeImage = new_line_byte * new_height;
    res_info_head.biWidth = new_width;
    res_info_head.biXPelsPerMeter = 0;
    res_info_head.biYPelsPerMeter = 0;

    // 写入文件
    fwrite(&res_info_head, sizeof(BITMAPINFOHEADER), 1, out_file);

    fwrite(color_table, sizeof(RGBQUAD), 256, out_file);

    fwrite(res_buf, new_line_byte * new_height, 1, out_file);

    fclose(out_file);
    
    return 0;
}
