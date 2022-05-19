import { Button, Grid, makeStyles, MenuItem, Modal, Paper, Select, TextField, FormControl, InputLabel, Input } from '@material-ui/core';
import React, { useState } from 'react';
import { useDispatch } from 'react-redux';
import { startGame } from '../redux/actioncreators';


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
    width: '250px',
    minHeight: '300px',
    padding: '10px',
  },
  selectItem: {
    padding: '10px 10px 20px 20px'
  },
  select: {
    minWidth: '100px'
  },
  input: {
    marginLeft: '10px'
  }
}));


function GameStart({isOpen, setIsOpen}) {
  const [firstName, setFirstName] = useState('Player 1');
  const [secondName, setSecondName] = useState('Player 2');
  const [firstType, setFirstType] = useState('human');
  const [secondType, setSecondType] = useState('human');
  const [boardSize, setBoardSize] = useState(8);
  const dispatch = useDispatch();
  const classes = useStyles();

  const handleSubmit = (e) => {
    e.preventDefault();
    dispatch(startGame(firstName, secondName, firstType, secondType, boardSize));
    setIsOpen(false);
  }

  return (
    <Modal
      open={isOpen}
      className = {classes.modal}
    >
      <Paper elevation={3} className={classes.paper}>
        <Grid container direction="row" justify="center" alignItems="center">
        <form
          className={classes.root}
          onSubmit={handleSubmit}
        >
          <Grid item className={classes.selectItem}>
            <FormControl className={classes.select}>
            <InputLabel>Player 1 Type</InputLabel>
            <Select
              value={firstType}
              onChange={e => setFirstType(e.target.value)}
            >
              <MenuItem value={'human'}>Human</MenuItem>
              <MenuItem value={'bot'}>Bot</MenuItem>
            </Select>
            </FormControl>
          </Grid>
          <Grid item className={classes.selectItem}>
            <FormControl className={classes.select}>
            <InputLabel>Player 2 Type</InputLabel>
            <Select
              value={secondType}
              onChange={e => setSecondType(e.target.value)}
            >
              <MenuItem value={'human'}>Human</MenuItem>
              <MenuItem value={'bot'}>Bot</MenuItem>
            </Select>
            </FormControl>
          </Grid>
          <Grid item>
            <TextField
              required
              label='Player 1 Name'
              value={firstName}
              onChange={e => setFirstName(e.target.value)}
            />
          </Grid>
          <Grid item>
            <TextField
              required
              label='Player 2 Name'
              value={secondName}
              onChange={e => setSecondName(e.target.value)}
            />
          </Grid>
          <Grid item className={classes.selectItem}>
            <FormControl className={classes.select}>
            <InputLabel>Board Size</InputLabel>
            <Select
              value={boardSize}
              onChange={e => setBoardSize(e.target.value)}
            >
              <MenuItem value={8}>8</MenuItem>
              <MenuItem value={6}>6</MenuItem>
            </Select>
            </FormControl>
          </Grid>
          <Grid item align="center">
            <Button 
              size='small'
              type="submit"
              variant="contained"
              color="primary"
            >
              Start Game
            </Button>
          </Grid>
        </form>
        </Grid>
      </Paper>
    </Modal>
  )
}

export default GameStart;
