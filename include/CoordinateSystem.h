// CoordinateSystem.h

#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QObject>
#include <QVector>
#include "QPoint"

#include "NeuralNetwork.h"

class CoordinateSystem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<QPoint> clickedPoints READ clickedPoints WRITE setClickedPoints NOTIFY clickedPointsChanged)

public:
    explicit CoordinateSystem(QObject *parent = nullptr);
    
    QVector<QPoint> clickedPoints() const;
    void setClickedPoints(const QVector<QPoint> &points);  // Setter function

signals:
    void clickedPointsChanged();

private:
    QVector<QPoint> m_clickedPoints;  // Store the clicked points
    NeuralNetwork *nw;

};

#endif // COORDINATESYSTEM_H
