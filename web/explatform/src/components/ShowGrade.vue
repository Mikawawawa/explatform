<template>
<li v-if='this.flag'><span @click='edit()'>{{info}}</span></li>
<input type="text" v-else @change='input()' @focusout="input()" autofocus="autofocus" v-model="info" style="max-width:30px;">
</template>

<script>
export default{
    props: {
        info: {
            type: String,
            default:""
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
        this.flag=(this.info==""?true:false)
    }
}
</script>

