import time
import math
import serial
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.tri as mtri

dataList = np.array([])
reduceData = np.array([])
finalData = np.array([])
layers = np.array([])

dataList_x = np.array([])
dataList_y = np.array([])
dataList_z = np.array([])

state =110
steps =-1
levels = -1
height = -1

i=0
num=0
l=0
dis=0
x_val=0
y_val=0

ser = serial.Serial("COM5", 9600)
time.sleep(2)

if height==-1 and levels==-1 and state ==110 and steps ==-1 :
    while levels== -1:
       ser.write(b'a')
       levels_string= ser.readline().decode('utf-8')
       levels = int(levels_string)
    print(levels)

if levels>=1:
    while height== -1:
        ser.write(b'd')
        height_string= ser.readline().decode('utf-8')
        height = int(height_string)
    print(height)

if height>0 and levels>=1:
    while steps== -1:
        ser.write(b'b')
        steps_string= ser.readline().decode('utf-8')
        steps = int(steps_string)
    print(steps)

split = steps*levels
l = split*5
print(l)

if l==5*split:
    while state==110:
       ser.write(b'i')
       state_string= ser.readline().decode('utf-8')
       state = int(state_string)
print(state)

if state == 111:
    ser.write(b'c')
    for i in range(l):
        arduinoData_string = ser.readline().decode('utf-8')
        arduinoData_float = int(arduinoData_string)
        dataList = np.append(dataList,arduinoData_float)

    reduceData = np.array_split(dataList,split)
    
    for j in range(split):
        sortData = np.sort(reduceData[j])[1]

        dis = -8.046e-07*(sortData**3) + 0.001581*(sortData**2) - 1.216*(sortData) + 409.7
        finalData = np.append(finalData,dis)

    layers = np.array_split(finalData,levels)

    for a in range (levels):
        for b in range (steps):
            x_val = (116 - layers[a][b]) * math.cos(2*b * math.pi / steps)
            y_val = (116 - layers[a][b]) * math.sin(2*b * math.pi / steps)
            dataList_x = np.append(dataList_x,x_val)
            dataList_y = np.append(dataList_y,y_val)
            
    for k in range (levels):
        for h in range (steps):
            num = (k+1) * (height/(levels))
            dataList_z = np.append(dataList_z,num)

    x = dataList_x
    y = dataList_y
    z = dataList_z

    triang = mtri.Triangulation(x, y)
                                
    fig = plt.figure(figsize=(8, 8))
    ax = plt.axes(projection='3d')
    
    ax.view_init(10, 10)

    ax.set_xlim(-50, 50)
    ax.set_ylim(-50, 50)
    ax.set_zlim(-10, 100)

    ax.set_title('3D plotting of scatter chart')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    

    ax.scatter(x, y, z, c=z, s=1,cmap='hsv')

    # ax.plot_trisurf(triang, z, cmap='jet')
    # ax.triplot(triang, c="#D3D3D3", marker='.', markerfacecolor="#DC143C",
    # markeredgecolor="black", markersize=10)

   # plt.draw()
    plt.show()  