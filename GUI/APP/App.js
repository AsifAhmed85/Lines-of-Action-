import React from 'react';
import './App.css';
import ConfigureStore from './redux/configureStore';
import { Provider } from 'react-redux';
import { BrowserRouter } from 'react-router-dom';
import Main from './components/Main';

const store = ConfigureStore();

function App() {
  return (
    <div className="App">
      <Provider store={store}>
        <BrowserRouter>
        <Main />
        </BrowserRouter>
      </Provider>
    </div>
  );
}

export default App;
