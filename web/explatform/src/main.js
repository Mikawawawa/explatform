// import Vue from 'vue'
import Vue from 'vue/dist/vue.js';
import Login from './view/Login'
import Home from "./view/Index"
import VueRouter from 'vue-router'
import VueMaterial from 'vue-material'
import VueAwesomeSwiper from 'vue-awesome-swiper'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'
import 'swiper/dist/css/swiper.css'

Vue.config.productionTip = false

// require styles
Vue.use(VueMaterial)
Vue.use(VueAwesomeSwiper, /* { default global options } */ )
Vue.use(VueRouter)

const routes = [
  { path: '/', component: Home },
  { path: '/login', component: Login }
]

const router = new VueRouter({
  routes // (缩写) 相当于 routes: routes
})

new Vue({
  router,
  el: '#app'
  // template: '<Home/>',
  // components: { Home,Login }
})