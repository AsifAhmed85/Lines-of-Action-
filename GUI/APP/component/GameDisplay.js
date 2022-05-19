import React, { useEffect, useState } from 'react';
import { Grid, makeStyles, Paper, TextField, Button } from '@material-ui/core'
import { useDispatch, useSelector } from 'react-redux';
import { changeHasBotMove, finishGame, sendBoardToBot, stopTimer } from '../redux/actioncreators';
import { getWinner } from '../game-logic/winningLogic';


const useStyles = makeStyles((theme) => ({
  root: {
    '& .MuiTextField-root': {
      margin: theme.spacing(2),
      // width: '25ch'
    },
  },
  modal: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
  },
  paper: {
    padding: '10px',
    maxWidth: '250px',
    minHeight: '340px'
  },
}));

function GameDisplay({ setIsOpen }) {
  const classes = useStyles();

  const { firstPlayerName, secondPlayerName } = useSelector(state => state.game)
  const [elapsedTime, setElapsedTime] = useState(0);

  const { board, currentPlayer, latestBlackMove, latestWhiteMove,
    totalBlackCells, totalWhiteCells } = useSelector(state => state.board);
  const { winner, firstPlayerType, secondPlayerType,
     subProcess1, subProcess2, hasBot1Move, hasBot2Move } = useSelector(state => state.game);
  const { startedAt, stoppedAt } = useSelector(state => state.timer);
  const dispatch = useDispatch();
  const minute = Math.floor(elapsedTime / 60);
  const sec = elapsedTime % 60;

  const getCurrentTurn = (player) => {
    return player === 'black' ? firstPlayerName.toUpperCase() : secondPlayerName.toUpperCase();
  }

  const handleSubmit = (e) => {
    e.preventDefault();
    setIsOpen(true);
    dispatch(stopTimer());
    dispatch(finishGame('', 0));
  }

  useEffect(() => {
    if (latestBlackMove && latestWhiteMove) {
      let lastMoveByCurrent, lastMoveByOpposition, currentCells, oppostionCells;
      if (currentPlayer === 'white') {
        lastMoveByCurrent = latestBlackMove;
        currentCells = totalBlackCells;
        lastMoveByOpposition = latestWhiteMove;
        oppostionCells = totalWhiteCells;
      } else {
        lastMoveByCurrent = latestWhiteMove;
        currentCells = totalWhiteCells;
        lastMoveByOpposition = latestBlackMove;
        oppostionCells = totalBlackCells;
      }

      let winnerPlayer = getWinner(board, lastMoveByCurrent, lastMoveByOpposition, currentCells, oppostionCells)
      if (winnerPlayer) {
        dispatch(stopTimer());
        dispatch(finishGame(winnerPlayer, elapsedTime))
        return;
      }
    }

    // send bots the board
    if (firstPlayerType === 'bot' && currentPlayer === 'black' && !hasBot1Move) {
      sendBoardToBot(board, subProcess1);
      dispatch(changeHasBotMove('hasBot1Move'))
    }
    if (secondPlayerType === 'bot' && currentPlayer === 'white' && !hasBot2Move) {
      sendBoardToBot(board, subProcess2);
      dispatch(changeHasBotMove('hasBot2Move'))
    }

  }, [currentPlayer, firstPlayerType, secondPlayerType])

  useEffect(() => {
    let timer;
    if (startedAt && !stoppedAt) {
      timer = setInterval(() => setElapsedTime(elapsedTime + 1), 1000)
    } else {
      setElapsedTime(0);
    }
    return () => {
      if (timer) clearInterval(timer);
    }
  }, [elapsedTime, startedAt, stoppedAt])

  return (
    <Paper elevation={3} className={classes.paper}>
      {firstPlayerName.length !== 0 ? (
        <h3 style={{
          textAlign: 'center',
        }}>{winner.length === 0 ? getCurrentTurn(currentPlayer) + "'s Turn" : getCurrentTurn(winner) + ' WON!!!!'}</h3>
      ) : (null)
      }
      <Grid container direction="row" justify="center" alignItems="center">
        <form
          className={classes.root}
          onSubmit={handleSubmit}
        >
          <Grid item>
            <TextField
              label='First Player Name (Blue)'
              value={firstPlayerName}
              InputProps={{
                readOnly: true
              }}
            />
          </Grid>
          <Grid item>
            <TextField
              label='Second Player Name (Red)'
              value={secondPlayerName}
              InputProps={{
                readOnly: true
              }}
            />
          </Grid>
          <Grid item>
            <TextField
              label='Time Elapsed (m : s)'
              value={minute + ' : ' + sec}
              InputProps={{
                readOnly: true
              }}
            />
          </Grid>
          <Grid item align="center">
            <Button
              size='small'
              type="submit"
              variant="contained"
              color="primary"
            >
              Quit the play
            </Button>
          </Grid>
        </form>
      </Grid>
    </Paper>
  )
}

export default GameDisplay;
