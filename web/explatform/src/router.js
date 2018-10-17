import VueRouter from 'vue-router'
// views
import Login from './view/Login'
import Home from "./view/Index"

// import Teacher_course from "./view/Teacher_course"
import Teacher_info from "./view/Teacher_info"
import Teacher_exp from "./view/Teacher_exp"

import Markdown from "./view/Markdown"
import Article from "./view/Article"

import Student_info from "./view/Student_info"
// import Student_course from "./view/Student_course"

import Test from "./view/Test.vue"
// rules
const routes = [
    {
        path:"/test",
        component:Test
    },
    {
        path: '/',
        props:true,
        component: Home
    },
    {
        path: '/login',
        props:true,
        component: Login
    },
     {
         path: '/teacher_course',
         props:false,
         component: Teacher_course
     },
     /*{
         path: '/student_course',
         props:true,
        component: Student_course
     },
    {
        path: '/student_exp',
        props:true,
        component: Student_info
    },
    {
        path: '/teacher_exp',
        props:false,
        component: Teacher_exp
    },*/
    {
        path: '/teacher_info',
        component:Teacher_info
    },
    {
        path: '/markdown',
        props:true,
        component: Markdown
    },
    {
        path: '/article',
        props:false,
        component: Article
    }
]
// router
const router = new VueRouter({
    routes // (缩写) 相当于 routes: routes
})
export default router