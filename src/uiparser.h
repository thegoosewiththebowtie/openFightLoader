/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common.h"

namespace v::parser {
    class Parser {
        public:        std::string  path_;
        std::fstream file_;
        struct sLine {
            bool        _fail{false};
            bool _packed{false};
            std::string _line{""};
            uint32_t    _scope{0};
            sLine& operator+=(const char arg_rhs) {
                _line+=arg_rhs;
                return *this;
            }
        };
        bool                                xctFindControl(char arg_rhs);
        char                                xctPeek();
        char                                xctConsume();
        bool                                xctCheck(char arg_rhs);
        std::unique_ptr<std::vector<sLine>> xctFile2Lines();
        std::unique_ptr<std::vector<sLine>> xctUnpackLine(const sLine& arg_line);
        common::Act                         xctLine2Act(sLine arg_line);
        public:
            explicit             Parser(std::string arg_path): path_{std::move(arg_path)} {}
            common::ui_screen_TD xctGetScreen();
    };
}
/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
