/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include "common.h"

namespace v::parser {
    class UiParser {
        std::string                 path_;
        std::optional<std::fstream> file_{};
        enum class eLineType { MTT , ACT , DAT , LOG };
        enum class eState {
            MTT
          , BEGINLINE
          , ENDLINE
          , SEND_COMMIT
          , SEND
          , COMMIT
          , SET_GET
          , SET
          , GET
          , REPEAT
          , ACCESS
          , STRING
          , XBEG_XEND
          , XBEG
          , XEND
          , EXIT
          , OPEN
          , LOAD
          , MAKE
          , SETX_SHOW
          , SETX
          , SHOW
          , PACK
          , UNPK
          , NVBX
          , FREE
          , WAIT
        };
        eState                                                                                                          state_{eState::MTT};
        int                                                                                                             scope_ = 0;
        std::unordered_map<eState , std::optional<std::variant<std::unordered_map<char , eState> , std::vector<char>>>> expect_{
            {{eState::BEGINLINE} , {std::nullopt}}
          , {{eState::ENDLINE} , {std::nullopt}}
          , {{eState::SEND_COMMIT} , {std::nullopt}}
          , {{eState::SEND} , {std::nullopt}}
          , {{eState::COMMIT} , {std::nullopt}}
          , {{eState::SET_GET} , {std::nullopt}}
          , {{eState::SET} , {std::nullopt}}
          , {{eState::GET} , {std::nullopt}}
          , {{eState::REPEAT} , {std::nullopt}}
          , {{eState::ACCESS} , {std::nullopt}}
          , {{eState::STRING} , {std::nullopt}}
          , {{eState::XBEG_XEND} , {std::nullopt}}
          , {{eState::XBEG} , {std::nullopt}}
          , {{eState::XEND} , {std::nullopt}}
          , {{eState::EXIT} , {std::nullopt}}
          , {{eState::OPEN} , {std::nullopt}}
          , {{eState::LOAD} , {std::nullopt}}
          , {{eState::MAKE} , {std::nullopt}}
          , {{eState::SETX_SHOW} , {std::nullopt}}
          , {{eState::SETX} , {std::nullopt}}
          , {{eState::SHOW} , {std::nullopt}}
          , {{eState::PACK} , {std::nullopt}}
          , {{eState::UNPK} , {std::nullopt}}
          , {{eState::NVBX} , {std::nullopt}}
          , {{eState::FREE} , {std::nullopt}}
          , {{eState::WAIT} , {std::nullopt}}};
        struct sLine {
            eLineType            _type{eLineType::MTT};
            common::eAct         _act{common::eAct::MTT};
            std::optional<sLine> _next{};
        };
        using ui_line_TD = std::variant<common::sUiError , sLine>;

        ui_line_TD xctGetLine();

        struct sPeekCheckRes {
            bool operator==(const bool arg_rhs) const { return equal == arg_rhs; }
            bool operator!=(const bool arg_rhs) const { return !(*this == arg_rhs); }
            bool operator==(const char arg_rhs) const { return value == arg_rhs; }
            bool operator!=(const char arg_rhs) const { return !(*this == arg_rhs); }
            char value;
            bool equal;
        };

        char xctPeek();

        bool xctConsume();

        bool xctCheck(const char arg_chara);

        bool xctCheckEof() const;

        std::string xctReadString();

        sPeekCheckRes xctPeekCheckConsume(const std::optional<char> check);

        std::optional<common::sUiError> xctExpect();
        public:
            UiParser()                                      = delete;
            UiParser(const UiParser&)                       = delete;
            UiParser(UiParser&&)                            = delete;
            UiParser&            operator=(const UiParser&) = delete;
            UiParser&            operator=(UiParser&&)      = delete;
            explicit             UiParser(std::string arg_path) : path_(std::move(arg_path)) {}
            common::ui_screen_TD xctGetUi();
    };
}
/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
