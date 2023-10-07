<script setup>
import LoanCalculator from '../components/LoanCalculator.vue'
</script>

<template>
  <main>
    <LoanCalculator />
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
