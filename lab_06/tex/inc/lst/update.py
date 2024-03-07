def updatePheromones(matrix, places, visited, pheromones, q, k_evaporation):
    ants = places

    for i in range(places):
        for j in range(places):
            delta = 0
            for ant in range(ants):
                if pathInWay(i, j, visited[ant]):
                    length = calcLength(matrix, visited[ant])
                    delta += q / length

            pheromones[i][j] *= (1 - k_evaporation)
            pheromones[i][j] += delta
            if (pheromones[i][j] < MIN_PHEROMONE):
                pheromones[i][j] = MIN_PHEROMONE

    return pheromones
