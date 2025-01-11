#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include "QPoint"
#include <QVariant>
#include <QVector>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <cstring>

class NeuralNetwork : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(QVector<QVector<double>> array READ getArray NOTIFY arrayChanged)

    public:
        explicit NeuralNetwork(QObject *parent = nullptr, QVariantList clicked_points = QVariantList(), int _epoch = -1, double _learning_rate = -1.0);
        void shuffle(int *array, int n);

        void init_weight();
        void update_wights_and_bias();

        // Q_INVOKABLE QVariantList getArray();

        // Define sigmoid. Range is between [0,1]
        double sigmoid(double x);
        // Derivate of sigmoid/ Calculate error during backpropagation
        double dSigmoid(double x);
        double dSigmoid2(double y);
        // Generate random between 0-1 for weights
        double generate_random();
        int sign_square(double x);
        double denormalize(double normalized_value, double min_val, double max_val);

        double normalizeDataY(double data);
        double normalizeDataX(double data);

        double getW1() { return weights1; }
        double getW2() { return weights2; }
        double getBias() { return bias; }

    private:
        int num_inputs;             // Count of noron in the input layer
        int num_hidden_nodes;       // Count of noron in the hidden layer
        int num_outputs;            // Count of noron in the output layer
        int num_training_sets;      // Count of training sets
        int num_neuron;             // Count of neuron in the system

        double lr;     // Learning rate, step size in the weight updates
        double *hidden_layer;       // Keep activation result in the hidden layer
        double *output_layer;       // Keep activation result in the output layer
        double *single_layer;       // Keep activation result in the single layer

        double *hidden_layer_bias;  // Keep bias result in the hidden layer
        double *output_layer_bias;  // Keep bias result in the output layer
        double *single_neuron_bias; // Keep bias result in the single layer

        // output-hidden, hidden-output layers wights
        double **hidden_weights;
        double **output_weights;
        double **single_neuron_weights;

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

        // line equation
        double x1, x2, w1, w2, w3, w4, w5, w6, b1, b2, b3 = 0.0;
        double up_x;
        double up_y;
        double down_x;
        double down_y;

        double left_x;
        double left_y;
        double right_x;
        double right_y;

        // double line_equation = ((x1*w1 + x2*w3 + b1) * w5) + ((x1*w2 + x2*w4 + b2) * w6) + b3;
        // QVariantList line_points;

        double weights1;
        double weights2;
        double bias;

};

#endif // NEURALNETWORK_H
