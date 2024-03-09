<script setup>
import SettingsComponent from '../components/SettingsComponent.vue'
</script>

<template>
  <main>
    <SettingsComponent />
  </main>
</template>

<style>
@media (min-width: 1024px) {
  .about {
    min-height: 100vh;
    display: flex;
    align-items: center;
  }
}
</style>
