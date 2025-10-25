import streamlit as st
import pandas as pd
import plotly.express as px

st.title("Visu interactive COVID-19")
covid = pd.read_csv("Jour-2/owid-covid-data.csv", parse_dates=['date'])
country = covid['location'].unique()
selected_country = st.selectbox("Choi un pays :", sorted(country))
series_disponibles = ["new_cases", "new_deaths"]
checked_series = st.multiselect(
    "Serie a afficher :", series_disponibles, default=series_disponibles)
covid_pays = covid[covid["location"] == selected_country]
cases_and_death = covid_pays.melt(
    id_vars='date',
    value_vars=checked_series,
    var_name='variable',
    value_name='valeur'
)
cases_and_death_ok = cases_and_death.dropna(subset=['valeur'])

fig = px.line(
    cases_and_death_ok,
    x='date', y='valeur', color='variable',
    title=f'Evolution des nouveaux cas et morts de COVID-19 en {selected_country}',
    labels={'date': 'Date', 'valeur': 'Nombre', 'variable': 'Série'},
    color_discrete_map={'new_cases': 'royalblue', 'new_deaths': 'firebrick'}
)
st.plotly_chart(fig, use_container_width=True)
# C'est très laid mais globalement c'est mashup les deux autres files en une seul + streamlit
