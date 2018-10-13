import VueRouter from 'vue-router'
// views
import Login from './view/Login'
import Home from "./view/Index"

import Teacher_course from "./view/Teacher_course"
import Teacher_info from "./view/Teacher_info"
import Teacher_exp from "./view/Teacher_exp"

import Markdown from "./view/Markdown"
import Article from "./view/Article"

import Student_info from "./view/Teacher_info"
import Student_course from "./view/Student_course"

// rules
const routes = [{
        path: '/',
        component: Home
    },
    {
        path: '/login',
        component: Login
    },
    {
        path: '/teacher_course',
        component: Teacher_course
    },
    {
        path: '/student_course',
        component: Student_course
    },
    {
        path: '/student_exp',
        component: Student_info
    },
    {
        path: '/teacher_exp',
        component: Teacher_exp
    },
    {
        path: '/teacher_info',
        component:Teacher_info
    },
    {
        path: '/markdown',
        component: Markdown
    },
    {
        path: '/article',
        component: Article
    }
]
// router
const router = new VueRouter({
    routes // (缩写) 相当于 routes: routes
})
export default router