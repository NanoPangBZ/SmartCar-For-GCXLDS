import sensor, image, time , pyb

#初始化LED,UART,clock对象
RedLed = pyb.LED(1)
GreenLed = pyb.LED(2)
BlueLed = pyb.LED(3)
clock = time.clock()
usart = pyb.UART(3,115200,timeout_char=100)
usart.init(115200,bits=8,parity=None,stop=1,timeout_char=1000,read_buf_len=64)

#初始化感光元件
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  #sensor.GRAYSCALE -> 灰度图(加快二维码扫描)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(50)
#sensor.set_contrast(2)              #对比度  -3~3
sensor.set_brightness(1)            #亮度
sensor.set_auto_gain(False)         #自动增益
#sensor.set_auto_whitebal(False,(-5.243186, -6.02073, -2.498888))     #自动白平衡 实验室光照增益
sensor.set_auto_whitebal(False,(-6.02073, -5.243186, -1.972561))
sensor.set_auto_exposure(False)     #自动曝光


#色块阈值
Light_threshold = (0, 52, -128, 127, -128, 127)  #二维码扫描位图转化阈值
#Red_threshold = (23, 77, 18, 101, -16, 96)
Red_threshold = (6, 68, 36, 127, -3, 47)
Green_threshold = (29, 67, -91, -27, -3, 49)
Blue_threshold = (0, 64, -72, 49, -94, -22)
Target_threshold = [Red_threshold,Green_threshold,Blue_threshold]
Target_List = [None,None,None,None] #过滤后的目标对象 前3元素为色块对象列表 第4元素为二维码对象(不是列表)
Target_proportion = (1.1,2.5)        #色块长宽比例过滤系数  H/W

OpenMVState = [2,0]

def Usart_Read():
    if usart.any() != 0:
        OpenMVState[0] = int(usart.read(1))
        RGB_Li()
        RGB_Li()

def QrCode_Find():
    if Target_List[3] == None :
        #img.binary([Light_threshold])   #根据阈值转化为位图,加快二维码识别
        QrCodes = img.find_qrcodes()
        if len(QrCodes)>0 :
            #扫描到二维码,载入Target_List[3],
            Target_List[3] = QrCodes[0]
            RGB_Li()
    else:
        data = Target_List[3].payload()
        print(data)
        Usart_Send(data)

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
                else:
                    img.draw_rectangle(Blob.rect(),thickness = 5,color = (175,0,175))
                    data = bytearray([temp,int(Blob.cx()/10),Blob.w()])
                    #print(data)
                    print(Blob.w())
                    Usart_Send(data)
        temp += 1

def Usart_Send(Data):
    usart.write(bytearray([0xee]))
    usart.write(bytearray([OpenMVState[0]]))
    usart.write(Data)
    usart.write(bytearray([0xde]))

#灯光闪烁指示
def RGB_Li():
    RedLed.off()
    GreenLed.off()
    BlueLed.off()
    time.sleep(50)
    RedLed.on()
    GreenLed.on()
    BlueLed.on()

#RGB补光
RedLed.on()
GreenLed.on()
BlueLed.on()
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(1.6)
    if OpenMVState[0] == 0:
        usart.write('A')
    elif OpenMVState[0] == 1:
        QrCode_Find()
    elif OpenMVState[0] ==2 or OpenMVState[0] ==3:
        TargetBlobs_Find()
    Usart_Read()
    #print(sensor.get_rgb_gain_db())

    #绘图调试
    '''
    temp = 0
    while temp < 3:
        if len(Target_List[temp])>0 :
            for Blob in Target_List[temp]:
                img.draw_rectangle(Blob.rect())
        temp += 1
    if Target_List[3] != None:
        print(Target_List[3].payload())
    '''
    #print(clock.fps())
