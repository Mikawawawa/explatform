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
      },
      logout(state){
        state.user_id=""
        state.user_type=""
      },
      setExp(state,data){
        state.Exp=JSON.parse(data)
      },
      getTcouse(state,data){
        state.Tcouse=JSON.parse(data)
      },
      getScouse(state,data){
        state.Tcouse=JSON.parse(data)
      }
    },
    actions:{

    }
  })

  export default store