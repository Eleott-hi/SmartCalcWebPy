// store.js

import { createStore } from 'vuex';

export default createStore({
  state: {
    buttonColor: '#00FF00', // Set your default color
  },
  mutations: {
    setButtonColor(state, color) {
      state.buttonColor = color;
    },
  },
});
