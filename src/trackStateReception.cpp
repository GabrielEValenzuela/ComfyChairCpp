/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackStateReception.hpp"

void ReceptionStateTrack::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                        const std::shared_ptr<Article>& article, OperationType operation)
{
    switch (operation)
    {
    case OperationType::Create:
        articles.push_back(article);
        break;
    case OperationType::Update:
        updateArticle(articles, article);
        break;
    case OperationType::Delete:
        removeArticle(articles, article);
        break;
    }
}

const std::string& ReceptionStateTrack::stateName()
{
    return m_stateName;
}

void ReceptionStateTrack::updateArticle(std::vector<std::shared_ptr<Article>>& articles,
                                        const std::shared_ptr<Article>& article)
{
    const auto& targetTitle = article->articleName();
    auto it = std::find_if(articles.begin(), articles.end(), [&targetTitle](const std::shared_ptr<Article>& article) {
        return article->articleName() == targetTitle;
    });
    if (it != articles.end())
    {
        (*it)->updateFields(article);
    }
    // LCOV_EXCL_START //ToDo Remove when article is fully implemented
    else
    {
        std::cout << "Article not found" << std::endl;
    }
    // LCOV_EXCL_STOP
}

void ReceptionStateTrack::removeArticle(std::vector<std::shared_ptr<Article>>& articles,
                                        const std::shared_ptr<Article>& article)
{
    const auto& targetTitle = article->articleName();
    auto it = std::find_if(articles.begin(), articles.end(), [&targetTitle](const std::shared_ptr<Article>& article) {
        return article->articleName() == targetTitle;
    });
    if (it != articles.end())
    {
        articles.erase(it);
    }
    // LCOV_EXCL_START //ToDo Remove when article is fully implemented
    else
    {
        std::cout << "Article not found" << std::endl;
    }
    // LCOV_EXCL_STOP
}

void ReceptionStateTrack::handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                                        const std::shared_ptr<Article>& article, BiddingInterest interest,
                                        OperationType operation)
{
    throw TrackStateException("Bidding is not allowed in reception state");
}
