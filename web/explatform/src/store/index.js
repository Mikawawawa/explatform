import Vuex from "vuex"
import Vue from 'vue/dist/vue.js'
Vue.use(Vuex)

const store = new Vuex.Store({
    state: {
      user_id:"",
      user_type:""
    },
    mutations: {
      setUser(state,user){
        user=JSON.parse(user)
        state.user_id=user.user_id
        state.user_type=user.user_type
        this.$cookie.set("user_id".user.user_id)
        this.$cookie.set("user_type".user.user_type)
      }
    },
    actions:{

    }
  })

  export default store