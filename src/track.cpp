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
    try
    {
        m_currentState->handleArticle(m_articles, article, OperationType::Create);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Track::updateArticle(const std::shared_ptr<Article>& article)
{
    try
    {
        m_currentState->handleArticle(m_articles, article, OperationType::Update);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Track::removeArticle(const std::shared_ptr<Article>& article)
{
    try
    {
        m_currentState->handleArticle(m_articles, article, OperationType::Delete);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Track::addBid(const std::shared_ptr<Article>& article, BiddingInterest interest)
{
    try
    {
        m_currentState->handleBidding(m_articleBidding, article, interest, OperationType::Create);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Track::updateBid(const std::shared_ptr<Article>& article, BiddingInterest interest)
{
    try
    {
        m_currentState->handleBidding(m_articleBidding, article, interest, OperationType::Update);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Track::removeBid(const std::shared_ptr<Article>& article)
{
    try
    {
        m_currentState->handleBidding(m_articleBidding, article, BiddingInterest::NotInterested, OperationType::Delete);
    }
    catch (const TrackStateException& e)
    {
        std::cerr << e.what() << '\n';
    }
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
