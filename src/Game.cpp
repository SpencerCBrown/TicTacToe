//
// Created by spencer on 4/3/18.
//

#include <iostream>

#include "GameBoard.h"
#include "Game.h"

Game::Game() : m_window(sf::VideoMode(375, 375), "TicTacToe"), m_event()
        , m_root(getTextureForBoard())
        , m_playerQueue()
{
    m_playerQueue.push(Player(Player::Type::HUMAN, MarkNode::MarkType::X));
    m_playerQueue.push(Player(Player::Type::AI, MarkNode::MarkType::O));
}

void Game::run()
{
    setup();

    while (m_window.isOpen() && !m_gameIsWon) {
        handleEvents();
        update();
        render();
    }

    m_window.close();
}

void Game::handleEvents()
{
    Player p = m_playerQueue.front();
    bool didTurn = false;

    while (m_window.pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                p = m_playerQueue.front();
                if (p.getType() == Player::Type::HUMAN) {
                    didTurn = p.handleDirectInput(m_event, m_root.getMarksToPlace())
                              && !m_root.hasMarkOnIndex(m_root.getClickedSquare(m_root.getMarksToPlace().back().second));
                }
        }
    }

    if (p.getType() == Player::Type::AI) {
        didTurn = p.handleGeneratedInput(m_root.getMarksToPlace())
                  && !m_root.hasMarkOnIndex(m_root.getClickedSquare(m_root.getMarksToPlace().back().second));
    }
    if (didTurn) {
        m_playerQueue.push(p);
        m_playerQueue.pop();
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
    if ((m_root.markWith3InARow() != MarkNode::MarkType::NONE) || (m_root.isFull())) {
        m_gameIsWon = true;
        std::cout << "WINNER IS: " << MarkNode::getNameOfMark(m_root.markWith3InARow());
    }
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
