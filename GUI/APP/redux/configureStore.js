import thunk from 'redux-thunk';
import logger from 'redux-logger';
import { createStore, combineReducers, applyMiddleware } from 'redux';
import Board from './board';
import Game from './game';
import Timer from './timer';



const ConfigureStore = () => {
  const store = createStore(
    combineReducers({
    board: Board,
    game: Game,
    timer: Timer 
  }),
  applyMiddleware(thunk, logger)
  );

  return store;
}

export default ConfigureStore;