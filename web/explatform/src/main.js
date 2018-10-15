// import Vue from 'vue'
import Vue from 'vue/dist/vue.js'
import VueRouter from 'vue-router'

import VueMaterial from 'vue-material'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'

import VueAwesomeSwiper from 'vue-awesome-swiper'
import 'swiper/dist/css/swiper.css'

import router from './router'
import store from './store/index'

const datasource=require("./service/api")

import Vuex from 'vuex'

Vue.use(Vuex)

Vue.config.productionTip = true

// require styles
Vue.use(VueMaterial)
Vue.use(VueAwesomeSwiper, /* { default global options } */ )
Vue.use(VueRouter)

Vue.prototype.$dataSource= datasource.default
Vue.prototype.$appName = 'My App'

new Vue({
  router,
  store,
  el: '#app'
})