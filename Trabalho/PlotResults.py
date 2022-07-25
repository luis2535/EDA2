import matplotlib.pyplot as plt
import numpy as np
import math
plt.style.use("seaborn-deep")

# (1) Caminho da pasta do trabalho:
generalPath = "C:\\Users\\bruni\\OneDrive\\Documentos\\GitHub\\EDA2001\\Trabalho\\"

# (2) Gráfico do caso médio da árvore Rubro-Negra:

with open(generalPath + "RedBlackTree\\PerformanceAverageCase.txt", 'r') as f:
    lines = f.readlines()

averageVectorRB = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        averageVectorRB[j] += float(vector[j])/10

xpointsAverageRB = np.array([x for x in range(0, len(averageVectorRB))])
ypointsAverageRB = np.array(averageVectorRB)

plt.xticks(range(0, len(xpointsAverageRB)+1, 100))
plt.plot(xpointsAverageRB, ypointsAverageRB, label="Average (Red-Black)", linewidth=0.6)
f.close()

# (3) Gráfico do pior caso da árvore Rubro-Negra:

with open(generalPath + "RedBlackTree\\PerformanceWorstCase.txt", 'r') as f:
    lines = f.readlines()

worstVectorRB = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        worstVectorRB[j] = float(vector[j])

xpointsWorstRB = np.array([x for x in range(0, len(worstVectorRB))])
ypointsWorstRB = np.array(worstVectorRB)

plt.plot(xpointsWorstRB, ypointsWorstRB, label="Worst (Red-Black)", linewidth=0.6)

plt.title("Average Case vs Worst Case")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\RedBlackTree.png")
plt.close()
f.close()

# (4) Gráfico do caso médio da árvore AVL:

with open(generalPath + "AVLTree\\PerformanceAverageCase.txt", 'r') as f:
    lines = f.readlines()

averageVectorAVL = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        averageVectorAVL[j] += float(vector[j])/10

xpointsAverageAVL = np.array([x for x in range(0, len(averageVectorAVL))])
ypointsAverageAVL = np.array(averageVectorAVL)

plt.plot(xpointsAverageAVL, ypointsAverageAVL, label="Average (AVL)", linewidth=0.6)
f.close()

# (5) Gráfico do pior caso da árvore AVL:

with open(generalPath + "AVLTree\\PerformanceWorstCase.txt", 'r') as f:
    lines = f.readlines()

worstVectorAVL = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        worstVectorAVL[j] = float(vector[j])

xpointsWorstAVL = np.array([x for x in range(0, len(worstVectorAVL))])
ypointsWorstAVL = np.array(worstVectorAVL)

plt.plot(xpointsWorstAVL, ypointsWorstAVL, label="Worst (AVL)", linewidth=0.6)

plt.title("Average Case vs Worst Case")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\AVLTree.png")
plt.close()
f.close()

# (6) Gráfico do caso médio da árvore B:

with open(generalPath + "BTree\\PerformanceAverageCase.txt", 'r') as f:
    lines = f.readlines()

averageVectorB = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        averageVectorB[j] = float(vector[j])

xpointsAverageB = np.array([x for x in range(0, len(averageVectorB))])
ypointsAverageB = np.array(averageVectorB)

plt.plot(xpointsAverageB, ypointsAverageB, label="Average (B)", linewidth=0.6)
f.close()

# (7) Gráfico do pior caso da árvore B:

with open(generalPath + "BTree\\PerformanceWorstCase.txt", 'r') as f:
    lines = f.readlines()

worstVectorB = [0 for i in range(len(lines[0].split()))]

for line in lines:
    vector = line.split()
    for j in range(len(vector)):
        worstVectorB[j] = float(vector[j])

xpointsWorstB = np.array([x for x in range(0, len(worstVectorB))])
ypointsWorstB = np.array(worstVectorB)

plt.plot(xpointsWorstB, ypointsWorstB, label="Worst (B)", linewidth=0.6)

plt.title("Average Case vs Worst Case")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\BTree.png")
plt.close()
f.close()

# (8) Plotando todos os gráficos em um só:

plt.plot(xpointsAverageRB, ypointsAverageRB, label="Average (RB)", linewidth=0.6)
plt.plot(xpointsAverageAVL, ypointsAverageAVL, label="Average (AVL)", linewidth=0.6)
plt.plot(xpointsAverageB, ypointsAverageB, label="Average (B)", linewidth=0.6)

plt.title("Average Cases")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\AllTreesAverage.png")
plt.close()

plt.plot(xpointsWorstRB, ypointsWorstRB, label="Worst (RB)", linewidth=0.6)
plt.plot(xpointsWorstAVL, ypointsWorstAVL, label="Worst (AVL)", linewidth=0.6)
plt.plot(xpointsWorstB, ypointsWorstB, label="Worst (B)", linewidth=0.6)

plt.title("Worst Cases")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\AllTreesWorst.png")
plt.close()

xAxis = np.linspace(1, len(worstVectorB))
plt.plot(xAxis, np.log2(xAxis), label="log(n) em base 2", linewidth=0.6)

plt.plot(xpointsAverageRB, ypointsAverageRB, label="Average (RB)", linewidth=0.6)
plt.plot(xpointsAverageAVL, ypointsAverageAVL, label="Average (AVL)", linewidth=0.6)
plt.plot(xpointsAverageB, ypointsAverageB, label="Average (B)", linewidth=0.6)
#plt.plot(xpointsWorstRB, ypointsWorstRB, label="Worst (RB)")
#plt.plot(xpointsWorstAVL, ypointsWorstAVL, label="Worst (AVL)")
#plt.plot(xpointsWorstB, ypointsWorstB, label="Worst (B)")

#plt.style.use("seaborn")
plt.title("Average Cases vs log(n)")
plt.xlabel("Elementos na árvore")
plt.ylabel("Etapas")
plt.legend(loc="upper left")
plt.savefig(generalPath + "Graphics\\LogAndAverage.png")
plt.close()