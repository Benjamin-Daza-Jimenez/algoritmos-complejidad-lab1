import matplotlib.pyplot as plt #pip install matplotlib
import pandas as pd
import numpy as np

path_measurmenets = "../data/measurements/"
path_plots = "../data/plots/"
tipos=["naive.txt","strassen.txt"]

data = []

for tipo in tipos:
    path_lectura = path_measurmenets+tipo
    with open(path_lectura) as f:

        for line in f:
            partes = line.strip().replace("[S]", "").replace("[KB]", "").split()

            nombre = partes[0]
            tiempo = float(partes[1]) if partes[1] != "-" else np.nan
            memoria = float(partes[2]) if partes[2] != "-" else np.nan

            data.append((nombre,tiempo,memoria,tipo))

df = pd.DataFrame(data, columns=["archivo", "tiempo", "memoria", "algoritmo"])
df = df.sort_values("archivo")

df["numero"] = df["archivo"].apply(lambda x: int(x.split('_')[0]))
df = df.sort_values("numero")

# Gráfico de tiempos
plt.figure(figsize=(10, 5))
for alg in df["algoritmo"].unique():
    sub = df[df["algoritmo"] == alg]
    plt.plot(sub["archivo"], sub["tiempo"], label=alg, marker='o')
plt.title("Comparación de Tiempos")
plt.legend()
plt.xticks(rotation=90)
plt.tight_layout()
plt.savefig(path_plots+"Grafico_tiempos.png") 

# Gráfico de memoria
plt.figure(figsize=(10, 5))
for alg in df["algoritmo"].unique():
    sub = df[df["algoritmo"] == alg]
    plt.plot(sub["archivo"], sub["memoria"], label=alg, marker='s')
plt.title("Comparación de Memoria")
plt.legend()
plt.xticks(rotation=90)
plt.tight_layout()
plt.savefig(path_plots+"Grafico_memoria.png") 