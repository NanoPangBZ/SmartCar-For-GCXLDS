import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(100)
print("初始化完成")

Red_threshold = (23, 77, 18, 101, -16, 96)
Green_threshold = (9, 87, -67, -11, -2, 66)
Blue_threshold = (12, 69, 2, 86, -128, -23)

Red_Blobs = None    #本帧捕捉到的色块列表
Green_Blobs = None
Blue_Blobs = None
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]   #目标色块阈值列表
Target_Blobs = [Red_Blobs,Green_Blobs,Blue_Blobs]   #注意!: 这是嵌套列表 , 成员为色块列表的列表
QrCodes = None           #从img中找到二维码对象(列表)
QrCode = None            #二维码对象
Save_Qrcode = None       #经过筛选后保存的二维码对象
qrcode_img = [3]          #拍到二维码后保存这张图片,累计保存三张
Name_List = ['Red','Green','Blue']
Target_proportion = (1.05,2)      #色块长宽比例系数  W/H

clock = time.clock()

def QrCode_Find():
    QrCodes = img.find_qrcodes()
    if len(QrCodes) > 0:
        qrcode_img[0] = img
        for QrCode in QrCodes:
            print(QrCode.payload())


def TargetBlobs_Find():
    temp = 0
    while temp < 3:
        Target_Blobs[temp] = img.find_blobs([Target_threshold[temp]],merge = True,area_threshold = 600)
        if len(Target_Blobs[temp]) > 0:
            for Blob in Target_Blobs[temp]:
                proportion = Blob.h()/Blob.w()
                if proportion > Target_proportion[0] and proportion < Target_proportion[1]:
                    img.draw_rectangle(Blob.rect())
                    img.draw_string(Blob.x(),Blob.y(),Name_List[temp])
        temp += 1

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(strength=1.6)    #矫正画面
    TargetBlobs_Find()
    QrCode_Find()
    #print(clock.fps())
