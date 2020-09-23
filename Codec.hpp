#ifndef CODEC_HPP_
#define CODEC_HPP_

#include <string>
#include <array>

// 被统计的字符的范围(0-127)
const int CharNum = 128;

std::array<uint32_t, CharNum> Stats(const std::string& filename)
{
    std::array<uint32_t, CharNum> chrFreq;
    FILE* fp = fopen(filename.c_str(), "r");
    char ch;
    while (fscanf(fp, "%c", &ch)) {
        chrFreq[static_cast<int>(ch)]++;
    }
    fclose(fp);
    return chrFreq;
}

#endif  // CODEC_HPP_