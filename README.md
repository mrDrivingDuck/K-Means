# K-Means - Algorithm of Clustering

Author : Mr Dk.

Date : 2018.6.16, Nanjing, Jiangsu, China.

Description : Implementation of K-Means algorithm with C/C++.

---

#### Data Set

* Iris - http://archive.ics.uci.edu/ml/datasets/Iris/
* Format : arg1,arg2,arg3,arg4,tag
  * arg1 : sepal length in cm
  * arg2 : sepal width in cm
  * arg3 : petal length in cm
  * arg4 : petal width in cm
  * tag : _Iris Setosa_ / _Iris Versicolour_ / _Iris Virginica_

---

#### How To Use

* include the header file _KMeans.h_
* Instantiate an object of class _KMeans_
* Constructor parameters:
  * __string inputDir__ : File of data sets
  * __string center_dir = ""__ : File for output of cluster center
  * __string cluster_dir = ""__ : File for output of cluster members
  * __int classes = 2__ : Number of classes to be cluststered
* Call _KMeans::Init()_ to initialize
* Call _KMeans::Execute()_ to execute (In different similarity measure)
* _Print_ / _Output_ / _Analyse_

---

#### Test Result

* __Euclidean Distance__ : 
  * _Iris-setosa_: __0__ _Iris-versicolor_: __3__ _Iris-virginica_: __36__
  * _Iris-setosa_: __0__ _Iris-versicolor_: __47__ _Iris-virginica_: __14__
  * _Iris-setosa_: __50__ _Iris-versicolor_: __0__ _Iris-virginica_: __0__
* __Manhattan Distance__:
  * _Iris-setosa_: __0__ _Iris-versicolor_: __48__ _Iris-virginica_: __15__
  * _Iris-setosa_: __0__ _Iris-versicolor_: __2__ _Iris-virginica_: __35__
  * _Iris-setosa_: __50__ _Iris-versicolor_: __0__ _Iris-virginica_: __0__
* __Chebyshev distance__ :
  * _Iris-setosa_: __1__ _Iris-versicolor_: __50__ _Iris-virginica_: __25__
  * _Iris-setosa_: __49__ _Iris-versicolor_: __0__ _Iris-virginica_: __0__
  * _Iris-setosa_: __0__ _Iris-versicolor_: __0__ _Iris-virginica_: __25__

---

#### Summarize

As far as it goes, _Iris_ seems to be the best data set to test this algorithm.

---

