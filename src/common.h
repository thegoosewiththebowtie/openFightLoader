/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
#pragma once
#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Text.hpp"

namespace v::common {
    enum class eState { SCENE , MENU , FIGHT };
    enum class eInteractionRequestType { PROCEED , UNPROCEED , MENU , MOVE_UP , MOVE_DOWN , MOVE_LEFT , MOVE_RIGHT };
    enum class eErrorType { COMMON };
    enum class eAct {
        MTT
      , XBEG
      , XEND
      , EXIT
      , OPEN
      , LOAD
      , XTPT
      , MAKE
      , SETX
      , PACK
      , UNPK
      , NVBX
      , SHOW
      , UNSH
    };

    struct sSpace {
        int _x = 0 , _y = 0;
    };

    struct sTimeNSpace {
        sSpace _space{};
        int    _t = 0;
    };

    class Pattern {
        enum class ePatternType { MOVE_IMG , CHNG_IMG };
        sSpace                                                      size_;
        std::vector<sTimeNSpace>                                    path_;
        std::set<sSpace>                                            hit_px_;
        std::optional<int>                                          image_id_;
        static std::unordered_map<int , std::unique_ptr<sf::Image>> image_dump_;
        public:
            Pattern(sSpace arg_size , std::vector<sTimeNSpace> arg_path , std::set<sSpace> arg_hit_px);
            Pattern(sSpace arg_size , std::vector<sTimeNSpace> arg_path , std::set<sSpace> arg_hit_px , int arg_image_id);
            Pattern(sSpace arg_size , std::vector<sTimeNSpace> arg_path , std::set<sSpace> arg_hit_px , const std::filesystem::path& arg_image_path);
    };

    struct sUiElement {
        sUiElement(std::unique_ptr<sf::Drawable>&& arg_drawable , const sSpace arg_place) : _drawable{std::move(arg_drawable)}
                                                                                        , _place{arg_place} {}

        sUiElement(sUiElement&)       = delete;
        sUiElement(const sUiElement&) = delete;
        sUiElement(sUiElement&&)      = default;
        ~sUiElement()                 = default;
        std::unique_ptr<sf::Drawable> _drawable;
        sSpace                        _place;
    };
    class Act {
        sSpace position_;
        public:
            struct sAct {
                virtual      ~sAct() = default;
                virtual eAct xctGetType() = 0;
            };
            struct sMtt final : sAct {
                eAct xctGetType() override { return eAct::MTT; }
            };
            struct sXbeg final : sAct {
                eAct xctGetType() override { return eAct::XBEG; }
            };
            struct sXend final : sAct {
                eAct xctGetType() override { return eAct::XEND; }
            };
            struct sExit final : sAct {
                eAct xctGetType() override { return eAct::EXIT; };
            };
            struct sOpen final : sAct {
                eAct xctGetType() override { return eAct::OPEN; };
            };
            struct sLoad final : sAct {
                eAct xctGetType() override { return eAct::LOAD; };
            };
            struct sXtpt final : sAct {
                eAct xctGetType() override { return eAct::XTPT; };
            };
            struct sMake final : sAct {
                eAct xctGetType() override { return eAct::MAKE; };
            };
            struct sSetx final : sAct {
                eAct xctGetType() override { return eAct::SETX; };
            };
            struct sPack final : sAct {
                eAct xctGetType() override { return eAct::PACK; };
            };
            struct sUnpk final : sAct {
                eAct xctGetType() override { return eAct::UNPK; };
            };
            struct sNvbx final : sAct {
                eAct xctGetType() override { return eAct::NVBX; };
            };
            struct sShow final : sAct {
                eAct xctGetType() override { return eAct::SHOW; };
            };
            struct sUnsh final : sAct {
                eAct xctGetType() override { return eAct::UNSH; };
            };
    };
    struct sUiScreen {
        sSpace                                               _resolution;
        std::unordered_map<int , std::shared_ptr<sUiScreen>> _links;
        std::vector<sUiElement>                              _drawable_elements;
        std::vector<Act::sAct>              _act_elements;
    };

    struct sUiError {
        eErrorType  _type;
        std::string _message;
        sUiError() = default;
        sUiError(const eErrorType arg_error , const std::basic_string<char>& arg_str): _type{arg_error} , _message{arg_str} {};
    };

    using ui_screen_TD = std::variant<sUiError , sUiScreen>;

}

/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
