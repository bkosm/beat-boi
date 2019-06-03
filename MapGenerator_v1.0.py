import random as rd


def dotExists(probability):
    if probability is 0:
        return False
    elif probability is 100:
        return True
    elif rd.randint(0, int(100/probability)) is 0:
        return True
    else:
        return False


def main():
    bpm = int(input('Enter song bpm: '))
    songDurationMinutes = float(
        input('Enter song duration in [minutes.seconds]: '))
    probability = int(input('Enter dot probability in percent (0-100): '))
    isHarder = False
    isEasier = False
    if bpm <= 100:
        check = int(input(
            'Do you want to generate a harder map? (type \'0\' for easy or \'1\' for hard): '))
        if check is 1:
            isHarder = True
    if bpm >= 130:
        check = int(input(
            'Do you want to generate an easier map? (type \'0\' for easy or \'1\' for hard): '))
        if check is 0:
            isEasier = True

    if isEasier:
        bpm = int(bpm/2)

    if isHarder:
        bpm = int(bpm*2)

    songDuration = int(int(songDurationMinutes)*60 +
                       (songDurationMinutes-int(songDurationMinutes))*100)
    numberOfBeats = int(songDuration*bpm/30) - 15

    map = open(file='data.bin', mode='w')
    map.write(str(bpm))

    for i in range(0, numberOfBeats):
        bar = ""
        for j in range(4):
            if dotExists(probability):
                bar += '1'
            else:
                bar += '0'
        map.write('\n'+bar)

    map.close()


main()
print('Done')
