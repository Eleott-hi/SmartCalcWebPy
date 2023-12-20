import './assets/main.css'

import { createApp } from 'vue'
import store from './store';
import App from './App.vue'
import router from './router'
import VueDatePicker from '@vuepic/vue-datepicker';
import '@vuepic/vue-datepicker/dist/main.css'

const app = createApp(App);

app.use(router).use(store);
app.component('VueDatePicker', VueDatePicker);


app.mount('#app')
