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

    Q_INVOKABLE void training();
    
    QVariantList clickedPoints() const;
    int epocSize() const;
    double learningRate() const;

    void setClickedPoints(const QVariantList &points);
    void setEpocSize(int &epoc);
    void setLearningRate(double &lrate);

signals:
    void clickedPointsChanged();
    void epocSizeChanged();
    void learningRateChanged();
    void trainingChanged();

private:
    QVariantList m_clickedPoints;
    NeuralNetwork *nw;
    int _epoc_size = -1;
    double _learning_rate = -1.0;

};

#endif // COORDINATESYSTEM_H
