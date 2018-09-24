import VueRouter from 'vue-router'
// views
import Login from './view/Login'
import Home from "./view/Index"
import Course from "./view/Course"
import Markdown from "./view/Markdown"
import Article from "./view/Article"
import Info from "./view/Info"
import Experiment_info from "./view/Experiment_info"
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
        path: '/course',
        component: Course
    },
    {
        path: '/Student_course',
        component: Student_course
    },
    {
        path: '/info',
        component: Info
    },
    {
        path: '/exp_info',
        component:Experiment_info
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