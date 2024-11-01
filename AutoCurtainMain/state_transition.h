// state_transition.h
#ifndef STATE_TRANSITION_H
#define STATE_TRANSITION_H

// DEFINE STATE ENUM
enum STATE {IDLE, OPENING, OPEN, CLOSING, CLOSED, ERROR};

// Declare the function that transitions between states
STATE getNextState(STATE current_state);

#endif