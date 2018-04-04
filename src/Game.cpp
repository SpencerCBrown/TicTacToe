//
// Created by spencer on 4/3/18.
//

#include "GameBoard.h"
#include "Game.h"

Game::Game() : m_window(sf::VideoMode(375, 375), "TicTacToe"), m_event(), m_root(getTextureForBoard())
{
}

void Game::run()
{
    setup();

    while (m_window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while (m_window.pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
        }
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_root.getMarksToPlace().push(std::pair<MarkNode::MarkType, sf::Vector2i>(MarkNode::MarkType::X, mousePos));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        m_root.getMarksToPlace().push(std::pair<MarkNode::MarkType, sf::Vector2i>(MarkNode::MarkType::O, mousePos));
    }

}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.draw(m_root);
    m_window.display();
}

void Game::update()
{
    m_root.update();
}

void Game::setup()
{

}

sf::Texture& Game::getTextureForBoard()
{
    m_tempTexture = new sf::Texture();
    m_tempTexture->loadFromFile("board.png");
    return *m_tempTexture;
}
