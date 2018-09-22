import VueRouter from 'vue-router'
// views
import Login from './view/Login'
import Home from "./view/Index"
import Course from "./view/Course"
import Markdown from "./view/Markdown"
import Article from "./view/Article"
import Info from "./view/Info"

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
        path: '/info',
        component: Info
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