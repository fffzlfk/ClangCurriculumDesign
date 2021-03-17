#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

int main(int argc, char** argv) {
    assert(argc == 3);

    FILE* fp = fopen(argv[1], "rb");
    if (fp == 0) return -1;

    // 读取位图文件头
    BITMAPFILEHEADER fileHead;
    fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

    // 读取位图信息头
    BITMAPINFOHEADER infoHead;
    fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
    int width = infoHead.biWidth;
    int height = infoHead.biHeight;
    int biCount = infoHead.biBitCount;

    int lineByte = (biCount * width / 8 + 3) / 4 * 4;

    // 读取颜色表
    RGBQUAD* pColorTable = new RGBQUAD[256];
    fread(pColorTable, sizeof(RGBQUAD), 256, fp);

    // 读取位图数据
    unsigned char* originBmpBuf = new unsigned char[lineByte * height];
    fread(originBmpBuf, lineByte * height, 1, fp);
    fclose(fp);

    // 统计概率
    double Pr[256] = {0};
    int Tr[256] = {0};
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int t = *(originBmpBuf + i * lineByte + j);
            Pr[t]++;
        }
    }
    // 计算累加直方图并完成映射
    Pr[0] = Pr[0] / (width * height);
    Tr[0] = round(double((256 - 1) * Pr[0]));
    for (int i = 1; i < 256; ++i) {
        Pr[i] = Pr[i] / (width * height);
        Pr[i] = Pr[i] + Pr[i - 1];
        Tr[i] = int(round(double((256 - 1) * Pr[i])));
    }

    // 新图像的像素填充
    unsigned char* resBmpBuf = new unsigned char[lineByte * height];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int t = *(originBmpBuf + i * lineByte + j);
            *(resBmpBuf + i * lineByte + j) = Tr[t];
        }
    }

    FILE* fop = fopen(argv[2], "wb");
    if (fop == 0) return -1;
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fop);
    fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fop);
    fwrite(pColorTable, sizeof(RGBQUAD), 256, fop);
    fwrite(resBmpBuf, lineByte * height, 1, fop);
    fclose(fop);
    return 0;
}
