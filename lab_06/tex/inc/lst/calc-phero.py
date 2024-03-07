def calcPheromones(size):
    min_phero = 1
    pheromones = [[min_phero for i in range(size)] for j in range(size)]
    return pheromones