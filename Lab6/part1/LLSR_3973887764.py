import matplotlib.pyplot as plt # matplotlib provides data visualization
import numpy as np # Multidimentional array objects and operations on them.
import pandas as pd # data analysis and manipulation tool
    
# Refer to https://medium.com/@dikshitkathuria1803/normal-equation-using-python-5993454fbb41
# Read input features and output values from txt file and plot
data = pd.read_csv('candyshop_data.txt', sep=",", header=None) # Read to a dataframe
x = data.iloc[:, 0].values # shape (97, )
y = data.iloc[:, 1].values # shape (97, )
plt.scatter(x, y, color = 'red')

# Update X: add one more column of all ones
length = len(data.index)
x_bias = np.ones((length,1)) # shape (97, 1)
x = np.reshape(x,(length,1))
updated_x = np.append(x_bias,x,axis=1) 

# Calculate (XT . X)-1
x_transpose = np.transpose(updated_x)   #calculating transpose
x_transpose_dot_x = x_transpose.dot(updated_x)  # calculating dot product
term1 = np.linalg.inv(x_transpose_dot_x) #calculating inverse

# Calculate (XT . y)
term2 = x_transpose.dot(y)

# Calculate w
w = term1.dot(term2)
print("w: ", w)

# Plot linear fit
y = w[0] + w[1] * x
plt.plot(x, y, color = 'blue')

plt.show()

y = w[0] + w[1] * 2
print("Predicted profit in dollar for the city of 20,000 population: ", y * 10000)
y = w[0] + w[1] * 5
print("Predicted profit in dollar for the city of 50,000 population: ", y * 10000)


