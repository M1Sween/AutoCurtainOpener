// state_transition.cpp

#include "state_transition.cpp"

// Function to determine the next state based on current state and conditions
STATE getNextState(STATE current_state){
  STATE next_state;
  
  // *** STATE TRANSITIONS *** 
  switch (current_state) {
    case IDLE:
      if (open_cmd) {
        next_state = OPENING;
      }
      else if (close_cmd) {
        next_state = CLOSING;
      }
      else if (LS == 1) {
        next_state = ERROR; // if LS is open, can't know if fully opened or closed
      }
      else {
        next_state = IDLE;
      }
      break;
    
    case OPENING:
      if (LS == 1) {
        next_state = OPEN;
      }
      else if (open_close_time_out){
        next_state = ERROR;
      }
      break;

    case OPEN:
      if (close_cmd){
        next_state = CLOSING;
      } 
    break;

    case CLOSING:
      if (LS == 1) {
        next_state = CLOSED;
        }
      else if (open_close_time_out){
        next_state = ERROR;
        }
    break;

    case CLOSED:
      if (open_cmd){
        next_state = OPENING;
      } 
    break;

    case ERROR:  
    break;

  }
  return next_state
}