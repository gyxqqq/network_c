#include <fstream>
#include <iostream>
#include <string>
#include "../Eigen/Eigen"
#include <list>
using namespace std;
using namespace Eigen;
class network
{
    list<MatrixXd> weights;
    list<MatrixXd> biases;
    int num_layers;
    int *sizes;

public:
    network(int *sizes, int num_layers)
    {
        this->num_layers = num_layers;
        this->sizes = new int[num_layers];
        memcpy(this->sizes, sizes, num_layers * sizeof(int));
        for (int i = 1; i < num_layers; i++)
        {
            weights.push_back(MatrixXd::Random(sizes[i], sizes[i - 1]));
            biases.push_back(MatrixXd::Random(sizes[i], 1));
        }
    }
    MatrixXd feedforward(MatrixXd a)
    {
        for (int i = 0; i < num_layers - 1; i++)
        {
            a = a * weights.front().unaryExpr([](double x)
                                              { return 1 / (1 + exp(-x)); }) +
                biases.front(); // sigmoid activation function
            weights.pop_front();
            biases.pop_front();
        }
        return a;
    }
    void save()
    { // save the network to a file
        cout << "Saving network..." << endl;
        ofstream out = ofstream("network.txt");
        out << num_layers << endl;
        for (int i = 0; i < num_layers; i++)
        {
            out << sizes[i] << " "; // write the sizes of the layers
        }
        out << endl;
        for (int i = 0; i < num_layers - 1; i++)
        {
            out << weights.front() << endl;
            out << biases.front() << endl;
            weights.pop_front();
            biases.pop_front();
        }
        cout << "Network saved to network.txt" << endl;
    }
    void sgd(MatrixXd training_data, int epochs, int mini_batch_size, double eta)
    {
        for (int i = 0; i < epochs; i++)
        {
            for (int j = 0; j < training_data.rows(); j += mini_batch_size)
            {
                MatrixXd mini_batch = training_data.block(j, 0, mini_batch_size, training_data.cols());
                update_mini_batch(mini_batch, eta);
            }
        }
    }
};