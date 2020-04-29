import sensor, image, time, machine, pyb, nn

barCol = 0
def DrawPgsBar(img, barLen, loopCnt, startTick, width=5):
    global barCol
    lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
    if (barCol & 0x80) == 0:
        c = barCol & 0x7F
    else:
        c = 128 - (barCol & 0x7F)
    img.draw_rectangle(2, 2, barLen + 2, width, color=(0,0,0))
    img.draw_rectangle(2, 3, lnLen, width-2, fill=True, color=(c,c,c))
    barCol += 16

def BlobTest(thresholds, loopCnt = 390, barLen = 120):
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.CIF)
    #sensor.set_windowing((320,240))
    sensor.set_auto_gain(True)
    #sensor.set_auto_whitebal(True) # must be turned off for color tracking
    clock = time.clock()
    avg = 0.0
    startTick = time.ticks()
    while(True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        img.draw_string(4, 8, 'color blob detect', color=(0,0,0), scale = 2)
        t0 = time.ticks()
        blobSet = img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200)
        t1 = time.ticks() - t0
        avg = avg * 0.95 + t1 * 0.05
        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        for blob in blobSet:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
        print('algo time cost : %.2f ms' % (avg))

def CorrTest(loopCnt = 220, barLen=120):
    sensor.reset()

    # Sensor settings
    sensor.set_contrast(1)
    sensor.set_gainceiling(16)

    sensor.set_framesize(sensor.QVGA)
    sensor.set_pixformat(sensor.RGB565)
    #sensor.set_windowing((480,272))
    clock = time.clock()
    avg = 0.0
    startTick = time.ticks()
    corr = 0.3
    while (True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        for i in range(7):
            img.draw_rectangle(160-i*15, 120-i*15, i*15*2, i*15*2)
        corr += 0.05
        if corr >= 4.0:
            corr = 0.3
        img.lens_corr(corr)

        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        img.draw_string(4,4,'Lens correction %.2f' % (corr), color=(0,0,0))

def FaceTest(loopCnt = 220, barLen=120):
    sensor.reset()

    # Sensor settings
    sensor.set_contrast(1)
    #sensor.set_gainceiling(16)
    # HQVGA and GRAYSCALE are the best for face tracking.

    #sensor.set_framesize(sensor.VGA)
    #sensor.set_windowing((320,240))
    sensor.set_framesize(sensor.VGA)
    sensor.set_windowing((320,240))
    sensor.set_pixformat(sensor.GRAYSCALE)
    #sensor.set_auto_gain(False)
    #sensor.set_auto_whitebal(True) # must be turned off for color tracking
    # Load Haar Cascade
    # By default this will use all stages, lower satges is faster but less accurate.
    face_cascade = image.HaarCascade("frontalface", stages=25)
    print(face_cascade)
    clock = time.clock()
    avg = 0.0
    startTick = time.ticks()
    while (True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        img.draw_string(4,4,'Face Detect', color=(0,0,0))
        t0 = time.ticks()
        objects = img.find_features(face_cascade, threshold=0.9, scale_factor=1.35)
        t1 = time.ticks() - t0
        avg = avg * 0.90 + t1 * 0.10
        fID = 0
        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        for r in objects:
            img.draw_rectangle(r, thickness=3)
            img.draw_rectangle(r[0], r[1], 48, 10, fill=True)
            fID += 1
            s = 'face %d' % (fID)
            img.draw_string(r[0], r[1], s, color = (0,0,0))
        print('algo time cost : %.2f ms' % (avg))

def LENetTest(loopCnt = 600, isFull = False, barLen = 80):
    sensor.reset()                          # Reset and initialize the sensor.
    sensor.set_contrast(3)
    sensor.set_pixformat(sensor.GRAYSCALE)     # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.CIF)       # Set frame size to QVGA (320x240)
    sensor.set_windowing((96, 96))        # Set 128x128 window.
    sensor.set_auto_gain(True)
    sensor.set_auto_whitebal(False)
    sensor.set_auto_exposure(False)
    sensor.skip_frames(time = 400)          # Wait for settings take effect.

    net = nn.load('/lenet.network')
    labels = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    clock = time.clock()
    tAvg = 0.0
    startTick = time.ticks()
    while(True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        t0 = time.ticks()
        tmp_img = img.copy().binary([(120,255)], invert=True)
        lst = net.search(tmp_img, threshold=0.8, min_scale=1.0, scale_mul=0.8, \
        x_overlap=-1, y_overlap=-1, contrast_threshold=0.5, softmax=False)
        t1 = time.ticks() - t0
        tAvg = tAvg * 0.9 + t1 * 0.1
        img.draw_string(4,8,'LENET', color=(0,0,0))
        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        for obj in lst:
            print('Detected %s - Confidence %f%%' % (labels[obj.index()], obj.value()))
            img.draw_rectangle(obj.rect(), color=(255,255,255))
            img.draw_string(4,4,labels[obj.index()])
        print('algo time cost : %.2f ms' % (tAvg))


def CIFAR10Test(loopCnt = 600, isFull = False, barLen = 105):
    pyb.LED(1).off()
    sensor.reset()                          # Reset and initialize the sensor.
    sensor.set_contrast(3)
    sensor.set_pixformat(sensor.RGB565)     # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.VGA)       # Set frame size to QVGA (320x240)
    sensor.set_windowing((192, 192))        # Set window
    sensor.skip_frames(time = 1300)          # Wait for settings take effect.
    sensor.set_auto_gain(False)
    #sensor.set_framerate(0<<9|1<<12)
    if isFull:
        net = nn.load('/cifar10.network')
    else:
        net = nn.load('/cifar10_fast.network')
    labels = ['plane', 'auto', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
    clock = time.clock()
    tAvg = 0.0
    startTick = time.ticks()
    while (True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        t0 = time.ticks()
        lst = net.search(img, threshold=0.640, min_scale=1, scale_mul=0.8, \
        x_overlap=-1, y_overlap=-1, contrast_threshold=0.5)
        t1 = time.ticks() - t0
        tAvg = tAvg * 0.9 + t1 * 0.1
        img.draw_string(4,8,'CIFAR-10: classify:\nplane,auto,cat,dog,\ndeer,horse,frog,ship,\ntruck,horse', color=(0,0,0))
        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        for obj in lst:
            print(' %s  - Confidence %f%%' % (labels[obj.index()], obj.value()))
            rc = obj.rect()
            #img.draw_rectangle(rc, color=(255,255,255))
            img.draw_rectangle(barLen+10,1,50,8,fill=True,color=(0,0,0))
            img.draw_string(barLen+10, 0, labels[obj.index()])
        print('algo time cost : %.2f ms' % (tAvg))

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green things. You may wish to tune them...
thresholds = [(30, 100, 15, 127, 15, 127), # generic_red_thresholds
                          (30, 100, -64, -8, -32, 32), # generic_green_thresholds
                          (0, 15, 0, 40, -80, -20)] # generic_blue_thresholds
# You may pass up to 16 thresholds above. However, it's not really possible to segment any
# scene with 16 thresholds before color thresholds start to overlap heavily.
thresholds2 = [(50, 92, -68, -16, 9, 119)]
thresholds3 = [(92, 64, -81, -9, 13, 75),(63, 25, 86, 63, 11, 127),(27, 69, -50,15, -67, -22),\
(11, 67, 41, -37, -96, -21),(85, 78, -3, 18, 98, 17)]

def LEDTest():
    i = 0
    while(True):
        if i & 1:
            pyb.LED(1).on()
        else:
            pyb.LED(1).off()
        if i & 2:
            pyb.LED(2).on()
        else:
            pyb.LED(2).off()
        if i & 4:
            pyb.LED(3).on()
        else:
            pyb.LED(3).off()
        i += 1
        time.sleep(5)

def QRCodeTest(loopCnt = 120, barLen = 120):
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.VGA)
    sensor.set_windowing((360,240))
    sensor.skip_frames(time = 1000)
    sensor.set_auto_gain(False)
    clock = time.clock()
    avg = 0.0
    startTick = time.ticks()
    while (True):
        if time.ticks() - startTick > loopCnt:
            break
        clock.tick()
        img = sensor.snapshot()
        #img.lens_corr(1.5) # strength of 1.8 is good for the 2.8mm lens.
        img.draw_string(4,8,'QR Code Scan', color=(0,255,0))
        t1 = time.ticks()
        codeSet = img.find_qrcodes()
        t2 = time.ticks() - t1
        lnLen = (barLen * (loopCnt - (time.ticks() - startTick))) // loopCnt
        DrawPgsBar(img, barLen, loopCnt, startTick)
        avg = avg * 0.92 + t2 * 0.08

        for code in codeSet:
            rc = code.rect()
            img.draw_rectangle(rc, thickness = 2, color=(0,191,255))
            #print(type(code))
            #print(code.payload())

            sPayload = code.payload()
            #print(len(sPayload))
            lnLen = len(sPayload) * 8
            if rc[0] + lnLen >= 400:
                x = 400 - lnLen
            else:
                x = rc[0]
            img.draw_rectangle(x - 1, rc[1]+1, lnLen+2, 8, color=(0,0,0), fill=True)
            img.draw_string(x, rc[1], sPayload)
        print('algo time cost : %.2f ms' % (avg))

while (True):
    #LEDTest()
    pyb.LED(1).off()
    pyb.LED(2).off()
    pyb.LED(3).on()
    #pyb.LED(2).on()
    #pyb.LED(3).on()
    pyb.LED(4).off()
    CorrTest(9000)
    BlobTest(thresholds3, 40000)
    QRCodeTest(40000)
    FaceTest(40000)
    LENetTest(40000)  # RT1052 does not have enough RAM to run this
    #If you use RT1052, 'isFull' should be False
    CIFAR10Test(40000, isFull = True)




    #LENETTest(20000)

