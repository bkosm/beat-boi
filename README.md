# BeatBoiGame
<p align="center">
  <b>Little rythm minigame made for a semester project.</b>
</p>

<p align="center">
<img src="https://github.com/bart-kosmala/BeatBoiGame/blob/master/SMFLsetup/resources/pictures/splashscreen.png">
</p>

All music uploaded by me as demo is my own property, and it is therefore free to use.
I do not support mapping music that belongs to other people without their approval.
Share your maps only when you are sure no rights are being broken.

<p align="center">
<a href="https://www.mediafire.com/file/zxkpqg76eipmac6/BeatBoi_v1.0.rar/file"><b>v1.0 DOWNLOAD</b></a>
</p>


To create your own maps simply create a folder in the **"./data/songs/"** directory and then paste there:
* Your song in **".wav"** format as **"music.wav"**.
* A dot hitting sound in the same format as **"hitsound.wav"**.
* A hit missing sound also in **".wav"** as **"misssound.wav"**.
* A **"data.bin"** file which contains the tempo of the song in the first line (in BPM) and a boolean chart of the map.

For reference look up to provided examples.

If you're experiencing some kind of tempo offset try to modify the value stored in **"./data/offset.bb"**. 
Open the file in notepad and experiment with the value to minimize the lag.

_The release also contains a python script for generating random maps. Enter the information you're asked for concerning the song and it will generate a "data.bin" file with a random chart ready to play._

**Have fun!**

> 2019 Bartosz Kosmala
