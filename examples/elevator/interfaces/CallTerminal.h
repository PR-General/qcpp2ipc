#include <QObject>

#ifdef  ELEVATOR_SYSTEM
#define SYS_CALL    ASYNC_OUT
#define CLIENT_CALL ASYNC_IN
#define OMNI_CALL   ASYNC_INOUT
#else
#define SYS_CALL    ASYNC_IN
#define CLIENT_CALL ASYNC_OUT
#define OMNI_CALL   ASYNC_INOUT
#endif
#include "../../../src/include/known_keywords.h"

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
    CLIENT_CALL void requestUpCall(){}
    CLIENT_CALL void requestDownCall(){}

    // set the internal variable state for connection status (to elevator system)
    SYS_CALL void setSystemConnection(bool connected){Q_UNUSED(connected);}

protected slots: // Elevator system notifies when to clear request
    SYS_CALL void clearRequest(){}
    SYS_CALL quint32 testFunction(){return 2;}

}; // End CALL_TERMINAL_H
