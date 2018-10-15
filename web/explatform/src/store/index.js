import Vuex from "vuex"
import Vue from 'vue/dist/vue.js'
Vue.use(Vuex)

const store = new Vuex.Store({
    state: {
      user:{}
    },
    mutations: {
      setUser(state,user){
        user=JSON.parse(user)
        state.user.id=user.user_id
        state.user.type=user.user_type
      }
    },
    actions:{

    }
  })

  export default store