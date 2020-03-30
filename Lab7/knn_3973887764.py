import sys
import numpy as np
from sklearn.decomposition import PCA
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

def unpickle(file):
    import pickle
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

def image_to_grayscale(image):
    y = np.zeros(1024)
    for i in range(1024):
        r = image[i];
        g = image[i + 1024];
        b = image[i + 1024 * 2];
        y[i] = 0.299 * r + 0.587 * g + 0.114 * b
    return y

# input - set_of_images: row - number of images, column - 1024 red + 1024 green + 1024 blue
# grayscaled_images: row - number of images, column - 1024
def set_of_images_to_grayscale(set_of_images):
    grayscaled_images = np.zeros((len(set_of_images), 1024))
    for i in range(len(set_of_images)):
        grayscaled_images[i] = image_to_grayscale(set_of_images[i])
    return grayscaled_images
    
# input - data(grayscaled images): row - number of images, column - 1024
# input - D: target dimension
# result: row - number of images, column - number of dimensions after dimensionality reduction
def perform_PCA(data, D, N):
    pca = PCA(n_components = D,  svd_solver = 'full')
    # use training data to train PCA
    pca.fit(data[:N]) 
    return pca.transform(data)

# both a and b are arraies of D elements
def compute_inversed_distance(a, b):
    distance = 0
    for i in range(len(a)):
        distance += abs(a[i] - b[i])
    return 1/distance

# both test and training data are arraies of D elements
# return the most frequently occurred label among K nearrest neighbors
## Algorithm:
## given a test data
## compute the distance(test data, each training data)
## find the nearest k neighbors(smallest distance, largest 1/distance)
## count labels of each neighbors, return the most frequently occured label
def KNN_classifier(test, training_data, training_labels, k):
    count_label = np.zeros(10)  # magic number 10 means 10 labels in dataset
    distances = np.zeros(len(training_data))
    for i in range(len(training_data)):
        distances[i] = compute_inversed_distance(test, training_data[i])
    result = distances.argsort()[-k:][::-1]
    for i in result:
        count_label[training_labels[i]] += 1;
    return np.argmax(count_label) 

def main():
    # Assume all arguments are valid(K<=N, D<1024 ,N<1000)
    K = int(sys.argv[1])
    D = int(sys.argv[2])
    N = int(sys.argv[3])
    PATH_TO_DATA = sys.argv[4] #./cifar-10-batches-py/data_batch_1
    dictionary = unpickle(PATH_TO_DATA)
    
    # read labels
    training_labels = dictionary[b'labels'][:N]
    test_labels = dictionary[b'labels'][N:1000]
    
    # read data and perform PCA 
    data = dictionary[b'data'][:1000]
    data = perform_PCA(set_of_images_to_grayscale(data), D, N)
    training_data = data[:N]
    test_data = data[N:1000]    
    
    # self implemented KNN
    outfile = open("knn_results.txt", "w")
    correct_count = 0
    for i in range(len(test_data)):
        predict = KNN_classifier(test_data[i], training_data, training_labels, K)
        if predict == test_labels[i]:
            correct_count += 1
        outfile.write(str(predict) + " " + str(test_labels[i]) + '\n')
    outfile.write(str(correct_count/(1000-N)))
    outfile.close()
    
    # use sklearn
    outfile = open("knn_results_sklearn.txt", "w")
    KNN_Classifier = KNeighborsClassifier(n_neighbors = K, p = 1)
    KNN_Classifier.fit(training_data, training_labels)
    pred_test = KNN_Classifier.predict(test_data)
    for i in range(len(test_data)):
        outfile.write(str(pred_test[i]) + " " + str(test_labels[i]) + '\n')
    outfile.write(str(accuracy_score(test_labels, pred_test)))
    outfile.close()


main()
