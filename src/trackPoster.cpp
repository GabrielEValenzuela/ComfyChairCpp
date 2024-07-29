/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackPoster.hpp"
#include "articlePoster.hpp"
#include "trackStateReception.hpp"
#include <bid.hpp>

TrackPoster::TrackPoster(const nlohmann::json& trackData)
{
    m_trackName = trackData.value("trackTopic", "");
    m_currentState = std::make_shared<ReceptionStateTrack>();
}

void TrackPoster::handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation)
{
    if (!article->isValid() || dynamic_cast<ArticlePoster*>(article.get()) == nullptr)
    {
        std::cerr << "Article is not valid for this track" << std::endl;
        return;
    }
    try
    {
        m_currentState->handleArticle(m_articles, article, operation);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackPoster::handleTrackBidding()
{
    try
    {
        m_currentState->handleBidding(m_articles, m_articleBidding, m_reviewers);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackPoster::handleTrackReview()
{
    try
    {
        m_currentState->handleReview(m_articles, m_articleBidding, m_articleReviews, m_reviewers);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

const std::string& TrackPoster::trackName() const
{
    return m_trackName;
}

void TrackPoster::establishState(const std::shared_ptr<ITrackState>& state)
{
    m_currentState = state;
}

void TrackPoster::currentState() const
{
    std::cout << "Poster '" << m_trackName << "' currently is in '" << m_currentState->stateName() << "' state"
              << std::endl;
}

int TrackPoster::amountArticles() const
{
    return m_articles.size();
}

size_t TrackPoster::amountBids() const
{
    return m_articleBidding.size();
}

void TrackPoster::addReviewer(const std::shared_ptr<User> reviewer)
{
    m_reviewers.push_back(reviewer);
}

void TrackPoster::currentBids() const
{
    for (const auto& article : m_articleBidding)
    {
        std::cout << "The article '" << article.first->articleName() << "' has the following biddings:" << std::endl;
        article.second.bidSummary();
    }
}

size_t TrackPoster::amountReviews() const
{
    return m_articleReviews.size();
}

void TrackPoster::currentReviews() const
{
    for (const auto& article : m_articleReviews)
    {
        std::cout << "The article '" << article.first->articleName() << "' has the following reviews:" << std::endl;
        article.second.printReview();
    }
}
