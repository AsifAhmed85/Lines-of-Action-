import { getOpposition } from "./boardUtils";
import Queue from '@datastructures-js/queue';

const isValidPosition = (boardSize, row, col) => {
  return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
}

const getNeighbors = (board, row, col) => {
  let neighbors = [];
  let myType = board[row][col].type;

  let testPositions = [
    {row, col: col+1}, {row, col: col-1}, {row: row+1, col},
    {row: row-1, col}, {row: row+1, col: col+1}, {row: row+1, col: col-1},
    {row: row-1, col: col+1}, {row: row-1, col: col-1}
  ]

  for(const position of testPositions){
    if(isValidPosition(board.length, position.row, position.col) && 
      board[position.row][position.col].type === myType){
        neighbors.push(position);
      }
  }
  return neighbors;
}

const getIndex = (boardSize, position) => boardSize * (position.row) + position.col


const bfs = (board, startPosition) => {
  const queue = new Queue();
  let visited = new Set();
  queue.enqueue(startPosition);
  visited.add(getIndex(board.length, startPosition));

  while(!queue.isEmpty()){
    let curr = queue.dequeue();
    for(const neighbor of getNeighbors(board, curr.row, curr.col)){
      let indx = getIndex(board.length, neighbor);
      if(!visited.has(indx)){
        queue.enqueue(neighbor);
        visited.add(getIndex(board.length, neighbor))
      }
    }
  }
  return visited.size;
}

const isEqualPosition = (a, b) => a.row === b.row && a.col === b.col;

const getAPosition = (board, type) => {
  for(let i = 0; i < board.length; i++){
    for(let j = 0; j < board.length; j++){
      if(board[i][j].type === type) return ({
        row: i,
        col: j
      })
    }
  }
  return null
}

export const getWinner = (board, lastMoveByCurrent, lastMoveOpposition, currentCells, oppositionCells) => {


  let currentType = board[lastMoveByCurrent.row][lastMoveByCurrent.col].type;
  let oppositionType = getOpposition(currentType);

  if(oppositionCells === 0) return currentType;
  if(bfs(board, lastMoveByCurrent) === currentCells) return currentType;

  let oppositionPosition = lastMoveOpposition;
  if(isEqualPosition(lastMoveByCurrent, lastMoveOpposition)){
    oppositionPosition = getAPosition(oppositionType);
  }

  if(!oppositionPosition) return currentType;

  if(bfs(board, oppositionPosition) === oppositionCells) return oppositionType;

  return null;

}