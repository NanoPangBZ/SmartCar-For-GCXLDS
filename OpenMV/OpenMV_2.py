import sensor, image, time , pyb

#初始化LED,UART,clock对象
RedLed = pyb.LED(1)
BlueLed = pyb.LED(3)
clock = time.clock()
usart = pyb.UART(3,115200,timeout_char=100)
usart.init(115200,bits=8,parity=None,stop=1,timeout_char=1000,read_buf_len=64)
RedLed.on()

#初始化感光元件
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  #sensor.GRAYSCALE -> 灰度图(加快二维码扫描)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(180)
#sensor.set_contrast(2)              #对比度  -3~3
#sensor.set_auto_gain(False)         #关闭自动增益
#sensor.set_auto_whitebal(False)     #关闭白平衡

RedLed.off()

#色块阈值
Light_threshold = (89, 100, -29, 21, -26, 127)  #二维码扫描位图转化阈值
Red_threshold = (23, 77, 18, 101, -16, 96)
Green_threshold = (9, 87, -67, -11, -2, 66)
Blue_threshold = (12, 69, 2, 86, -128, -23)
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]
Target_List = [None,None,None,None] #过滤后的目标对象 前3元素为色块对象列表 第4元素为二维码对象(不是列表)
Target_proportion = (1.1,2.5)        #色块长宽比例过滤系数  H/W

def Usart_Read(timer):
    pass
#串口定时器(用于定时读取串口的数据)
tim = pyb.Timer(4,freq = 2)
tim.callback(Usart_Read)

def LED_Li():
    BlueLed.on()
    time.sleep(100)
    BlueLed.off()

def QrCode_Find():
    if Target_List[3] == None :
        img.binary([Light_threshold])   #根据阈值转化为位图,加快二维码识别
        QrCodes = img.find_qrcodes()
        if len(QrCodes)>0 :
            Target_List[3] = QrCodes[0]
            LED_Li()

def TargetBlobs_Find():
    temp = 0
    while temp<3:
        Target_List[temp] = img.find_blobs([Target_threshold[temp]],merge = True,area_threshold = 600)
        if len(Target_List[temp]) > 0:
            #过滤列表中不满足长宽比的色块对象
            for Blob in Target_List[temp]:
                proportion = Blob.h()/Blob.w()
                if proportion < Target_proportion[0] or proportion > Target_proportion[1]:
                    Target_List[temp].remove(Blob)
        temp += 1

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(1.6)
    TargetBlobs_Find()
    QrCode_Find()
    #绘图调试
    temp = 0
    while temp < 3:
        if len(Target_List[temp])>0 :
            for Blob in Target_List[temp]:
                img.draw_rectangle(Blob.rect())
        temp += 1
    if Target_List[3] != None:
        print(Target_List[3].payload())
    print(clock.fps())
