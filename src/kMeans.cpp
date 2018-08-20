#include <iostream>
#include "KMeans.h"
using namespace std;

int main() {

    KMeans kMeans("../test/iris.data", "../data/ClassCenter.txt", "../data/Class.txt", 3);

    kMeans.Init();
    // kMeans.Execute(MhtDistance);
    kMeans.Execute(EucDistance);
    // kMeans.Execute(CbsDistance);
    kMeans.Print();
    kMeans.OutputClassCenter();
    kMeans.OutputClassVector();
    kMeans.Analyse();

    return 0;
}
