/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
//
// Created by Vlada on 11/4/2025.
//

#include "uiparser.h"

#include <variant>

namespace v::parser {
    char UiParser::xctPeek() {
        file_.value() >> std::ws;
        return file_.value().peek();
    }

    bool UiParser::xctConsume() {
        file_.value() >> std::ws;
        file_.value().ignore(1);
        return true;
    }

    bool UiParser::xctCheck(const char arg_chara) {
        file_.value() >> std::ws;
        return file_.value().peek() == arg_chara;
    }

    bool UiParser::xctCheckEof() const { return  file_.value().eof(); }

    std::string UiParser::xctReadString() {
        std::string retstr;
        while(true) {
            sPeekCheckRes peekcheckres = xctPeekCheckConsume('\"');
            if(xctCheckEof() || peekcheckres == true) {
                break;
            }
            retstr.append(peekcheckres.value());
        }
        return retstr;
    }

    UiParser::sPeekCheckRes UiParser::xctPeekCheckConsume(const std::optional<char> check) {
        file_.value() >> std::ws;
        char a;
        file_.value() >> a;
        return sPeekCheckRes{a , check.has_value() && check.value() == a};
    }

    std::optional<common::sUiError> UiParser::xctExpect() {
        if(!expect_[state_].has_value()) { return std::nullopt; }
        if(std::holds_alternative<std::vector<char>>(expect_[state_].value())) {
            const std::vector<char>& charavec = std::get<std::vector<char>>(expect_[state_].value());
            for(const char chara : charavec) {
                sPeekCheckRes result = xctPeekCheckConsume(chara);
                if(xctCheck(chara)) { xctConsume(); }
                else { return common::sUiError{common::eErrorType::COMMON , "UNEXPECTED" + chara}; }
            }
        }
        else {
            std::unordered_map<char , eState>& charamap = std::get<std::unordered_map<char , eState>>(expect_[state_].value());
            sPeekCheckRes result = xctPeekCheckConsume()
            if(charamap.find(xctPeek()) != charamap.end()) {
                ;
                state_ = charamap.at(xctPeek());
                xctConsume();
            }
            else { return common::sUiError{common::eErrorType::COMMON , "UNEXPECTED" + xctPeek()}; }
        }
        return std::nullopt;
    }

    common::ui_screen_TD UiParser::xctGetUi() {
        file_ = std::fstream(path_);
        if(!file_.has_value() || !file_.value().is_open()) { return common::sUiError(common::eErrorType::COMMON,
            "Cannot open " + path_); }
        while(true) {
            ui_line_TD line = xctGetLine();
            if(std::holds_alternative<common::sUiError>(line)) {
                return std::get<common::sUiError>(line);
            }
        }
    }

    UiParser::ui_line_TD UiParser::xctGetLine() {
        while(true) {
            sLine         line;
            if(state_ == eState::MTT) {

            }
            if(peek_check_res == true) {
                continue;
            }
            switch(xctPeekCheckConsume(std::nullopt)) {
                //key symbols
                case '[': // BEGLINE
                    scope_++;
                    break;
                case ']': //ENDLINE
                    scope_--;
                    if(scope_ <= 0) {
                        state_ = eState::MTT;
                        return {};
                    }
                    break;
                case '>': //SEND|COMMIT
                    state_ = eState::SEND_COMMIT;
                    if(xctCheck('>')) {
                        state_ = eState::COMMIT;
                        xctConsume();
                    } else {state_ = eState::SEND;}
                    break;
                case '<': //SET|GET
                    state_ = eState::SET_GET;
                    if(xctCheck('<')) {
                        state_ = eState::GET;
                        xctConsume();
                    } else {state_ = eState::SET;}
                    break;
                case '|': //REPEAT (UNPACK)
                    state_ = eState::REPEAT;
                    break;
                case ':': //ACCESS|?
                    if(xctCheck(':')) {
                        state_ = eState::ACCESS;
                        xctConsume();
                    } else {
                        return common::sUiError{common::eErrorType::COMMON, "UNEXPECTED" + xctPeek()};
                    }
                    break;
                case '\"': //STRING|?
                    break;
                //keywords
                case 'X': //XBEG|XEND|?
                    break;
                case 'E': //EXIT|?
                    break;
                case 'O': //OPEN|?
                    break;
                case 'L': //LOAD|?
                    break;
                case 'M': //MAKE|?
                    break;
                case 'S': //SETX|SHOW?
                    break;
                case 'P': //PACK|?
                    break;
                case 'U': //UNPK|?
                    break;
                case 'N': //NVBX|?
                    break;
                case 'F': //FREE|?
                    break;
                case 'W': //WAIT|?
                    break;
            }
        }
    }

}
/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
