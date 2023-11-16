<script>
export default {
  data() {
    return {
      colorScheme: localStorage.getItem('darkMode') === 'true',
    };
  },
  
  watch: {
    colorScheme: {
      handler(isDarkMode) {
        this.ToggleColorScheme(isDarkMode);
      },
      immediate: true,
    },
  },

  methods: {
    ToggleColorScheme(isDarkMode) {
      document.body.classList.toggle('dark-mode', isDarkMode);
      localStorage.setItem('darkMode', isDarkMode);
    },
  },
};
</script>

<template>
  <div class="container">
    <div class="mb-4 input-group">
      <div class="form-check form-switch">
        <input
          v-model="colorScheme"
          class="form-check-input"
          type="checkbox"
          id="flexSwitchCheckChecked"
        />
        <label class="form-check-label" for="flexSwitchCheckChecked">Dark Mode</label>
      </div>
    </div>
  </div>
</template>
