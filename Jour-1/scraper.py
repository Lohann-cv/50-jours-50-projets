import pandas as pd 
import snscrape.modules.twitter as stwitter

scrape_query = "#IA since:2024-01-01 until:2025-10-01"

tweets_list = []

for i, tweet in enumerate(stwitter.TwitterSearchScraper(scrape_query).get_items()):
    tweets_list.append([
        tweet.date,
        tweet.content,
        tweet.replyCount,
        tweet.retweetCount,
        tweet.likeCount
    ])
    if i >= 999:
        break

df = pd.DataFrame(tweets_list, columns=["Date", "Text", "Replies", "Retweets", "Likes"])

print(df.head())