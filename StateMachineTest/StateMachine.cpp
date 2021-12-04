#include "StateMachine.h"
#include <QDebug>

StateMachine::StateMachine(QObject *parent) : QObject(parent)
{
    qDebug() << __func__;
    m_pInEventDequeueTimer = new(std::nothrow) QTimer(this);
    m_pInEventDequeueTimer->setInterval(1000);
    connect(m_pInEventDequeueTimer, &QTimer::timeout, this, [=]() {
        this->stateMachineLoop();
    });
    m_pInEventDequeueTimer->start();
}

bool StateMachine::trigger(StateMachine::InEvent event)
{
    qDebug() << __func__;
    m_inEventStack.append(event);
    return true;
}

bool StateMachine::stateMachineLoop()
{
    this->_processEventStack();
    this->_do();
    m_pInEventDequeueTimer->start();
    return true;
}

bool StateMachine::_do()
{
    qDebug() << __func__;
    switch(m_state) {
    case StateMachine::State::State1:
        _state1Do();
        return true;
        // 例外到達
        break;

    case StateMachine::State::State2:
        _state2Do();
        return true;
        break;

    default:
        // 処理するイベントなし.
        return false;
        break;
    }
}

bool StateMachine::_processEventStack()
{
    qDebug() << __func__;
    if (m_inEventStack.isEmpty()) {
        // 処理するイベントなし.

        return false;
    } else {
        // 遷移処理を行う.
        StateMachine::InEvent inEvent = m_inEventStack.first();
        m_inEventStack.removeFirst();

        switch(m_state) {
        case StateMachine::State::State1:
            // STATE 1 >>>>
            switch(inEvent) {
            case StateMachine::InEvent::InEvent1:
                // STATE 1, INEVENT 1 >>>>
                _state1Exit();

                // StateChange to Transitioning State2.
                m_state = StateMachine::State::Transitioning;
                emit stateChanged();

                _action1();

                // StateChange to State2.
                m_state = StateMachine::State::State2;
                emit stateChanged();

                _state2Entry();
                // STATE 1, INEVENT 1 <<<<
                break;

            case StateMachine::InEvent::InEvent2:
                // STATE 1, INEVENT 2 >>>>
                // STATE 1, INEVENT 2 <<<<
                break;

            default:
                // 処理するイベントなし.
                break;
            }
            break;
            // STATE 1 <<<<

        case StateMachine::State::State2:
            // STATE 2 >>>>
            switch(inEvent) {
            case StateMachine::InEvent::InEvent1:
                // STATE 2, INEVENT 1 >>>>
                // STATE 2, INEVENT 1 <<<<
                break;
            case StateMachine::InEvent::InEvent2:
                // STATE 2, INEVENT 2 >>>>
                _state2Exit();

                // StateChange to Transitioning State2.
                m_state = StateMachine::State::Transitioning;
                emit stateChanged();

                _action2();

                // StateChange to State2.
                m_state = StateMachine::State::State1;
                emit stateChanged();

                _state1Entry();
                // STATE 2, INEVENT 2 <<<<
                break;

            default:
                // 処理するイベントなし.
                break;
            }
            // STATE 2 <<<<
            break;
            
        default:
            // 処理するイベントなし.
            break;
        }
    }
    return true;
}

bool StateMachine::_state1Do()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_state1Entry()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_state1Exit()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_state2Do()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_state2Entry()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_state2Exit()
{
    qDebug() << __func__;
    return true;
}

bool StateMachine::_action1()
{
    qDebug() << __func__;
    emit eventOutput(StateMachine::OutEvent::OutEvent1);
    return true;
}

bool StateMachine::_action2()
{
    qDebug() << __func__;
    emit eventOutput(StateMachine::OutEvent::OutEvent2);
    return true;
}
