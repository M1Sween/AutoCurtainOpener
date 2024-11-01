void setup() {
  // put your setup code here, to run once:
  enum STATE {IDLE, OPENING, OPEN, CLOSING, CLOSED, ERROR}; //
  STATE current_state = IDLE;

  // LIST OF VARIABLES

}



void loop() {
  // put your main code here, to run repeatedly:

  // *** STATE TRANSITIONS *** 
  switch (current_state) {
    case IDLE:
      if (open_cmd) {
        current_state = OPENING;
      }
      else if (close_cmd) {
        current_state = CLOSING;
      }
      else if (LS == 1) {
        current_state = ERROR; // if LS is open, can't know if fully opened or closed
      }
      else {
        current_state = IDLE;
      }
      break;
    
    case OPENING:
      if (LS == 1) {
        current_state = OPEN;
      }
      else if (open_close_time_out){
        current_state = ERROR;
      }
      break;

    case OPEN:
      if (close_cmd){
        current_state = CLOSING;
      } 
    break;

    case CLOSING:
      if (LS == 1) {
            current_state = CLOSED;
          }
          else if (open_close_time_out){
            current_state = ERROR;
          }
    break;

    case CLOSED:
      if (open_cmd){
        current_state = OPENING;
      } 
    break;

    case ERROR:
      
    break;

  }
}
