// CoordinateSystem.cpp

#include "CoordinateSystem.h"
#include <QDebug>

CoordinateSystem::CoordinateSystem(QObject *parent) : QObject(parent) {
    nw = new NeuralNetwork();
}

QVector<QPoint> CoordinateSystem::clickedPoints() const {
    return m_clickedPoints;
}

void CoordinateSystem::setClickedPoints(const QVector<QPoint> &points) {
    if (m_clickedPoints != points) {
        m_clickedPoints = points;
        emit clickedPointsChanged();
        for (const QPoint &point : m_clickedPoints) {
            qDebug() << "X:" << point.x() << "Y:" << point.y();
        }
    }
}
