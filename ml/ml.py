from sklearn.linear_model import LinearRegression
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier

from sklearn.model_selection import train_test_split

from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.metrics import f1_score

from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler, PolynomialFeatures

from sklearn.model_selection import GridSearchCV

import seaborn as sns

parameters = {'kernel':(['rbf', 'linear', 'sigmoid', 'poly']), 'C':[0.25,0.5,1,2,4,8,16]}

import pandas as pd
#import pandas.tools as pdt
from pandas.plotting import scatter_matrix, radviz

import matplotlib.pyplot as plt

#predictor = SVC()

#PolynomialFeatures(interaction_only=False), StandardScaler(), SVC(max_iter=10000, C=10

predictor = make_pipeline(PolynomialFeatures(interaction_only=True), SVC(max_iter=20000, C=10, kernel='rbf'))
#predictor = SVC()

clf = GridSearchCV(SVC(), parameters)

data = pd.read_csv('train.csv')
data.drop(data.columns[[21]], axis=1, inplace=True)

# Проверяем, всё ли правильно загрузилось

#print(data.head(5))
#print(data.describe(include='all'))
#sns.heatmap(data.corr())
#plt.savefig("heatmap.png")

#fig = scatter_matrix(data, alpha=0.05, figsize=(32, 32))
#fig = radviz(data.iloc[:,:], class_column="target")
#plt.savefig("1.png")

# ".iloc" принимает row_indexer, column_indexer
X = data.iloc[:,:-1]
print(len(X.columns))
X = X.values
# Теперь выделим нужный столбец
y = data['target']

#for i in range(32):
    #X[i] = (X[i] - X[i].mean()) / X[i].std()
    #print(i, pd.DataFrame(X[i]).describe())

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=17)

#print(clf.fit(X, y))
#print(clf.cv_results_)

predictor.fit(X_train, y_train)

prediction = predictor.predict(X_test)

print(accuracy_score(prediction, y_test))
print(confusion_matrix(prediction, y_test))
print(classification_report(prediction, y_test))

test = pd.read_csv('test.csv')
test.drop(test.columns[[21]], axis=1, inplace=True)
print(len(test.columns))
test = test.values

#for i in range(32):
    #test[i] = (test[i] - test[i].mean()) / test[i].std()
    #print(i, pd.DataFrame(test[i]).describe())

predictor.fit(X, y)

test_prediction = predictor.predict(test)

pd.DataFrame(test_prediction).to_csv('res.csv', index=False, header=['target'])

