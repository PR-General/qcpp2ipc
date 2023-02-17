#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QList>
class ElevatorCar;
class ElevatorMotor;
class ElevatorFloor;
class ElevatorSystem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ElevatorMotor* motorController  READ motorController CONSTANT)
    Q_PROPERTY(ElevatorCar* carController  READ carController CONSTANT)
    Q_PROPERTY(quint32 state READ state NOTIFY stateChanged)
    Q_PROPERTY(qreal currentPosition READ currentPosition NOTIFY currentPositonChanged)
    Q_PROPERTY(quint32 targetState READ targetState NOTIFY targetStateChanged)
    Q_PROPERTY(qreal targetPosition READ targetPosition NOTIFY targetPositionChanged)
    Q_PROPERTY(quint32 floorCount  READ floorCount CONSTANT)
    Q_PROPERTY(quint32 restingFloor  READ restingFloor CONSTANT)
    Q_PROPERTY(QList< ElevatorFloor* > floors  READ floors CONSTANT)

public:
    explicit ElevatorSystem(QObject *parent = nullptr);
    ~ElevatorSystem();
    // ...

};

#endif // ELEVATOR_SYSTEM_H
