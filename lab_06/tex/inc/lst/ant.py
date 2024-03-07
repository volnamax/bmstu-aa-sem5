def antAlgorithm(matrix, places, alpha, beta, k_evaporation, days, elite_ant_total):
    q = calcQ(matrix, places)
    bestWay = []
    minDist = float("inf")
    pheromones = calcPheromones(places)
    visibility = calcVisibility(matrix, places)
    ants = places
    for day in range(days):
        route = np.arange(places)
        visited = calcVisitedPlaces(route, ants)
        for ant in range(ants):
            while (len(visited[ant]) != ants):
                pk = findWays(pheromones, visibility, visited, places, ant, alpha, beta)
                chosenPlace = chooseNextPlaceByPosibility(pk)
                visited[ant].append(chosenPlace - 1)

            curLength = calcLength(matrix, visited[ant])

            if (curLength < minDist):
                minDist = curLength
                bestWay = visited[ant]

        for i in range(elite_ant_total):
            visited.append(bestWay)

        pheromones = updatePheromones(matrix, places, visited, pheromones, q, k_evaporation)

    return minDist, bestWay
