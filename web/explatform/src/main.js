// import Vue from 'vue'
import Vue from 'vue/dist/vue.js'
import VueRouter from 'vue-router'

import VueMaterial from 'vue-material'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'

  import Vuex from 'vuex'

import VueAwesomeSwiper from 'vue-awesome-swiper'
import 'swiper/dist/css/swiper.css'

import router from './router'
import store from './store/index'
import cookie from './store/cookie'

const datasource=require("./service/api")

Vue.use(Vuex)

Vue.config.productionTip = false

// require styles
Vue.use(VueMaterial)
Vue.use(VueAwesomeSwiper, /* { default global options } */ )
Vue.use(VueRouter)

Vue.prototype.$dataSource= datasource.default
Vue.prototype.$appName = 'My App'
Vue.prototype.$cookie=cookie.default

new Vue({
  router,
  store,
  el: '#app'
})