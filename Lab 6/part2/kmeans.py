import matplotlib.pyplot as plt
import numpy as np
import struct
import os
import sys
import pandas as pd
import random
import math

# Refer to https://blog.csdn.net/u013597931/article/details/80099243
def load_images(file_name, number):
    binfile = open(file_name, 'rb')
    buffers = binfile.read()
    magic, num, rows, cols = struct.unpack_from('>IIII', buffers, 0)
    bits = number * rows * cols
    images = struct.unpack_from('>' + str(bits) + 'B', buffers, struct.calcsize('>IIII'))
    binfile.close()
    images = np.reshape(images, [number, rows * cols])
    images = np.true_divide(images, 255)
    return images

def read_from_input():
    return np.loadtxt('input.txt', delimiter = ',', usecols=range(784))
   
def read_from_train_images(N, train_images):
    lines = random.sample(range(N), 7)
    data = train_images[lines, :]
    return data

def cal_distance(a, b):
    sum = 0
    for i in range(784):
        sum += (a[i] - b[i])**2
    return math.sqrt(sum)

def assign_label(nlabels, train_images, centroids):
    for j in range(nlabels.size):
        mini = cal_distance(train_images[j, :], centroids[0, :]) 
        min_index = 0
        for i in range(1, 7): 
            curr = cal_distance(train_images[j, :], centroids[i, :])
            if curr < mini:
                min_index = i
        nlabels[j] = min_index
    return nlabels

def update_centroids(nlabels, train_images, N, centroids):
    sums = np.zeros(shape=(7, 784))
    counts = np.zeros(7, dtype = int)
    for i in range(N): 
        counts[nlabels[i]]+=1
        for j in range(784):
            sums[nlabels[i]][j] += train_images[i][j]
    new_centroids = np.zeros(shape = (7, 784))
    for i in range(7):
        if counts[i] != 0:
            new_centroids[i] = sums[i]/counts[i]
        else:
            new_centroids[i] = centroids[i]
    return new_centroids
    
def Kmeans(train_images, nlabels, centroids, N):
    new_centroids = np.zeros(shape = (7, 784))
    count = 0
    prev_centroids = centroids
    while not np.array_equal(new_centroids, prev_centroids):
        if count != 0:
            prev_centroids = new_centroids
        nlabels = assign_label(nlabels, train_images, centroids)
        new_centoids = update_centroids(nlabels, train_images, N, centroids)
        count+=1
    return nlabels
    
def main():
    N = int(sys.argv[1])
    Flag_of_Reading = int(sys.argv[2])

    script_dir = os.path.dirname(__file__) 
    filename_train_images = os.path.join(script_dir, "train-images.idx3-ubyte")
    train_images=load_images(filename_train_images, N)

    if Flag_of_Reading == 1:
        centroids = read_from_input()
    elif Flag_of_Reading == 0:
        centroids = read_from_train_images(N, train_images)
    else: 
        print("Invalid flag")

    nlabels = np.zeros(N, dtype = int)
    nlabels = Kmeans(train_images, nlabels, centroids, N)
    with open('results.txt', 'w') as the_file:
        for i in range(N):
            the_file.write("{}\n".format(nlabels[i]))

main()













