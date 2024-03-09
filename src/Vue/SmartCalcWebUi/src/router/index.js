import { createRouter, createWebHistory } from 'vue-router'
import AboutView from '../views/AboutView.vue'
import CalculatorView from '../views/CalculatorView.vue'
import PlotView from '../views/PlotView.vue'
import DepositView from '../views/DepositView.vue'
import LoanView from '../views/LoanView.vue'
import SettingsView from '../views/SettingsView.vue'


const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/about',
      name: 'about',
      component: AboutView
    },
    {
      path: '/',
      name: 'calculator',
      component: CalculatorView
    },
    {
      path: '/plot',
      name: 'plot',
      component: PlotView
    },
    {
      path: '/loan_calculator',
      name: 'loan_calculator',
      component: LoanView
    },
    {
      path: '/deposit_calculator',
      name: 'deposit_calculator',
      component: DepositView
    },
    {
      path: '/settings',
      name: 'settings',
      component: SettingsView
    },
  ]
})

export default router
