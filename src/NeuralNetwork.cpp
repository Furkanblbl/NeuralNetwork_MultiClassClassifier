#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(QObject *parent, QVariantList clicked_points, int _epoch, double _learning_rate) : QObject(parent), m_clickedPoints(clicked_points), num_of_epochs(_epoch), lr(_learning_rate) {

    num_inputs = 2;
    num_hidden_nodes = 2;
    num_outputs = 1;
    num_neuron = 1;
    num_training_sets = m_clickedPoints.size();

    hidden_layer = new double[num_hidden_nodes];
    output_layer = new double[num_outputs];
    single_layer = new double[num_neuron];

    hidden_layer_bias = new double[num_hidden_nodes];
    output_layer_bias = new double[num_outputs];
    single_neuron_bias = new double[num_neuron];

    hidden_weights = new double*[num_inputs];
    for (int i = 0; i < num_inputs; i++) {
        hidden_weights[i] = new double[num_hidden_nodes];
    }
    output_weights = new double*[num_hidden_nodes];
    for (int i = 0; i < num_inputs; i++) {
        output_weights[i] = new double[num_outputs];
    }
    single_neuron_weights = new double*[num_inputs];
    for (int i = 0; i < num_inputs; i++) {
        single_neuron_weights[i] = new double[num_neuron];
    }

    // Neural network inputs so, coordinates and labels
    training_inputs = new double*[num_training_sets];
    for (int i = 0; i < num_training_sets; i++) {
        training_inputs[i] = new double[num_inputs];
    }

    training_outputs = new double*[num_training_sets];
    for (int i = 0; i < num_training_sets; i++) {
        training_outputs[i] = new double[num_outputs];
    }

    // Veri giriş işlemi
    for (int i = 0; i < m_clickedPoints.size(); i++) {
        QVariantMap pointMap = m_clickedPoints[i].toMap();

        training_inputs[i][0] = pointMap["x"].toFloat();
        training_inputs[i][1] = pointMap["y"].toFloat();
        training_outputs[i][0] = pointMap["color"].toFloat();

        qDebug() << "Check x:" << pointMap["x"].toDouble() 
                << pointMap["y"].toDouble() 
                << pointMap["color"].toDouble() << "\n";
    }
    training_set_order = new int[num_training_sets];
    for (int i = 0; i < num_training_sets; i++) {
        training_set_order[i] = i;
    }

    init_weight();
    update_wights_and_bias();
    qDebug() << "num_of_epochs: " << num_of_epochs << "\n";
    qDebug() << "lr: " << lr << "\n";

    for (int i = 0; i < num_training_sets; i++) {
        qDebug() << "lr: " << training_set_order[i]  << "\n";
    }
}

/**
 * Computes the sigmoid of the given input value.
 * The sigmoid function maps any real-valued number into the range (0, 1).
 * It is commonly used in machine learning models such as neural networks to introduce non-linearity.
 
 * @param x The input value to be processed by the sigmoid function.
 * @return The sigmoid value in the range (0, 1).
*/
double NeuralNetwork::sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

int NeuralNetwork::sign_square(double x) {
    return (x < 0) ? -1 : 1;
}

/**
 * Computes the derivative of the sigmoid function.
 * 
 * The derivative of the sigmoid function is used during backpropagation in neural networks
 * to calculate the error gradient and update weights during training.
 * The derivative of sigmoid(x) is sigmoid(x) * (1 - sigmoid(x)).
 * 
 * @param x The output value of the sigmoid function, which should lie between 0 and 1.
 * @return The derivative of the sigmoid function, calculated as: x * (1 - x).
 */
double NeuralNetwork::dSigmoid(double x) {
    return x * (1 - x);
}

/**
 * Generates a random number between 0.0 and 1.0.
 * 
 * This function uses the standard library's rand() function to generate a random number,
 * which is then scaled to the range [0.0, 1.0] by dividing by RAND_MAX.
 * It is commonly used for generating random values such as initial weights for neural networks.
 * 
 * @return A random number in the range [0.0, 1.0].
 *         The result is obtained by dividing the output of rand() by RAND_MAX.
 */
double NeuralNetwork::generate_random() {
    return ((double)rand()) / ((double)RAND_MAX);
}

/**
 * Shuffles the elements of an integer array in place using the Fisher-Yates algorithm.
 * 
 * The Fisher-Yates shuffle algorithm (also known as the Knuth shuffle) randomly permutes
 * the elements of the array, ensuring that each possible permutation of the array is equally
 * likely to occur. This is commonly used to shuffle training data in machine learning models
 * to improve the training process by reducing bias.
 * 
 * @param array Pointer to the array to be shuffled.
 * @param n The number of elements in the array to be shuffled.
 *          The array should contain at least 2 elements for the shuffle to be meaningful.
 */
void NeuralNetwork::shuffle(int* array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            // Random index between i and n-1
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            
            // Swap elements at index i and j
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

/**
 * Init wights as random.
 */
void NeuralNetwork::init_weight() {
    // Gizli katmanların ağırlık ataması
    for (int i = 0; i < num_inputs; i++) {
        for (int j = 0; j < num_hidden_nodes; j++) {
            hidden_weights[i][j] = generate_random();
        }
    }

    for (int i = 0; i < num_hidden_nodes; i++) {
        for (int j = 0; j < num_outputs; j++) {
            output_weights[i][j] = generate_random();
        }
    }

    for (int i = 0; i < num_inputs; i++) {
        for (int j = 0; j < num_neuron; j++) {
            single_neuron_weights[i][j] = generate_random();
        }
    }

    for (int i = 0; i < num_outputs; i++) {
        output_layer_bias[i] = generate_random();
    }

    for (int i = 0; i < num_outputs; i++) {
        hidden_layer_bias[i] = generate_random();
    }
}

/**
 * todo: write function definations
 */
void NeuralNetwork::update_wights_and_bias() {
    // Train the neural network for a number of epochs
    for (int epoch = 0; epoch < num_of_epochs; epoch++) {
        shuffle(training_set_order, num_training_sets);

        for (int x = 0; x < num_training_sets; x++) {
            // Forward pass
            related_data = training_set_order[x];

            // Compute hidden layer activation
            // for (int j = 0; j < num_hidden_nodes; j++) {
            //     double activation = hidden_layer_bias[j];
            //     for (int k = 0; k < num_inputs; k++) {
            //         activation += training_inputs[related_data][k] * hidden_weights[k][j];
            //     }
            //     hidden_layer[j] = sigmoid(activation);
            // }
            for(int j = 0; j < num_neuron; j++) {
                double activation = single_neuron_bias[j];
                for (int k = 0; k < num_inputs; k++) {
                    activation += training_inputs[related_data][k] * single_neuron_weights[k][j];
                }
                single_layer[j] = sign_square(activation);
            }

            // Compute output layer activation
            // for (int j = 0; j < num_outputs; j++) {
            //     double activation = output_layer_bias[j];
            //     for (int k = 0; k < num_hidden_nodes; k++) {
            //         activation += hidden_layer[k] * output_weights[k][j];
            //     }
            //     output_layer[j] = sigmoid(activation);
            // }

            printf("Input: %g  %g Output: %g    Excepted Output: %g \n",
                    training_inputs[related_data][0],
                    training_inputs[related_data][1],
                    single_layer[0],
                    training_outputs[related_data][0]
                );

            // Backpropogation
            // Compute change in output weights
            // double deltaOutput[num_outputs];

            // for (int j = 0; j < num_outputs; j++) {
            //     double error = (training_outputs[related_data][j] - output_layer[j]);
            //     deltaOutput[j] = error * dSigmoid(output_layer[j]);
            //     if (deltaOutput[j] < 0.01) {
            //         break;
            //     }
            // }

            double delta_single_output[num_neuron];
            for(int j = 0; j < num_neuron; j++) {
                double error = (training_outputs[related_data][j] - single_layer[j]);
                delta_single_output[j] = error * dSigmoid(single_layer[j]);
            }

            // Compute change in hidden weights
            // double deltaHidden[num_hidden_nodes];
            // for (int j = 0; j < num_hidden_nodes; j++) {
            //     double error = 0.0f;
            //     for (int k = 0; k < num_outputs; k++) {
            //         error += deltaOutput[k] * output_weights[j][k];
            //     }
            //     deltaHidden[j] = error * dSigmoid(hidden_layer[j]);
            // }

            // Apply change in output weights
            // for (int j = 0; j < num_outputs; j++) {
            //     output_layer_bias[j] += deltaOutput[j] * lr;
            //     for (int k = 0; k < num_hidden_nodes; k++) {
            //         output_weights[k][j] += hidden_layer[k] * deltaOutput[j] * lr;
            //     }
            // }

            for (int j = 0; j < num_neuron; j++) {
                single_neuron_bias[j] += delta_single_output[j] * lr;
                for (int k = 0; k < num_inputs; k++) {
                    single_neuron_weights[k][j] += single_layer[k] * delta_single_output[j] * lr;
                }
            }

            // Apply change in hidden weights
            // for (int j = 0; j < num_hidden_nodes; j++) {
            //     hidden_layer_bias[j] += deltaHidden[j] * lr;
            //     for (int k = 0; k < num_inputs; k++) {
            //         hidden_weights[k][j] += training_inputs[related_data][k] * deltaHidden[j] * lr;
            //     }
            // }

        }

    }



    fputs("\n Final Hidden Weights\n[ ", stdout);
    for (int j = 0; j < num_hidden_nodes; j++) {
        fputs("[ ", stdout);
        for (int k = 0; k < num_inputs; k++) {
            printf("%f ", hidden_weights[k][j]);
        }
        fputs("] \n", stdout);
    }

    fputs("]\n Final Hidden Biases\n[ ", stdout);
    for (int j = 0; j < num_hidden_nodes; j++) {
        printf("%f ", hidden_layer_bias[j]);
    }

    // Print Final weights after done training
    fputs("]\n Final Output Weights\n[ ", stdout);
    for (int j = 0; j < num_outputs; j++) {
        fputs("[ ", stdout);
        for (int k = 0; k < num_hidden_nodes; k++) {
            printf("%f ", output_weights[k][j]);
        }
        fputs("] \n", stdout);
    }

    fputs("]\n Final Output Biases\n[ ", stdout);
    for (int j = 0; j < num_outputs; j++) {
        printf("%f ", output_layer_bias[j]);
    }
}
