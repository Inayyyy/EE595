# KNN and Naive Bayes
Name: Yani Jin
studentID: 3973887764
Email: yanijin@usc.edu

## Part 1: Use PCA and Implement KNN
Please download [python version CIFAR-10 dataset](https://www.cs.toronto.edu/~kriz/cifar.html) before running this program.

To run the code, use command `python knn_3973887764.py K D N PATH_TO_DATA`. For Example, `python knn_3973887764.py 5 100 960 ./cifar-10-batches-py/data_batch_1`. 

## Part 2: Naive Bayes
To run this program, use command `python naive_bayes_3973887764.py`. The input file `seeds_dataset.txt` is given under the same directory where the python file sits.

To write line 15, which initialize a numpy array of lists, I refer to [this](https://stackoverflow.com/questions/57364197/how-to-initialize-numpy-array-of-list-objects). 

To write line 36, I refer to [this blog talking about MLE](https://medium.com/@rrfd/what-is-maximum-likelihood-estimation-examples-in-python-791153818030).

In addition to self-implemented naive bayes, I use tools provided by sklearn, including Sklearn Naive Bayes, SVC, Decision Tree.

When computing training time and testing time, I defined the start time and end time here:

1. Training time:
   - Start time: after I read and processed row data
   - End time: once I got all Gaussian normal model parameters
2. Testing time:
   - Start time: once I start using model parameters to predict label for test set
   - End time: when the prediction for test set ends

