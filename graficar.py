import csv
import os

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

CARPETA = "resultados"
VALORES_REFERENCIA = [1, 10, 100, 1000, 10000, 100000, 1000000]

PROBLEMAS = [
    ("problema2", "Problema 2: tamaño de input vs. tiempo", "c · n", 1),
    ("problema3", "Problema 3: tamaño de input vs. tiempo", "c · n²", 2),
]


def leer_resultados(ruta):
    valores_n = []
    tiempos = []
    with open(ruta, newline="") as archivo:
        for fila in csv.DictReader(archivo):
            valores_n.append(int(fila["n"]))
            tiempos.append(float(fila["tiempo_segundos"]))
    return valores_n, tiempos


def graficar(nombre, titulo, etiqueta_referencia, exponente):
    valores_n, tiempos = leer_resultados(os.path.join(CARPETA, nombre + ".csv"))
    constante = tiempos[-1] / (valores_n[-1] ** exponente)
    referencia = [constante * (n ** exponente) for n in VALORES_REFERENCIA]

    figura, ejes = plt.subplots(figsize=(7, 4.5))
    ejes.plot(VALORES_REFERENCIA, referencia, linestyle="--", linewidth=1.5, color="#8a8983", label=etiqueta_referencia)
    ejes.plot(valores_n, tiempos, marker="o", markersize=7, linewidth=2, color="#2a78d6", label="Tiempo medido")
    ejes.set_xscale("log")
    ejes.set_yscale("log")
    ejes.set_xlabel("Tamaño de input (n)")
    ejes.set_ylabel("Tiempo (s)")
    ejes.set_title(titulo, loc="left")
    ejes.grid(True, which="major", color="#e4e3df", linewidth=0.8)
    ejes.set_axisbelow(True)
    ejes.spines["top"].set_visible(False)
    ejes.spines["right"].set_visible(False)
    ejes.legend(frameon=False, loc="upper left")
    figura.tight_layout()
    figura.savefig(os.path.join(CARPETA, nombre + ".png"), dpi=150)
    plt.close(figura)


def main():
    for nombre, titulo, etiqueta_referencia, exponente in PROBLEMAS:
        graficar(nombre, titulo, etiqueta_referencia, exponente)
        print("Generada", os.path.join(CARPETA, nombre + ".png"))


if __name__ == "__main__":
    main()
