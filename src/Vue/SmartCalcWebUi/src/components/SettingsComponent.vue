<script>
export default {
  data() {
    return {
      bootstrapButtonStyles: [
        "btn-primary",
        "btn-secondary",
        "btn-success",
        "btn-danger",
        "btn-warning",
        "btn-info",
        "btn-light",
        "btn-dark",
      ],
    };
  },

  methods: {
    ToggleColorScheme() {
      this.$store.state.isDarkMode = !this.$store.state.isDarkMode;
      document.body.classList.toggle("dark-mode", this.$store.state.isDarkMode);
      console.log(`Switched mode to ${this.$store.state.isDarkMode}`);
      this.$store.dispatch('saveConfig');
    },

    SetPrimaryButton(buttonStyle) {
      this.$store.state.primaryBtnBootstrapType = buttonStyle;
      console.log("Set Primary", buttonStyle);
      this.$store.dispatch('saveConfig');
    },

    SetSecondaryButton(buttonStyle) {
      this.$store.state.secondaryBtnBootstrapType = buttonStyle;
      console.log("Set Secondary", buttonStyle);
      this.$store.dispatch('saveConfig');
    },
  },
};
</script>


<template>
  <div class="container mt-5">
    <div class="mb-4 input-group">
      <div class="form-check form-switch">
        <input
          v-model="$store.state.isDarkMode"
          class="form-check-input"
          type="checkbox"
          id="flexSwitchCheckChecked"
          @click="ToggleColorScheme"
        />
        <label class="form-check-label" for="flexSwitchCheckChecked"
          >Dark Mode</label
        >
      </div>
    </div>

    <div class="row">
      <div class="col btn-group-toggle" data-toggle="buttons">
        <div class="row" v-for="style in bootstrapButtonStyles" :key="style">
          <div :class="['btn', style]" @click="SetPrimaryButton(style)">
            <label>
              <input
                type="radio"
                name="primaryOptions"
                autocomplete="off"
                :checked="$store.state.primaryBtnBootstrapType === style"
                :id="`option primary ${style}`"
              />
              Primary button
            </label>
          </div>
        </div>
      </div>

      <div class="col-1"></div>

      <div class="col btn-group-toggle" data-toggle="buttons">
        <div class="row" v-for="style in bootstrapButtonStyles" :key="style">
          <div
            :class="['btn', style, 'btn-radio']"
            @click="SetSecondaryButton(style)"
          >
            <label>
              <input
                type="radio"
                name="secondaryOptions"
                autocomplete="off"
                :checked="$store.state.secondaryBtnBootstrapType === style"
                :id="`option secondary ${style}`"
              />
              Secondary button
            </label>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

