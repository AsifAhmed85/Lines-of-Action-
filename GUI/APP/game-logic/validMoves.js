const getTotalActiveCells = (board, row, col) => {

  let rowCount = 0, colCount = 0,
    leftDiagonalCount = 0, rightDiagonalCount = 0;

  for (const val of board[row]) {
    if (val.type !== 'empty') {
      rowCount += 1;
    }
  }

  for (let i = 0; i < board.length; i++) {
    if (board[i][col].type !== 'empty') {
      colCount += 1;
    }
  }

  for (let i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j].type !== 'empty') {
      leftDiagonalCount += 1;
    }
  }

  for (let i = row + 1, j = col + 1; i < board.length && j < board.length; i++, j++) {
    if (board[i][j].type !== 'empty') {
      leftDiagonalCount += 1;
    }
  }

  for (let i = row, j = col; i < board.length && j >= 0; i++, j--) {
    if (board[i][j].type !== 'empty') {
      rightDiagonalCount += 1;
    }
  }

  for (let i = row - 1, j = col + 1; i >= 0 && j < board.length; i--, j++) {
    if (board[i][j].type !== 'empty') {
      rightDiagonalCount += 1;
    }
  }

  return { rowCount, colCount, leftDiagonalCount, rightDiagonalCount }

}


export const getValidMoves = (row, col, board) => {
  let validMoves = []
  const myType = board[row][col].type;
  const oppositionType = myType === 'black' ? 'white' : 'black';
  let { rowCount, colCount, leftDiagonalCount, rightDiagonalCount } = getTotalActiveCells(board, row, col);

  let valDirection = {
    leftRow: true,
    rightRow: true,
    upCol: true,
    downCol: true,
    leftUpDiagonal: true,
    rightDownDiagonal: true,
    rightUpDiagonal: true,
    leftDownDiagonal: true
  }
  for (let i = 1; i <= rowCount - 1; i++) {
    if (col - i < 0 || board[row][col - i].type === oppositionType) {
      valDirection.leftRow = false;
    }

    if (col + i >= board.length || board[row][col + i].type === oppositionType) {
      valDirection.rightRow = false;
    }
  }
  if (col - rowCount < 0 || board[row][col - rowCount].type === myType) valDirection.leftRow = false;
  if (col + rowCount >= board.length || board[row][col + rowCount].type === myType) valDirection.rightRow = false;

  for (let i = 1; i <= colCount - 1; i++) {
    if (row - i < 0 || board[row - i][col].type === oppositionType) {
      valDirection.upCol = false;
    }

    if (row + i >= board.length || board[row + i][col].type === oppositionType) {
      valDirection.downCol = false;
    }
  }
  if (row - colCount < 0 || board[row - colCount][col].type === myType) valDirection.upCol = false;
  if (row + colCount >= board.length || board[row + colCount][col].type === myType) valDirection.downCol = false;

  for (let i = 1; i <= leftDiagonalCount - 1; i++) {
    if (row - i < 0 || col - i < 0 || board[row - i][col - i].type === oppositionType) {
      valDirection.leftUpDiagonal = false;
    }

    if (row + i >= board.length || col + i >= board.length || board[row + i][col + i].type === oppositionType) {
      valDirection.rightDownDiagonal = false;
    }
  }
  if (row - leftDiagonalCount < 0 || col - leftDiagonalCount < 0 || board[row - leftDiagonalCount][col - leftDiagonalCount].type === myType) valDirection.leftUpDiagonal = false;
  if (row + leftDiagonalCount >= board.length || col + leftDiagonalCount >= board.length || board[row + leftDiagonalCount][col + leftDiagonalCount].type === myType)
    valDirection.rightDownDiagonal = false;

  for (let i = 1; i <= rightDiagonalCount - 1; i++) {
    if (row + i >= board.length || col - i < 0 || board[row + i][col - i].type === oppositionType) {
      valDirection.leftDownDiagonal = false;
    }

    if (row - i < 0 || col + i >= board.length || board[row - i][col + i].type === oppositionType) {
      valDirection.rightUpDiagonal = false;
    }
  }
  if (row + rightDiagonalCount >= board.length || col - rightDiagonalCount < 0 || board[row + rightDiagonalCount][col - rightDiagonalCount].type === myType)
    valDirection.leftDownDiagonal = false;
  if (row - rightDiagonalCount < 0 || col + rightDiagonalCount >= board.length || board[row - rightDiagonalCount][col + rightDiagonalCount].type === myType)
    valDirection.rightUpDiagonal = false;


  if (valDirection.leftRow) validMoves.push({
    row,
    col: col - rowCount
  })
  if (valDirection.rightRow) validMoves.push({
    row,
    col: col + rowCount
  })
  if (valDirection.upCol) validMoves.push({
    row: row - colCount,
    col
  })
  if (valDirection.downCol) validMoves.push({
    row: row + colCount,
    col
  })
  if (valDirection.leftUpDiagonal) validMoves.push({
    row: row - leftDiagonalCount,
    col: col - leftDiagonalCount
  })
  if (valDirection.rightDownDiagonal) validMoves.push({
    row: row + leftDiagonalCount,
    col: col + leftDiagonalCount
  })
  if (valDirection.leftDownDiagonal) validMoves.push({
    row: row + rightDiagonalCount,
    col: col - rightDiagonalCount
  })
  if (valDirection.rightUpDiagonal) validMoves.push({
    row: row - rightDiagonalCount,
    col: col + rightDiagonalCount
  })

  return validMoves;
}


export const isValidMove = (validMoves, move, type) => {
  for(const m of validMoves){
    if(m.row === move.row && m.col === move.col){
      return true;
    }
  }
  return false;
}