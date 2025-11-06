/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
//
// Created by Vlada on 11/4/2025.
//

#include "uiparser.h"

#include <io.h>

namespace v::parser {
    struct UpCounter {
        int max;
        int min;
        int value;

        UpCounter() : max{0}
                  , min{0}
                  , value{0} {};

        UpCounter(const int arg_val) : max{arg_val}
                                   , min{arg_val}
                                   , value{arg_val} {};

        void Equalize() {
            min = std::min(min, value);
            max = std::max(max, value);
        }

        UpCounter& operator+=(const int arg_rhs) {
            value += arg_rhs;
            Equalize();
            return *this;
        }

        UpCounter& operator-=(const int arg_rhs) {
            value -= arg_rhs;
            Equalize();
            return *this;
        }

        UpCounter& operator++() {  // prefix
            ++value;
            Equalize();
            return *this;
        }

        UpCounter operator++(int) {  // postfix
            const UpCounter temp = *this;
            ++value;
            Equalize();
            return temp;
        }

        UpCounter& operator--() {  // prefix
            --value;
            Equalize();
            return *this;
        }

        UpCounter operator--(int) {  // postfix
            const UpCounter temp = *this;
            --value;
            Equalize();
            return temp;
        }
    };

    enum class eFile2LineState { ZERO , OPENING , READING , CLOSING };

    std::unique_ptr<std::vector<Parser::sLine>> Parser::xctFile2Lines() {
        char            c;
        UpCounter       scope = 0;
        eFile2LineState state = eFile2LineState::ZERO;
        std::unique_ptr retline{std::make_unique<std::vector<sLine>>()};
        sLine           current_line{};
        auto            l_xctSave = [&] {
            current_line._scope = scope.max;
            scope               = {};
            retline->push_back(std::move(current_line));
            current_line = {};
        };
        while(true) {
            file_ >> std::ws;
            file_ >> c;
            if(file_.eof()) { break; }
            if(c == '|') { current_line._packed = true; }
            switch(state) {
                case eFile2LineState::ZERO : switch(c) {
                        case '[' : state = eFile2LineState::OPENING;
                            ++scope;
                            break;
                        case ']' : [[fallthrough]];
                        default : break;
                    }
                    break;
                case eFile2LineState::OPENING : switch(c) {
                        case '[' : ++scope;
                            break;
                        case ']' : state = eFile2LineState::CLOSING;
                            break;
                        default : state = eFile2LineState::READING;
                            current_line += c;
                            break;
                    }
                    break;
                case eFile2LineState::READING : switch(c) {
                        case '[' : current_line._fail = true;
                            l_xctSave();
                            state = eFile2LineState::ZERO;
                            break;
                        case ']' : state = eFile2LineState::CLOSING;
                            --scope;
                            if(scope.value == 0) {
                                l_xctSave();
                                state = eFile2LineState::ZERO;
                            }
                            break;
                        default : current_line += c;
                            break;
                    }
                    break;
                case eFile2LineState::CLOSING : switch(c) {
                        case '[' : if(scope.value != 0) { current_line._fail = true; }
                            l_xctSave();
                            state = eFile2LineState::OPENING;
                            break;
                        case ']' : --scope;
                            if(scope.value == 0) {
                                l_xctSave();
                                state = eFile2LineState::ZERO;
                            }
                            break;
                        default : if(scope.value != 0) { current_line._fail = true; }
                            l_xctSave();
                            state = eFile2LineState::ZERO;
                            break;
                    }
                    break;
            }
        }
        return retline;
    }

    enum class eUnpackLineState { PREFIX , CONTENT , POSTFIX };

    std::unique_ptr<std::vector<Parser::sLine>> Parser::xctUnpackLine(const sLine& arg_line) {
        std::stringstream        packed_line{arg_line._line};
        char                     c{};
        std::unique_ptr          retvec{std::make_unique<std::vector<sLine>>()};
        eUnpackLineState         state{eUnpackLineState::PREFIX};
        bool                     need_more_unpack{false};
        std::string              prefix{};
        std::vector<std::string> content{};
        std::string current_content{};
        std::string              postfix{};
        bool                     fail{false};
        while(true) {
            packed_line >> std::ws;
            if(packed_line.eof()) { break; }
            packed_line >> c;
            switch(state) {
                case eUnpackLineState::PREFIX : switch(c) {
                        case '{' : state = eUnpackLineState::CONTENT;
                            break;
                        case '|' : fail = true;
                            packed_line = {};
                            break;
                        case '}' : state = eUnpackLineState::POSTFIX;
                            break;
                        default : prefix += c;
                    }
                    break;
                case eUnpackLineState::CONTENT : switch(c) {
                        case '{' :
                        fail = true;
                        packed_line = {};
                        break;
                        case '|' :
                        content.push_back(std::move(current_content));
                        current_content = {};
                        break;
                        case '}' :
                        content.push_back(std::move(current_content));
                        current_content = {};
                        state = eUnpackLineState::POSTFIX;
                        break;
                        default : current_content += c;
                    }
                    break;
                case eUnpackLineState::POSTFIX : switch(c) {
                        case '{' : need_more_unpack = true;
                            break;
                        case '|' :
                        fail = true;
                        packed_line = {};
                        break;
                        case '}' :
                        fail = true;
                        packed_line = {};
                        break;
                        default :
                        postfix += c;
                    }
                    break;
            }
        }
        for(const std::string& string : content) {
            if(need_more_unpack) { xctUnpackLine(sLine{fail , false , prefix + string + postfix , arg_line._scope}); }
            else { retvec->push_back(sLine{fail , false , prefix + string + postfix , arg_line._scope}); }
        }
        return retvec;
    }

    common::Act Parser::xctLine2Act(sLine arg_line) {
        s
    }

    common::ui_screen_TD Parser::xctGetScreen() {
        file_ = std::fstream{path_};
        // std::unique_ptr<std::vector<sLine>> lines = xctFile2Lines();
        return common::sUiError{};
    }
}
/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
