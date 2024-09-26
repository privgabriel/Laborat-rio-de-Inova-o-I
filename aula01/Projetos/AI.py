#Projeto IA
#Autor: Lucas Gabriel
#Data: 2021-09-20
#Descrição: Projeto de IA para prever a nota de um aluno com base em suas notas anteriores

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import metrics
import matplotlib.pyplot as plt

#Carregando o dataset
dataset = pd.read_csv('student-mat.csv')

#Selecionando as colunas que serão utilizadas
dataset = dataset[['G1', 'G2', 'G3']]

#Definindo as variáveis dependentes e independentes
X = dataset[['G1', 'G2']]
y = dataset['G3']

#Dividindo o dataset em treino e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)

#Treinando o modelo
model = LinearRegression()
model.fit(X_train, y_train)

#Fazendo previsões
y_pred = model.predict(X_test)

#Avaliando o modelo
print('Erro médio absoluto:', metrics.mean_absolute_error(y_test, y_pred))
print('Erro médio quadrático:', metrics.mean_squared_error(y_test, y_pred))
print('Raiz do erro médio quadrático:', np.sqrt(metrics.mean_squared_error(y_test, y_pred)))

#Plotando o gráfico
plt.scatter(y_test, y_pred)
plt.xlabel('Nota real')
plt.ylabel('Nota prevista')
plt.title('Nota real x Nota prevista')
plt.show()

#Testando o modelo
G1 = 10
G2 = 15
print('Nota prevista:', model.predict([[G1, G2]]))

#Salvando o modelo
import joblib
joblib.dump(model, 'model.pkl')

#Carregando o modelo
model = joblib.load('model.pkl')
print('Nota prevista:', model.predict([[G1, G2]]))

#Fim do código

