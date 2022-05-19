export const createBoard = (boardSize) => {
  let board = [];
  for (let i = 0; i < boardSize; i++) {
    board[i] = [];
    for (let j = 0; j < boardSize; j++) {
      if ((i === 0 || i === boardSize - 1) && j !== 0 && j !== boardSize - 1) {
        board[i][j] = {
          type: 'black'
        }
      } else if ((j === 0 || j === boardSize - 1) && i !== 0 && i !== boardSize - 1) {
        board[i][j] = {
          type: 'white'
        }
      } else {
        board[i][j] = {
          type: 'empty'
        }
      }
    }
  }
  return board;
}


export const getOpposition = (player) => {
  return player === 'black'? 'white': 'black';
}

const getFirstChar = (type) => {
  if(type === 'black') return 'b';
  if(type === 'white') return 'r';
  return 'e';
}

export const getBoardForBot = (board) => {
  let botBoard = '';
  for(let i = 0; i < board.length; i++){
    for(let j = 0; j < board.length; j++){
      botBoard += getFirstChar(board[i][j].type) + ' ';
    }
    botBoard += '\n';
  }
  return botBoard;
}