import React from 'react';
import AdjustIcon from '@material-ui/icons/Adjust';
import { makeStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import { highlightAvailableMoves, move } from '../redux/actioncreators';
import { useDispatch, useSelector } from 'react-redux';
import { getValidMoves } from '../game-logic/validMoves';

const useStyles = makeStyles((theme) => ({
  cellButton: {
    maxWidth: '50px',
    maxHeight: '50px',
    minWidth: '50px',
    minHeight: '50px',
  },
  cellHighlightButton: {
    maxWidth: '50px',
    maxHeight: '50px',
    minWidth: '50px',
    minHeight: '50px',
    border: '1px solid aliceBlue',
    borderRadius: '2px',
    backgroundColor: '#ABEBC6'
  }
}));

const inCells = (cells, row, col) => {
  if(!cells) return false;
  let found = false;
  cells.map(cell => {
    if(cell.row === row && cell.col === col)
      found = true;
  })
  return found;
}

function Cell(props) {
  const classes = useStyles();
  let buttonClassName = classes.cellButton;
  const { board, currentPlayer, highlightCells } = useSelector(state => state.board);
  const dispatch = useDispatch();
  let isHighlighted = false;
  let color;
  let disabled;

  if(props.type === currentPlayer){
    disabled = false;
  } else{
    disabled = true;
  }
  if(inCells(highlightCells, props.row, props.col)){
    buttonClassName = classes.cellHighlightButton; 
    disabled = false;
    isHighlighted = true;
  } 
  if(props.type === 'black'){
    color = 'primary';
  } else if(props.type === 'white'){
    color = 'secondary';
  } else{
    color = 'disabled';
  }

  

  const handleClick = () => {
    if(isHighlighted){
      dispatch(move(props.row, props.col));
    } else{
    const availableMoves = getValidMoves(props.row, props.col, board);
    dispatch(highlightAvailableMoves(availableMoves, {
      row: props.row,
      col: props.col
    }));
    }
  }

  return (
    <Button
      onClick={handleClick}
      className={buttonClassName}
      disabled={disabled}>
      <AdjustIcon
        color={color}
      />
    </Button>
  )
}

export default Cell;
