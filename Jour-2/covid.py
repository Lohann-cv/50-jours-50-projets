import pandas as pd
import streamlit as st
# Ce fichier csv de ourworldindata qui contien plusieurs informations concernant la pandemie du covide 19
covid = pd.read_csv('Jour-2/owid-covid-data.csv')

selected_country = 'France'
covid_pays = covid[covid['location'] == selected_country]
# ce dataset contien aussi le nombre de lit d'hopital par millier de personne (dans le pays), il aurait intéresent de prendre cette data pour un model de ml
useful_columns = ["date", "new_cases",
                  "new_deaths", "total_cases", "total_deaths"]
covid_pays = covid_pays[useful_columns]
