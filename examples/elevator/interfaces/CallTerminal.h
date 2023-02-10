#include <QObject>

class CallTerminal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 state READ state NOTIFY stateChanged)
    // Scriptable false will notify the IPC generator to ignore this property and its signals (remains local)
    Q_PROPERTY(bool systemConnection READ systemConnection NOTIFY systemConnectionChanged SCRIPTABLE false)
public:
    // Valid States
    enum CallTerminalStates{
        CLEAR = 0,
        UP = 2,
        DOWN = 4
    };
    CallTerminal(QObject* parent = nullptr){}
    virtual ~CallTerminal(){}
    virtual bool    systemConnection(){ return false; }
    virtual quint32 state() { return CallTerminalStates::CLEAR; }

signals:
    // notify systems monitoring state that the elevator floor state changed
    void stateChanged(quint32);
    void systemConnectionChanged(bool);

public slots: // user called request methods
    virtual void requestUpCall(){}
    virtual void requestDownCall(){}

    // set the internal variable state for connection status (to elevator system)
    void setSystemConnection(bool connected){Q_UNUSED(connected);}

protected slots: // Elevator system notifies when to clear request
    virtual void clearRequest(){}

}; // End CALL_TERMINAL_H
