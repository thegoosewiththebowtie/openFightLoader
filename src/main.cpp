#include <iostream>
#include <SFML/Graphics.hpp>

#include "uiparser.h"

int main(int argc , char* argv[]) {
    v::parser::Parser parser{"F:/Libraries/Projects/openFightLoader/defaultUi/simple/main_menu.ofui"};
    parser.xctGetScreen();
    std::unique_ptr<std::vector<v::parser::Parser::sLine>> a = parser.xctFile2Lines();
    std::vector<v::parser::Parser::sLine>                  b = *a;
    for(v::parser::Parser::sLine line : b) {
        if(line._packed) {
            auto d = *parser.xctUnpackLine(line);
            for(auto linee : d) {
                std::cout << linee._fail << "\t" << linee._line << "\t" << linee._scope << std::endl;
            }
        } else {
            std::cout << line._fail << "\t" << line._line << "\t" << line._scope << std::endl;
        }
    }
    /* auto window = sf::RenderWindow(sf::VideoMode({1600u , 900u}), "openFight");
     window.setFramerateLimit(144);
     while(window.isOpen()) {
         while(const std::optional event = window.pollEvent()) {
             if(event->is<sf::Event::Closed>()) { window.close(); }
             else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                 switch(keyPressed->scancode) {
                     case sf::Keyboard::Scancode::Up : std::cout << "UP DETECTED" << std::endl;
                         break;
                     case sf::Keyboard::Scancode::Down : std::cout << "DOWN DETECTED" << std::endl;
                         break;
                     case sf::Keyboard::Scancode::Left : std::cout << "LEFT DETECTED" << std::endl;
                         break;
                     case sf::Keyboard::Scancode::Right : std::cout << "RIGHT DETECTED" << std::endl;
                         break;
                     case sf::Keyboard::Scancode::Enter : std::cout << "PROCEED DETECTED" << std::endl;
                         break;
                     case sf::Keyboard::Scancode::LShift : [[fallthrough]] case sf::Keyboard::Scancode::RShift : std::cout << "UNPROCEED DETECTED" << std::endl;
                         break;
                     default : std::cout << "key pressed or smth" << std::endl;
                 }
             }
         }

         window.clear(sf::Color::Black);
         v::parser::UiParser parser("F:/Libraries/Projects/openFightLoader/defaultUi/simple/main_menu.ofl");
                 for(v::common::ui_element_TD ui_element_td : parsed) {
             std::visit([&window](const auto& arg_ui_element_td) { window.draw(arg_ui_element_td); }, ui_element_td);
         }
         window.display();
     }*/
}

namespace v {}
