import { Grid, Paper } from '@material-ui/core';
import React, { useState } from 'react';
import Board from './Board';
import GameDisplay from './GameDisplay';
import GameStart from './GameStart';
import GameFinish from './GameFinish';
import Footer from './Footer';

function Main() {
  const [isOpen, setIsOpen] = useState(true);

  return (
    <div >
      <GameStart isOpen={isOpen} setIsOpen={setIsOpen} />
      <GameFinish setGameStart={setIsOpen} />
      <Grid style={{
        minHeight: '100vh'
      }} container justify="space-around" direction="column" alignItems="center">
        <Grid item style={{
          width: '100%'
        }}>
          <Paper style={{
            minHeight: '90vh',
            padding: '20px'
          }} elevation={3}>
            <h2 style={{
              marginBottom: '50px',
              textAlign: 'center'
            }}>
              LINES OF CODE
      </h2>
            <Grid container justify="center">
              <Grid item align="right" md={6} style={{
                paddingRight: '50px'
              }}>
                <Board />
              </Grid>
              <Grid item md={6} style={{
                padding: '15px 20px 20px 30px'
              }}>
                <GameDisplay setIsOpen={setIsOpen} />
              </Grid>
            </Grid>
          </Paper>
        </Grid>
        <Grid item>
          <Footer />
        </Grid>
      </Grid>
    </div>
  )
}

export default Main;
