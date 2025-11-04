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
    using ui_element_TD = std::variant<sf::Shape, sf::Image, sf::Text>;
    enum class eState { SCENE , MENU , FIGHT };
    enum class eInteractionRequestType { PROCEED , UNPROCEED , MENU , MOVE_UP , MOVE_DOWN , MOVE_LEFT , MOVE_RIGHT };
    enum class eACT{EXIT, XBEG, XEND};
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
    struct sUiElement : ui_element_TD {
        sSpace _place;
    };
    struct sUiScreen {
        sSpace _resolution;
        std::unordered_map<int, std::shared_ptr<sUiScreen>> _links;
        std::vector<sUiElement> _elements;
    };
}

/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
