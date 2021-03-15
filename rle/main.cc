#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <regex>

int main(int argc, char *argv[]) {
    // 检验命令行参数个数是否合法
    assert(argc == 4);

    std::vector<std::string> vec;
    vec.assign(argv + 1, argv + argc);

    std::string cmd = "";
    for (const auto &e : vec)
        cmd += e + ' ';
    cmd.pop_back();
    
    // 检验命令是否合法
    std::regex txt_regex("[a-zA-Z0-9.-_-]+ -[c|d] [a-zA-Z0-9.-_-]+");
    assert(std::regex_match(cmd, txt_regex));

    std::ifstream origin(argv[1], std::ios::in);
    std::ofstream output(argv[3], std::ios::out);
    
    // 压缩
    auto compress = [&]() {
        char pre = origin.get();
        int cnt = 1;
        char c;
        while ((c = origin.get()) != EOF) {
            if (c == pre) ++cnt;
            else {
                output << std::to_string(cnt) + pre;
                cnt = 1;
            }
            pre = c;
        }
        output << std::to_string(cnt) + pre;
    };

    // 解压
    auto decompress = [&]() {
        int cnt = 0;
        char c;
        while ((c = origin.get()) != EOF) {
            if (!isdigit(c)) {
                output << std::string(cnt, c);
                cnt = 0;
            } else {
                cnt = cnt * 10 + c - '0';
            }
        }
    };

    if (argv[2][1] == 'c') {
        compress();
    } else if (argv[2][1] == 'd') {
        decompress();
    }

    origin.close();
    output.close();
    return 0;
}