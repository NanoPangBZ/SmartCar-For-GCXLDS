import sensor,image#引入感光元件的模块

# 设置摄像头
sensor.reset()#初始化感光元件
sensor.set_pixformat(sensor.RGB565)#设置为彩色，用到其它参数时再上官方文档里找，下同
sensor.set_framesize(sensor.QVGA)#设置图像的大小
sensor.skip_frames(20)#跳过n张照片，在更改设置后，跳过一些帧，等待感光元件变稳定。

Red_threshold = (0, 70, 30, 85, -27, 68)
Green_threshold = (0, 70, 30, 85, -27, 68)

def RedFind():
    RedBlobs = img.find_blobs([Red_threshold],merge=True,area_threshold = 1000)
    MaxW = 0
    TargetBlob = None
    if RedBlobs:
        for RedBlob in RedBlobs:
            if RedBlob.area() > MaxW:
                MaxW = RedBlob.area()
                TargetBlob = RedBlob
        img.draw_rectangle(TargetBlob.rect())
        img.draw_string(TargetBlob[0],TargetBlob[1]-10,'Red',mono_space = False)
    return TargetBlob

# 一直拍照
while(True):
    img = sensor.snapshot()#拍摄一张照片，img为一个image对象
    x = RedFind()
