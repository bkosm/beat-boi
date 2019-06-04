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
        check = input(
            'Do you want to generate a easy or hard map? (type \"e\" for easy or \"h\" for hard): ')
        if check is 'h':
            isHarder = True
    elif bpm >= 130:
        check = input(
            'Do you want to generate a easy or hard map? (type \"e\" for easy or \"h\" for hard): ')
        if check is 'e':
            isEasier = True

    if isEasier:
        bpm = int(bpm/2)
    elif isHarder:
        bpm = int(bpm*2)

    songDuration = int(int(songDurationMinutes)*60 +
                       (songDurationMinutes-int(songDurationMinutes))*100)
    numberOfBeats = int(songDuration*bpm/15) - 10

    try:
        map = open(file='data.bin', mode='w')
        map.write(str(bpm))

        for i in range(numberOfBeats):
            bar = ""
            for j in range(4):
                if dotExists(probability):
                    bar += '1'
                else:
                    bar += '0'
            map.write('\n'+bar)

        map.close()
    except:
        print('Couldnt open \"data.bin\" file.')


main()
print('Done')
