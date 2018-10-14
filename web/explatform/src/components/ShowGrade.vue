<template>
<li v-if='this.flag'><span @click='edit()'>{{grade}}</span></li>
<input type="text" v-else @change='input()' @focusout="input()" autofocus="autofocus" v-model="grade" style="max-width:30px;">
</template>

<script>
export default{
    props: {
        grade: {
            type: String,
            default:"0"
        }
    },
    data:()=>({
        flag:true
    }),
    methods:{
        edit(){
            this.flag=false;
        },
        input(){
            this.flag=true;
        },
    },
    created:()=>{
        this.flag=(this.grade==""?true:false)
    }
}
</script>

