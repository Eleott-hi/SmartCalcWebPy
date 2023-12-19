// store.js

import { createStore } from 'vuex';

export default createStore({
  state: {
    primaryBtnBootstrapType: 'btn-primary',
    secondaryBtnBootstrapType: 'btn-secondary',
    isDarkMode: false,
  },

  mutations: {
    updateConfig(state, config) {
      state.primaryBtnBootstrapType = config.primaryBtnType;
      state.secondaryBtnBootstrapType = config.secondaryBtnType;
      state.isDarkMode = config.isDarkMode;


      console.log(config);
    },
  },

  actions: {
    saveConfig({ commit, state }) {
      $.ajax({
        url: 'http://localhost:8000/config',
        type: 'POST',
        contentType: 'application/json',
        data: JSON.stringify({
          primaryBtnType: state.primaryBtnBootstrapType,
          secondaryBtnType: state.secondaryBtnBootstrapType,
          isDarkMode: state.isDarkMode,
        }),
        headers: {
          'X-CSRFToken': document.querySelector('[name=csrfmiddlewaretoken]').value,
        },

        success: (data) => {
          commit('updateConfig', data);
          console.log('Config saved successfully');
        },
        error: (error) => {
          console.error('Error saving config', error);
        },
      });
    },
  },
});
