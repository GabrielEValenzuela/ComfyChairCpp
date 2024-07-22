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

void TrackPoster::handleTrackBidding(const std::shared_ptr<Article>& article, BiddingInterest interest,
                                     OperationType operation)
{
    try
    {
        m_currentState->handleBidding(m_articleBidding, article, interest, operation);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackPoster::handleTrackReview(const std::shared_ptr<Article>& article, const std::string& review,
                                    OperationType operation)
{
    std::cout << "Not implemented yet" << std::endl; // ToDo Implement this method
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
