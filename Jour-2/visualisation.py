import covid as clean
import plotly.express as px
# enlever le vide
cases_and_death = clean.covid_pays.melt(id_vars='date', value_vars=[
                                        'new_cases', 'new_deaths'], var_name='variable', value_name='valeur')
cases_and_death_ok = cases_and_death.dropna(subset=['valeur'])
graph = px.line(
    cases_and_death_ok,
    x='date', y='valeur', color='variable',
    title=f'Evolution des nouveaux cas et mort de COVID-19 en {clean.selected_country}',
    labels={'date': 'Date', 'valeur': 'Nombre', 'variable': 'Série'},
    color_discrete_map={'new_cases': 'royalblue', 'new_deaths': 'firebrick'}
)
# Je suis consient que les noms des variables sont incomprehensible mais ca va faire un peu de temps que je suis lever
graph.show()
