#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QTimer>
#include <QList>


class StateMachine : public QObject
{
    Q_OBJECT
public:
    explicit StateMachine(QObject *parent = nullptr);
    enum InEvent {
        InEvent1,
        InEvent2,
    } ;
    enum State {
        Transitioning,
        State1,
        State2,
    };
    enum OutEvent {
        OutEvent1,
        OutEvent2,
    };

    Q_ENUM(InEvent)
    Q_ENUM(OutEvent)
    Q_ENUM(State)
    Q_PROPERTY(StateMachine::State state READ state NOTIFY stateChanged)
    StateMachine::State state() const;

    Q_INVOKABLE bool trigger(StateMachine::InEvent event);


private:
    bool stateMachineLoop();
    bool _processEventStack();
    bool _do();
    bool _state1Do();
    bool _state1Entry();
    bool _state1Exit();
    bool _state2Do();
    bool _state2Entry();
    bool _state2Exit();

    bool _action1();
    bool _action2();

signals:
    void eventOutput(StateMachine::OutEvent outEvent);
    void stateChanged();

private:
    StateMachine::State m_state = State1;
    QTimer *m_pInEventDequeueTimer = nullptr;
    QList<InEvent> m_inEventStack;
};

#endif // STATEMACHINE_H
