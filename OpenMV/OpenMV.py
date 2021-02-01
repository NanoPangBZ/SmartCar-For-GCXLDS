# Untitled - By: 马猴烧酒哒 - 周一 2月 1 2021

import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(100)

Red_threshold = (0, 70, 30, 85, -27, 68)
Green_threshold = (0, 100, -128, -17, 94, 5)
Blue_threshold = (14, 68, 10, 127, -128, -17)

Red_Blobs = None
Green_Blobs = None
Blue_Blobs = None
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]
Target_Blobs = [Red_Blobs,Green_Blobs,Blue_Blobs]

clock = time.clock()

def TargetBlobs_Get():
    temp = 0
    while temp < 3:
        Target_Blobs[temp] = img.find_blobs([Target_threshold[temp]],merge = True,area_threshold = 600)
        if Target_Blobs[temp] != None:
            for Blob in Target_Blobs[temp]:
                img.draw_rectangle(Blob.rect())
        temp += 1

while(True):
    clock.tick()
    img = sensor.snapshot()
    TargetBlobs_Get()
    print(clock.fps())
