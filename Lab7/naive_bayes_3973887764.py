# dataset: 7 features, the last column is class
import numpy as np
from scipy.stats import norm
import time
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn import tree

# https://stackoverflow.com/questions/57364197/how-to-initialize-numpy-array-of-list-objects
# Calculate prior probability of each label and group up each feature for each label
# feature x1, x2, ..., x7 | label(1,2,3)
# E.g. relocation[1][2] contians a list of data from feature x3 for label 2 
def cal_prior_dist(training):
    li = np.zeros(3)
    relocation = np.frompyfunc(list, 0, 1)(np.empty((3,7), dtype=object))
    for data in training:
        label = int(data[-1])
        li[label - 1] += 1
        for i in range(7):
            relocation[label - 1][i].append(data[i])
    return relocation, np.true_divide(li, len(training))

# Calculate mean and variance for a numpy array
def cal_param(a):
    return a.mean(), a.std()

# https://medium.com/@rrfd/what-is-maximum-likelihood-estimation-examples-in-python-791153818030
# Calculate log likelihood for a test dataset
def testing(test, param, flag, dur):
    test_start_time = time.time()
    count_acc = 0
    for item in test:  # a row of data
        prob = np.zeros(3)
        for i in range(7):
            for j in range(3):
                prob[j] += np.log(norm.pdf(item[i], param[7*j+i][0], param[7*j+i][1]))
        # compare pred_label_for_item and real_label_for_item
        if (np.argmax(prob) + 1) == int(item[-1]):
            count_acc += 1
    test_dur = time.time()-test_start_time
    if flag == 0:
        print("Training acc: {0:.2f}% Training time: {1:.2f}s".format((count_acc/len(test)*100), dur))
    if flag == 1:
        print("Testing acc: {0:.2f}% Testing time: {1:.2f}s".format(count_acc/len(test)*100, test_dur))
    
def seperate(training, test):
    return training[:, :-1], training[:, -1], test[:, :-1], test[:, -1]

def other_ML(training, test, flag):
    training_data, training_label, test_data, test_label = seperate(training, test)
    clf = 0
    if flag == 0:
        clf = GaussianNB()
        print("Sklearn Naive Bayes: ")
    if flag == 1:
        clf = SVC(gamma='auto')
        print("SVC: ")
    if flag == 2:
        clf = tree.DecisionTreeClassifier()
        print("Decision Tree: ")
    train_start = time.time()
    clf.fit(training_data, training_label)
    train_dur = time.time() - train_start
    # test training set
    print("Training acc: {0:.2f}% Training time: {1:.2f}s".format(clf.score(training_data, training_label)*100, train_dur))
    # test test set
    test_start = time.time()
    diffs = clf.predict(test_data) - test_label
    test_dur = time.time() - test_start
    count_test_error = np.count_nonzero(diffs)
    print("Testing acc: {0:.2f}% Testing time: {1:.2f}s".format(((len(test)-count_test_error)/len(test)*100), test_dur))
    

def main():
    data = np.loadtxt("seeds_dataset.txt")
    np.random.shuffle(data)
    training, test = data[:int(len(data)*0.8),:], data[int(len(data)*0.8):,:]
    train_start_time = time.time()
    relocation, prob = cal_prior_dist(training)
    # calculate model parameters
    model_param = []
    for row in relocation:
        for i in row:
            model_param.append(cal_param(np.array(i)))
    train_dur = time.time() - train_start_time
    print("My Naive Bayes: ")
    testing(training, model_param, 0, train_dur)
    testing(test, model_param, 1, 0)

    other_ML(training, test, 0)
    other_ML(training, test, 1)
    other_ML(training, test, 2)
main()
