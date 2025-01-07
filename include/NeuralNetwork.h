#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "QPoint"
#include <QVariant>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <cstring>

class NeuralNetwork : public QObject
{
    Q_OBJECT

    public:
        explicit NeuralNetwork(QObject *parent = nullptr, QVariantList clicked_points = QVariantList(), int _epoch = -1, double _learning_rate = -1.0);
        void shuffle(int* array, size_t n);
        void init_weight();
        void update_wights_and_bias();

        // Define sigmoid. Range is between [0,1]
        double sigmoid(double x);
        // Derivate of sigmoid/ Calculate error during backpropagation
        double dSigmoid(double x);
        // Generate random between 0-1 for weights
        double generate_random();

    private:
        int num_inputs;             // Count of noron in the input layer
        int num_hidden_nodes;       // Count of noron in the hidden layer
        int num_outputs;            // Count of noron in the output layer
        int num_training_sets;      // Count of training sets

        double lr;     // Learning rate, step size in the weight updates
        double *hidden_layer;       // Keep activation result in the hidden layer
        double *output_layer;       // Keep activation result in the output layer

        double *hidden_layer_bias;  // Keep bias result in the hidden layer
        double *output_layer_bias;  // Keep bias result in the output layer

        // output-hidden, hidden-output layers wights
        double **hidden_weights;
        double **output_weights;

        // Training sets index. Every epocs compare that array and choose different order
        int *training_set_order;
        // Network learning repeat count
        int num_of_epochs;

        // Forward pass
        int related_data = -1;

        // Neural network inputs
        double **training_inputs;
        double **training_outputs;

        // clicked_points data
        QVariantList m_clickedPoints;
};

#endif // NEURALNETWORK_H
