<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
        <p>{{sexp}}</p>
        <p>{{texp}}</p>
        <p>{{tcourse}}</p>
        <p>{{this.$dataSource.request}}</p>
    </div>
</template>

<script>
export default {
    name:"test",
    data:()=>({
        test:"",
        login:"",
        sexp:"",
        tcourse:"",
        texp:""
    }),
    created:async function(){
        this.test=this.$appName
        // console.log(this.$dataSource)
        this.login=await this.$dataSource.Login("17031803","aptx4869")
        this.sexp=await this.$dataSource.sGetExp("17041802","101")
        this.tcourse=await this.$dataSource.tGetCourse("17031803")
        this.texp=await this.$dataSource.tCourseDetail("17040318")
        // console.log(this.sexp)
    }
}
</script>

