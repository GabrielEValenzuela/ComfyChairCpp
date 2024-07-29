/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackStateReception.hpp"
#include "bid.hpp"

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

void ReceptionStateTrack::handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                                        std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                        const std::vector<std::shared_ptr<User>> reviewers)
{
    throw TrackStateException("Bidding is not allowed in reception state");
}

void ReceptionStateTrack::handleSelection(
    std::vector<std::shared_ptr<Article>> selectedArticles, std::shared_ptr<SelectionStrategy> selectionStrategy,
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    throw TrackStateException("Cannot handle selection in Reception state");
}

void ReceptionStateTrack::handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                                       const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                       std::unordered_map<std::shared_ptr<Article>, Review>& reviewMap,
                                       const std::vector<std::shared_ptr<User>> reviewers)
{
    throw TrackStateException("Review is not allowed in reception state");
}
