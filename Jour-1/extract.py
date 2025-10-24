import praw
import pandas as pd

# Mets ici tes infos (client_id, client_secret = ceux obtenus à l'étape 1, user_agent = ce que tu veux, par ex ton mail)
reddit = praw.Reddit(
    client_id='l05Y8F6jhrG-pK9uwE6FAg',
    client_secret='Ukidz_4fTUxImqSfixmKY79WZos7qQ',
    user_agent='lohanncoantverdier@gmail.com'
)

posts_list = []
for post in reddit.subreddit('all').search('IA', sort='new', limit=1000):
    posts_list.append([
        post.created_utc,
        post.title,
        post.selftext,
        post.subreddit.display_name,
        post.url,
        post.score  # nombre de upvotes
    ])

df = pd.DataFrame(posts_list, columns=[
                  "Date", "Titre", "Texte", "Subreddit", "URL", "Score"])
print(df.head())
df.to_csv("reddit_posts.csv", index=False)
