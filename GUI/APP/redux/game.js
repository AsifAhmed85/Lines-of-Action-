import * as ActionTypes from './actiontypes';

const Game = (state = {
  firstPlayerName: '',
  secondPlayerName: '',
  firstPlayerType: '',
  secondPlayerType: '',
  totalTimeTaken: null,
  subProcess1: null,
  subProcess2: null,
  hasBot1Move: false,
  hasBot2Move: false,
  winner: ''
}, action) => {
  switch(action.type){
    case ActionTypes.SET_PLAYER_NAMES:
      return {
        ...state,
        firstPlayerName: action.firstPlayerName,
        secondPlayerName: action.secondPlayerName,
        firstPlayerType: action.firstPlayerType,
        secondPlayerType: action.secondPlayerType,
        subProcess1: action.subProcess1,
        subProcess2: action.subProcess2,
        hasBot1Move: false,
        hasBot2Move: false,
        winner: '',
        totalTimeTaken: null
      }
    
    case ActionTypes.CHANGE_HAS_BOT_MOVE:
      return {
        ...state,
        [action.botType]: !state[action.botType]
      }
    case ActionTypes.SET_TOTAL_TIME:
      return {
        ...state,
        totalTimeTaken: action.payload
      }

    case ActionTypes.FINISH_GAME:
      if(state.subProcess1){
        state.subProcess1.kill();
      }
      if(state.subProcess2){
        state.subProcess2.kill();
      }
      return {
        ...state,
        totalTimeTaken: action.totalTimeTaken,
        winner: action.winner,
        hasBot1Move: false,
        hasBot2Move: false,
      }
    default:
      return state;
  }
}

export default Game;