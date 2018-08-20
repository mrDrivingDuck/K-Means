#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
using namespace std;

#define EucDistance 1
#define MhtDistance 2
#define CbsDistance 3

class KMeans {
    private:
        string inputDir;
        string center_dir;
        string cluster_dir;
        int classes;
        int length;

        vector<vector<double> > AllVectors;
        vector<vector<double> > ClassesCenter;
        map <int, string> Tag;
        map <int, int> ClassMap;

    public:
        KMeans(string inputDir, string center_dir = "", string cluster_dir = "", int classes = 2) {
            this -> inputDir.assign(inputDir);
            this -> center_dir = center_dir;
            this -> cluster_dir = cluster_dir;
            this -> classes = classes;
            AllVectors.reserve(32);
            ClassesCenter.reserve(this -> classes);
        }
        void Init();
        void Execute(int distance_type);
        void OutputClassCenter();
        void OutputClassVector();
        void Print();
        void Analyse();
        double EuclideanDistance(vector <double> &X, vector <double> &Y);
        double ManhattanDistance(vector <double> &X, vector <double> &Y);
        double ChebyshevDistance(vector <double> &X, vector <double> &Y);
};

double KMeans::EuclideanDistance(vector <double> &X, vector <double> &Y) {
    double sum = 0.0;
    for (unsigned int i = 0; i < X.size(); i++) {
        sum += pow(X[i] - Y[i], 2.0);
    }
    return pow(sum, 0.5);
}

double KMeans::ManhattanDistance(vector <double> &X, vector <double> &Y) {
    double sum = 0.0;
    for (unsigned int i = 0; i < X.size(); i++) {
        sum += (abs(X[i] - Y[i]));
    }
    return sum;
}

double KMeans::ChebyshevDistance(vector <double> &X, vector <double> &Y) {
    double sum = 0.0;
    for (unsigned int i = 0; i < X.size(); i++) {
        sum += pow(abs(X[i] - Y[i]), DBL_MAX);
    }
    return pow(sum, 1.0 / DBL_MAX);
}

void KMeans::Init() {
    
    string line_buf;
    ifstream fileIn (inputDir.c_str());
    if (!fileIn.is_open()) {
        cout << "OPEN INPUT FILE ERROR" << endl;
        exit(0);
    }

    int i = 0;

    while (!fileIn.eof()) {
        vector <double> Vector;
        Vector.reserve(4);

        getline(fileIn, line_buf);
        char line[1024];
        strcpy(line, line_buf.c_str());
        if (0 == strcmp(line, "")) {
            break;
        }

        char *p = strtok(line, ",");
        while (p) {
            stringstream ss;
            string temp (p);

            if (temp == "Iris-setosa") {
                Tag.insert(pair <int, string> (i, temp));
                break;
            } else if (temp == "Iris-versicolor") {
                Tag.insert(pair <int, string> (i, temp));
                break;
            } else if (temp == "Iris-virginica") {
                Tag.insert(pair <int, string> (i, temp));
                break;
            }

            double convert;
            ss << p;
            ss >> convert;
            ss.str("");
            ss.clear();
            Vector.push_back(convert);

            p = strtok(NULL, ",");
        }

        AllVectors.push_back(Vector);
        i++;
    }

    fileIn.close();

    length = AllVectors[0].size();
    for (int i = 0; i < classes; i++) {
        vector <double> Vector (AllVectors[i]);
        ClassesCenter.push_back(Vector);
    }
}

void KMeans::Execute(int distance_type) {
    bool iteration = true;
    while (iteration) {
        iteration = false;

        for (unsigned int i = 0; i < AllVectors.size(); i++) {
            double d_min = DBL_MAX;
            int nearest_class_index = 0;

            for (unsigned int j = 0; j < ClassesCenter.size(); j++) {
                double dis; 
                switch(distance_type) {
                    case EucDistance:
                        dis = EuclideanDistance(AllVectors[i], ClassesCenter[j]);
                        break;
                    case MhtDistance:
                        dis = ManhattanDistance(AllVectors[i], ClassesCenter[j]);
                        break;
                    case CbsDistance:
                        dis = ChebyshevDistance(AllVectors[i], ClassesCenter[j]);
                        break;
                    default:
                        break;
                }
                if (dis < d_min) {
                    d_min = dis;
                    nearest_class_index = j;
                }
            }

            map <int, int>::iterator mapIter = ClassMap.find(i);
            if (mapIter == ClassMap.end()) {
                ClassMap.insert(pair <int, int> (i, nearest_class_index));
                iteration = true;
            } else if (mapIter -> second != nearest_class_index) {
                mapIter -> second = nearest_class_index;
                iteration = true;
            }
        }

        vector <vector <double> > UpdateCenter (classes, vector <double> (length, 0.0));
        vector <int> in_class_num (classes, 0);
        for (map <int, int>::iterator mapIter = ClassMap.begin(); mapIter != ClassMap.end(); mapIter++) {
            in_class_num[mapIter -> second]++;
            for (int i = 0; i < length; i++) {
                UpdateCenter[mapIter -> second][i] += AllVectors[mapIter -> first][i];
            }
        }
        for (unsigned int i = 0; i < UpdateCenter.size(); i++) {
            for (unsigned int j = 0; j < UpdateCenter[i].size(); j++) {
                if (in_class_num[i] != 0) {
                    UpdateCenter[i][j] /= in_class_num[i];
                }
            }
            ClassesCenter[i].assign(UpdateCenter[i].begin(), UpdateCenter[i].end());
        }
        for (unsigned int i = 0; i < in_class_num.size(); i++) {
            if (in_class_num[i] == 0) {
                srand((unsigned) time(NULL));
                int random = rand() % AllVectors.size();
                ClassesCenter[i].assign(AllVectors[random].begin(), AllVectors[random].end());
                iteration = true;
            }
        }
    }
}

void KMeans::Print() {
    for (unsigned int i = 0; i < ClassesCenter.size(); i++) {
        for (unsigned int j = 0; j < ClassesCenter[i].size(); j++) {
            // cout << ClassesCenter[i][j] << " ";
            printf ("%10lf ", ClassesCenter[i][j]);
        }
        cout << endl;
    }
}

void KMeans::OutputClassCenter() {
    ofstream ofs (center_dir.c_str());
    if (!ofs.is_open()) {
        cout << "NO OUTPUT FILE" << endl;
        return;
    }

    for (unsigned int i = 0; i < ClassesCenter.size(); i++) {
        for (unsigned int j = 0; j < ClassesCenter[i].size(); j++) {
            ofs << ClassesCenter[i][j] << " ";
        }
        ofs << endl;
    }

    ofs.close();
}

void KMeans::OutputClassVector() {
    ofstream ofs (cluster_dir.c_str());
    if (!ofs.is_open()) {
        cout << "NO OUTPUT FILE" << endl;
        return;
    }

    for (unsigned int i = 0; i < ClassesCenter.size(); i++) {
        for (map<int, int>::iterator mapIter = ClassMap.begin(); mapIter != ClassMap.end(); mapIter++) {
            if (mapIter -> second == (int) i) {
                for (unsigned int j = 0; j < AllVectors[mapIter->first].size(); j++) {
                    ofs << AllVectors[mapIter->first][j] << " ";
                }
                ofs << endl;
            }
        }
        ofs << endl;
    }

    ofs.close();
}

void KMeans::Analyse() {
    for (unsigned int i = 0; i < ClassesCenter.size(); i++) {
        int Iris_setosa = 0;
        int Iris_versicolor = 0;
        int Iris_virginica = 0;

        for (map<int, int>::iterator mapIter = ClassMap.begin(); mapIter != ClassMap.end(); mapIter++) {
            if (mapIter->second == (int) i) {
                map <int, string>::iterator TagIter = Tag.find(mapIter->first);
                if (TagIter->second == "Iris-setosa") {
                    Iris_setosa++;
                } else if (TagIter->second == "Iris-versicolor") {
                    Iris_versicolor++;
                } else if (TagIter->second == "Iris-virginica") {
                    Iris_virginica++;
                }
            }
        }
        cout << "Iris-setosa: " << Iris_setosa << " Iris-versicolor: " << Iris_versicolor << " Iris-virginica: " << Iris_virginica << endl;
    }
}