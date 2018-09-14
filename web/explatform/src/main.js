// import Vue from 'vue'
import Vue from 'vue/dist/vue.js'
import VueRouter from 'vue-router'

import VueMaterial from 'vue-material'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'

import VueAwesomeSwiper from 'vue-awesome-swiper'
import 'swiper/dist/css/swiper.css'

import router from './router'

Vue.config.productionTip = false

// require styles
Vue.use(VueMaterial)
Vue.use(VueAwesomeSwiper, /* { default global options } */ )
Vue.use(VueRouter)

new Vue({
  router,
  el: '#app'
})