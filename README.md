# BeatBoiGame
Little rythm minigame made for a school project.

All music uploaded by me as demo is my own property, and it is therefore free to use.
I do not support mapping music that belongs to other people without their approval.
Share your maps only when you are sure no rights are being broken.

To create your own maps simply create a folder in the "./data/songs/" directory and then paste there:
1. Your song in ".wav" format as "music.wav".
2. A dot hitting sound in the same format as "hitsound.wav".
3. A hit missing sound also in ".wav" as "misssound.wav".
4. A "data.bin" file which contains the tempo of the song in the first line (in BPM) and a boolean chart of the map.
For reference look up to provided examples.

If you're experiencing some kind of tempo offset try to modify the value stored in "./data/offset.bb". 
Open the file in notepad and experiment with the value to minimize the lag.

Have fun!

> 2019 Bartosz Kosmala
