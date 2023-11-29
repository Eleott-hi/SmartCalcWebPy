<script>
export default {
  data() {
    return {
      textColor: this.$store.state.buttonColor, // Initialize with the default $primary color
    };
  },
  
  watch: {
    textColor: {
      handler(newColor) {
        this.SetPrimaryColor(newColor);
      },
      immediate: true,
    },
  },

  methods: {
    SetPrimaryColor(newColor) {
      // Update the $primary variable with the selected color
      // this.$root.$style.$primary = newColor;

      // Update the CSS variable with the selected color
      // document.documentElement.style.setProperty('--primary',    newColor);
      // document.documentElement.style.setProperty('--bs-primary', newColor);

      this.$store.commit('setButtonColor', newColor);

      // Implement additional logic if needed
      console.log(`Primary color set to: ${newColor}`);
    },
  },

  computed: {
    buttonColor: {
      get() {
        return this.$store.state.buttonColor;
      },
      set(value) {
        this.$store.commit('setButtonColor', value);
      },
    },
  },

};
</script>


<template>
  <div class="container">
    <div class="mb-4 input-group">
      <label for="colorPicker" class="form-label mb-2">Choose Text Color:</label>
      <div class="input-group-prepend">
        <span class="input-group-text">#</span>
      </div>
      <input
        id="colorPicker"
        v-model="textColor"
        @input="SetTextColor"
        type="color"
        class="form-control form-control-color"
      />
    </div>
    <button :style="{ backgroundColor : $store.state.buttonColor }">Click me</button>
  </div>
</template>


