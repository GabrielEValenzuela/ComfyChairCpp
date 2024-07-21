/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "track.hpp"

Track::Track(const std::string& trackName, const std::shared_ptr<ITrackState>& state,
             const std::vector<std::shared_ptr<User>>& users)
    : m_trackName(trackName), m_currentState(state), m_users(users)
{
}

void Track::addArticle(const std::shared_ptr<Article>& article)
{
    m_currentState->handleArticle(m_articles, article, OperationType::Create);
}

void Track::updateArticle(const std::shared_ptr<Article>& article)
{
    m_currentState->handleArticle(m_articles, article, OperationType::Update);
}

void Track::removeArticle(const std::shared_ptr<Article>& article)
{
    m_currentState->handleArticle(m_articles, article, OperationType::Delete);
}

const std::string& Track::trackName() const
{
    return m_trackName;
}

void Track::establishState(const std::shared_ptr<ITrackState>& state)
{
    m_currentState = state;
}

void Track::currentState() const
{
    std::cout << "Track currently is in '" << m_currentState->stateName() << "' state" << std::endl;
}

int Track::amountArticles() const
{
    return m_articles.size();
}