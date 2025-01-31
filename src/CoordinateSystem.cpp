// CoordinateSystem.cpp

#include "CoordinateSystem.h"
#include <QDebug>

CoordinateSystem::CoordinateSystem(QObject *parent) : QObject(parent) {

}

QVariantList CoordinateSystem::clickedPoints() const {
    return m_clickedPoints;
}

int CoordinateSystem::epocSize() const {
    return _epoc_size;
}

double CoordinateSystem::learningRate() const {
    return _learning_rate;
}

void CoordinateSystem::setClickedPoints(const QVariantList &points) {
    if (m_clickedPoints != points) {
        m_clickedPoints = points;
        emit clickedPointsChanged();
    }
}

void CoordinateSystem::setEpocSize(int &epoc) {
    if (_epoc_size != epoc) {
        _epoc_size = epoc;
        emit epocSizeChanged();

    }
}

void CoordinateSystem::setLearningRate(double &lrate) {
    if (_learning_rate != lrate) {
        _learning_rate = lrate;
        emit learningRateChanged();
    }
}


void CoordinateSystem::training() {

    nw = new NeuralNetwork(this, m_clickedPoints, epocSize(), learningRate());
    qDebug() << "_learning_rate:" << _learning_rate;
    qDebug() << "_epoc_size:" << _epoc_size;

    for (const QVariant &point : m_clickedPoints) {
        QVariantMap pointMap = point.toMap();
        qDebug() << "x:" << pointMap["x"].toFloat() << " y:" << pointMap["y"].toFloat() << " class:" << pointMap["color"].toString();
    }

    nw->init_weight();
    nw->update_wights_and_bias();

}

QVariantList CoordinateSystem::getArray() {
    double w1   = nw->getW1();
    double w2   = nw->getW2();
    double bias = nw->getBias();

    qDebug() << "Weights and bias: w1 =" << w1 << ", w2 =" << w2 << ", b =" << bias;

    for (int i = -320; i <= 320; i += 1) {  // Step size increased for efficiency
        double x = i;
        
        // Corrected equation
        double y = (-(w1 * x) - bias) / w2;
        // double y = (-1 * (w1 * x + bias)) / w2;

        // Denormalize y before adding to the list

        qDebug() << " (-(w1 * x) - 100) / w2 -> " << w1 << ", " << x << ", " << bias << ", " << w2;
        QVariantList rowList;
        rowList.append(x);
        rowList.append(y);
        rowList.append(5);
        line_points.append(rowList);

    }
    return line_points;
}
