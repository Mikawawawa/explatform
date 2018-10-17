import Vuex from "vuex"
import Vue from 'vue/dist/vue.js'
Vue.use(Vuex)

const store = new Vuex.Store({
    state: {
      user_id:"",
      user_type:"",
      subject_id:"",
      subject_name:""
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
      getTcourse(state,Tcourse){
        Tcouse=JSON.parse(Tcourse)
        state.subject_id=Tcourse.subject_id
        atate.subject_name=Tcourse.subject_name
      },
      getScourse(state,Scourse){
        Scourse=JSON.parse(Scourse)
        state.subject_name=Scourse.subject_name
      },
      getExplist(state,Texp){
        state.Texp=JSON.parse(Texp)  
      }
    },
    actions:{

    }
  })

  export default store