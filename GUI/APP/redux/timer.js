import * as ActionTypes from './actiontypes';

const Timer = (state = {
  startedAt: null,
  stoppedAt: null,
}, action) => {
  switch(action.type){
    case ActionTypes.START_TIMER:
      return {...state, 
        startedAt: action.now,
        stoppedAt: null  
      }
    case ActionTypes.STOP_TIMER:
      return {
        ...state,
        stoppedAt: action.now
      }
    case ActionTypes.RESET_TIMER:
      return {
        startedAt: null,
        stoppedAt: null
      }
    default:
      return state;
  }
}

export default Timer;