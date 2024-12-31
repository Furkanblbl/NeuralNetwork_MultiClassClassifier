// CoordinateSystem.h

#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QObject>
#include <QVector>
#include "QPoint"
#include <QVariant>

#include "NeuralNetwork.h"

class CoordinateSystem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList clickedPoints READ clickedPoints WRITE setClickedPoints NOTIFY clickedPointsChanged)
    Q_PROPERTY(int epocSize READ epocSize WRITE setEpocSize NOTIFY epocSizeChanged)
    Q_PROPERTY(double learningRate READ learningRate WRITE setLearningRate NOTIFY learningRateChanged)

public:
    explicit CoordinateSystem(QObject *parent = nullptr);
    
    QVariantList clickedPoints() const;
    int epocSize() const;
    double learningRate() const;

    void setClickedPoints(const QVariantList &points);  // Setter function
    void setEpocSize(int &epoc);
    void setLearningRate(double &lrate);

signals:
    void clickedPointsChanged();
    void epocSizeChanged();
    void learningRateChanged();

private:
    QVariantList m_clickedPoints;  // Store the clicked points
    NeuralNetwork *nw;
    int _epoc_size = -1;
    double _learning_rate = -1.0;

};

#endif // COORDINATESYSTEM_H
