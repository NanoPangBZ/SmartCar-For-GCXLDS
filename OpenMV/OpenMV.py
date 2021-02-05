import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(100)

Red_threshold = (23, 77, 18, 101, -16, 96)
Green_threshold = (9, 87, -67, -11, -2, 66)
Blue_threshold = (12, 69, 2, 86, -128, -23)

Red_Blobs = None
Green_Blobs = None
Blue_Blobs = None
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]
Target_Blobs = [Red_Blobs,Green_Blobs,Blue_Blobs]
Find_qrcodes= None
Find_qrcodes_flag = 0
Name_List = ['Red','Green','Blue']
Target_proportion = (1.05,2)      #色块长宽比例系数  W/H

clock = time.clock()

def QRCode_Get():
    if Find_qrcodes_flag == 0:
        Find_qrcodes = img.find_qrcodes()
        if Find_qrcodes != None:
            for QRCode in Find_qrcodes:
                img.draw_rectangle(QRCode.rect())

def TargetBlobs_Get():
    temp = 0
    while temp < 3:
        Target_Blobs[temp] = img.find_blobs([Target_threshold[temp]],merge = True,area_threshold = 600)
        if Target_Blobs[temp] != None:
            for Blob in Target_Blobs[temp]:
                proportion = Blob.h()/Blob.w()
                if proportion > Target_proportion[0] and proportion < Target_proportion[1]:
                    img.draw_rectangle(Blob.rect())
                    img.draw_string(Blob.x(),Blob.y(),Name_List[temp])
        temp += 1

while(True):
    clock.tick()
    img = sensor.snapshot()
    if Find_qrcodes != None:
        Find_qrcodes_flag = 1
    else:
        Find_qrcodes_flag = 0
    TargetBlobs_Get()
    QRCode_Get()
    print(clock.fps())
