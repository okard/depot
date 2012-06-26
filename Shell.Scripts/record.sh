#!/usr/bin/env bash

#geometry = $(xwininfo | grep 'geometry' | awk '{print $2;}')

ffmpeg -f alsa -ac 2 -i pulse -acodec aac -ab 192 \
-f x11grab -r 15 -s 1440x1080 -i :0.0+240,0 -vcodec libx264 -preset ultrafast \
$1 

#-aspect 4:3
#702x845+767+105
# ffmpeg -f alsa -ac 2 -i pulse -f x11grab -r 30 -s 1024x768 -i :0.0 -acodec pcm_s16le 
#  -vcodec libx264 -vpre lossless_ultrafast -threads 0 output.mkv
#-acodec libfaac  -ar 48000 -ab 192k
#vorbis
# xdpyinfo | grep 'dimensions:'|awk '{print $2}'
# 1920/1080

#ffmpeg [-an] -s <width>x<height> -r <fps> -f x11grab -i \
# :0.0[+<ox,oy>] -codec mpeg4 -sameq -y <temporary-file>.mp4

# 1440 × 1080 +240, 0
# 4:3 und 16:9