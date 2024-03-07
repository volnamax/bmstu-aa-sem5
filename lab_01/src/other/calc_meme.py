import csv


def main():
    before = 1000
    step =100
    saveTableToCSV(meme_levenshtein(before, step), meme_dam_lev_rec(before, step), meme_dam_lev_cache(before, step),
                   before, step)


def meme_levenshtein(before, step):
    cost_int = 4
    cost_char = 1
    cost_meme = [0] * (before+1)
    for i in range(1,  before + 1 , step):
        cost_meme[i] = ((i * i) * cost_int) + (8 + 8) + (3 * cost_int) + (2 * cost_int)

    return cost_meme


def meme_dam_lev_rec(before, step):
    cost_int = 4
    cost_char = 1
    cost_meme = [0] * (before+1)

    cost_m_call = 0

    for i in range(1, before + 1, step):
        cost_m_call = (8 + 8) + (2 * cost_int) + cost_int + 8
        cost_meme[i] = (i + i) * cost_m_call

    return cost_meme


def meme_dam_lev_cache(before, step):
    cost_int = 4
    cost_char = 1
    cost_meme = [0] * (before+1)

    cost_m_call = 0

    for i in range(1, before + 1, step):
        cost_m_call = (8 + 8) + 2 * cost_int + cost_int + 8
        cost_meme[i] = (i + i) * cost_m_call + (i * i) * cost_int

    return cost_meme


def saveTableToCSV(lev, dam_lev_rec, dam_lev_rec_cache, count, step):
    file_name = "meme.csv"
    name_rows = ['size', 'lev', 'dam-lev', 'dam-lev-rec', 'dam-lev-rec-cash']
    with open(file_name, mode='w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(name_rows)
        for i in range(1 , count, step ):
            row = [i, lev[i], lev[i], dam_lev_rec[i], dam_lev_rec_cache[i]]
            writer.writerow(row)


main()
