import pandas as pd
import matplotlib.pyplot as plt

# 1. Lire le CSV
dataset = pd.read_csv("Jour-1/reddit_posts-clean.csv")

# 2. Conversion date
dataset['Date'] = pd.to_datetime(dataset['Date'], unit='s', errors='coerce')

# 3. Extraire uniquement la date (jou)
dataset['Jour'] = dataset['Date'].dt.date

# 4. Compter le nombre de posts par jour
posts_par_jour = dataset.groupby('Jour').size()

# 5. Afficher la courbe
plt.figure(figsize=(12, 6))
posts_par_jour.plot()
plt.title("Évolution du nombre de posts IA par jour sur Reddit")
plt.xlabel("Date")
plt.ylabel("Nombre de posts")
plt.tight_layout()
plt.show()
