import { Grid } from '@material-ui/core';
import React from 'react';

function Footer() {
  return (
    <Grid style={{
      }} container justify="center" alignItems="center">
      <Grid item>
      <span style={{
        fontWeight: 700,
        fontSize: "small",
        marginBottom: '20px'
      }}>
        Developed By: Abdur Rashid Tushar (CSE, BUET)
        </span>
      </Grid>
    </Grid>
  )
}

export default Footer;
