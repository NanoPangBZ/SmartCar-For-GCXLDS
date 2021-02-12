import sensor, image, time ,pyb

led = pyb.LED(1)
led.on()

usart = pyb.UART(3,115200,timeout_char=1000)
usart.init(115200,bits=8,parity=None,stop=1,timeout_char=1000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(150)
clock = time.clock()

led.off()

#初始化结束指示灯
led = pyb.LED(2)
led.on()
time.sleep(150)
led.off()

#色块相关变量和参数
Red_threshold = (23, 77, 18, 101, -16, 96)
Green_threshold = (9, 87, -67, -11, -2, 66)
Blue_threshold = (12, 69, 2, 86, -128, -23)
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]   #目标色块阈值列表
Name_List = ['Red','Green','Blue','QrCode']
Target_proportion = (1.05,2)        #色块长宽比例系数  W/H
Red_Blobs = None                    #本帧捕捉到的色块列表
Green_Blobs = None
Blue_Blobs = None
Target_Blobs = [Red_Blobs,Green_Blobs,Blue_Blobs]   #注意!: 这是嵌套列表 , 成员为色块列表的列表
#二维码相关变量和参数
QrCode_En = 1
QrCodes = None
QrCode_List = [QrCodes]

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

def QrCode_Find():
    if QrCode_En == 1:
        QrCode_List[0] = img.find_qrcodes()
        if len(QrCode_List[0])>0:
            led.on()
            time.sleep(50)
            led.off()
            for QrCode in QrCode_List[0]:
                print(QrCode.payload())
        else:
            QrCode_List[0] = None

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(strength=1.6)    #矫正画面
    TargetBlobs_Find()
    QrCode_Find()
    if QrCode_List[0] != None:
        QrCode_En = 0
    #print(clock.fps())
