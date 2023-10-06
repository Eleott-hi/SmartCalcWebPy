<script setup>
import Calculator from '../components/Calculator.vue'
</script>

<template>
  <main>
    <Calculator />
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
