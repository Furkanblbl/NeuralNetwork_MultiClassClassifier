// CoordinateSystem.cpp

#include "CoordinateSystem.h"
#include <QDebug>

CoordinateSystem::CoordinateSystem(QObject *parent) : QObject(parent) {
    nw = new NeuralNetwork();
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
        for (const QVariant &point : m_clickedPoints) {
            QVariantMap pointMap = point.toMap();
            qDebug() << "x:" << pointMap["x"].toFloat() << " y:" << pointMap["y"].toFloat() << " class:" << pointMap["color"].toString();
        }
    }
}

void CoordinateSystem::setEpocSize(int &epoc) {
    if (_epoc_size != epoc) {
        _epoc_size = epoc;
        emit epocSizeChanged();
        qDebug() << "_epoc_size:" << _epoc_size;

    }
}

void CoordinateSystem::setLearningRate(double &lrate) {
    if (_learning_rate != lrate) {
        _learning_rate = lrate;
        emit learningRateChanged();
        qDebug() << "_learning_rate:" << _learning_rate;
    }
}
