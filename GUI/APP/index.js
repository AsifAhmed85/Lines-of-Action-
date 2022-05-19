import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import { AppContainer as ReactHotAppContainer } from 'react-hot-loader';

const AppContainer = process.env.PLAIN_HMR ? Fragment : ReactHotAppContainer;

ReactDOM.render(
  <AppContainer>
    <App />
 </AppContainer>,
  document.getElementById('root')
);
