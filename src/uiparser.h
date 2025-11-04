/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
#pragma once
#include <string>
#include <vector>

#include "common.h"

namespace v::parser {
    class UiParser {
        std::string path;
        enum class eLineType{MTT , ACT, DAT};
        enum class eACT{XBEG, XEND, EXIT, OPEN, LOAD, XTPT, MAKE, SETX, PACK, UNPK, NVBX, SHOW};
        struct sLine {

        };
        public:
            UiParser()                           = delete;
            UiParser(const UiParser&)            = delete;
            UiParser(UiParser&&)                 = delete;
            UiParser& operator=(const UiParser&) = delete;
            UiParser& operator=(UiParser&&)      = delete;
            explicit  UiParser(std::string arg_path) : path(std::move(arg_path)) {}
            common::sUiScreen xctGetUi();
            void GetLine();
    };
}
/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
