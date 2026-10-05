Enlace del video: https://youtu.be/3OzrLK4ZL8I


Requisitos:

- gcc (en Windows: MinGW-w64)
- Python 3 con matplotlib (`pip install matplotlib`)

Ejecución

Todos los comandos se ejecutan desde la raíz del repositorio.

Windows (PowerShell):

```
gcc -O2 problema2/problema2.c -o problema2/problema2.exe
gcc -O2 problema3/problema3.c -o problema3/problema3.exe
.\problema2\problema2.exe
.\problema3\problema3.exe
python graficar.py
```

```
.\problema3\problema3.exe 1 10 100 1000 10000 100000
```

El problema 3 con n = 1000000 ejecuta 83 333 250 000 impresiones y tardó unos 67 minutos en la máquina de prueba.


