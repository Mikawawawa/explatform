import Vuex from "vuex"
import Vue from 'vue/dist/vue.js'
Vue.use(Vuex)

const store = new Vuex.Store({
    state: {
      user_id:"",
      user_type:"",
      subject_id:"",
      Tcourse:"",
      Scourse:"",
      Texp:"",
      Tsubject_name:"",
      Ssubject_name:""
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
      setTcourse(state,Tcourse){
        state.Tcourse=JSON.parse(Tcourse)
        //state.subject_id=Tcourse.course_id
        //atate.subject_name=Tcourse.info.course_name
      },
      setScourse(state,Scourse){
        state.Scourse=JSON.parse(Scourse)
       // state.Ssubject_name=Scourse.subject_name
      },
      setTexp(state,Texp){
        state.Texp=JSON.parse(Texp)  
      }
    },
    actions:{

    }
  })

  export default store