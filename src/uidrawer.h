/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */
#pragma once
#include <memory>

#include "common.h"
#include "SFML/Graphics/Drawable.hpp"

namespace v::ui_drawer {
class UiDrawer {
    common::sUiScreen screen_;
    public:
        UiDrawer(common::sUiScreen);
        UiDrawer()                           = delete;
        UiDrawer(const UiDrawer&)            = delete;
        UiDrawer& operator=(const UiDrawer&) = delete;
        ~UiDrawer();
        std::unique_ptr<sf::Drawable> xctGetFrame();
};
}
