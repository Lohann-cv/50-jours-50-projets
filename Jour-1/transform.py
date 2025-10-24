import pandas as pd
import re
from langdetect import detect


# IMPORTANT on enlève beaucoup de chose dans ce netoyage mais c'est important si on veux exploiter les donnée sans bruits (élément inutile) qui pourait gêner
# On peut par exemple l'utiliser pour une analise de sentiment (savoir si l'avis et plutot négatif, neutre ou positif)

# On lis le csv de l'exctraction (le remplacer avec le votre)
dataset = pd.read_csv("Jour-1/reddit_posts.csv")

# On enlève les titre et/ou texte en trop qui doperai inutilement les données
dataset.drop_duplicates(subset=['Titre', 'Texte'], inplace=True)

# On enlèvre les postes entièrement vide
dataset = dataset[(dataset['Titre'].str.strip() != '') |
                  (dataset['Texte'].str.strip() != '')]

# On enlève les lien.     On fait ca grave au module regex de pandas (expretion regulière), ici 'http\S+ === tout ce qui à http et est suivie de caractère
dataset['Texte'] = dataset['Texte'].str.replace(r'http\S+', '', regex=True)
dataset['Titre'] = dataset['Titre'].str.replace(r'http\S+', '', regex=True)

# on convertie la date qui est en unix (nb sec depuis 1970) en date lisible
dataset['Date'] = pd.to_datetime(dataset['Date'], unit='s')

# Cette fonction utilise le regex pour prendre tout les caratère ayant un code unicode corespondant à des emojies symbloe ou autre puis à les remplacer par un string vide


def remove_emoji(text):
    emoji_pattern = re.compile("["
                               u"\U0001F600-\U0001F64F"
                               u"\U0001F300-\U0001F5FF"
                               # Pour trouver les element et leur code unicode aller sur unicode.org
                               u"\U0001F680-\U0001F6FF"
                               # Mais faire la recherche sur google est plus rapide
                               u"\U0001F1E0-\U0001F1FF"
                               u"\U00002702-\U000027B0"
                               u"\U000024C2-\U0001F251"
                               "]+", flags=re.UNICODE)
    return emoji_pattern.sub(r'', text)


# On utilise la fonction sur les titre et tewtes
dataset['Texte'] = dataset['Texte'].astype(str).apply(remove_emoji)
dataset['Titre'] = dataset['Titre'].astype(str).apply(remove_emoji)

# Supprimer ce qui n'est une lettre chiffre ou tabulation/espacement
dataset['Texte'] = dataset['Texte'].str.replace(
    r'[^a-zA-Z0-9\s]', '', regex=True)
dataset['Titre'] = dataset['Titre'].str.replace(
    r'[^a-zA-Z0-9\s]', '', regex=True)

# le dataset clean vaut pour celui international
dataset.to_csv("reddit_posts-clean.csv", index=False)

# Partie séparation en fonction de la langue


def detect_lang(text):
    try:
        return detect(text)
    except:
        return "unknown"


# On met une nouvelle colonne et on trie ensuite en fonction de la langue
dataset['Langue'] = (dataset['Titre'] + " " +
                     dataset['Texte']).apply(detect_lang)
francais = dataset[dataset['Langue'] == 'fr']
anglais = dataset[dataset['Langue'] == 'en']
espagnol = dataset[dataset['Langue'] == 'es']
# Les partie trier devienne des fichier csv
francais.to_csv("reddit_posts_fr.csv", index=False)
anglais.to_csv("reddit_posts_en.csv", index=False)
espagnol.to_csv("reddit_posts_es.csv", index=False)
