def chooseNextPlaceByPosibility(pk):
    posibility = random()
    choice = 0
    chosenPlace = 0
    while ((choice < posibility) and (chosenPlace < len(pk))):
        choice += pk[chosenPlace]
        chosenPlace += 1

    return chosenPlace