<template message="hello">
  <div>
    <md-toolbar class="md-primary">
        <h1 class="md-title">Explatform</h1>
    </md-toolbar>
    
    <md-content>
        {{message}}
    </md-content>
  </div>
</template>

<script>
  export default {
    name: 'App',
    data(){
      return{
        message:"loading..."
      }
    },
    mounted(){
      setTimeout(()=>{
        this.message="hello"
      },3000)
    }
  }
</script>

<style>
.md-content {
  padding: 16px;
}
</style>
