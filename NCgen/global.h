#pragma once
#include <iostream>
#include <string>

extern std::string content;
extern std::string post_content;

void console_log(std::string text) {
    printf((text + "\n").c_str());
}

void append_content(std::string appendthis) {
    content = content + appendthis;
}

void append_content_post(std::string appendthis) {
    post_content = post_content + appendthis;
}

void apply_post_content() {
    content = content + post_content;
}