<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
     <div class="md-layout md-gutter" style="padding:20px">
    <Card  v-for="value in Tcourse" v-bind:name="value.course_name" info="1"></Card>
    </div>
    <md-content style="height:95vh!important">
      <md-empty-state
        v-if="this.Tcourse==''"
        md-icon="book"
        md-label="未找到实验"
        md-description="可能是网络质量不佳，请耐心等待">
      </md-empty-state>
    
    </md-content>
    <md-snackbar :md-position="'center'" :md-active.sync="showToast" md-persistent>
        <span>抱歉，服务器吃饭去了，请重试</span>
        <md-button class="md-primary" @click="showToast = false">重试</md-button>
      </md-snackbar>
      <p>{{Tcourse}}</p>
    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";

import Tcourse_form from "../template/Tcourse_form";
export default {
  name: "Course1",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    showToast:false,
    search: null,
    searched: [],
    Tcourse: []
  }),
  created:async function() {
      let data
      if(this.$store.state.Tcourse!==""){
        this.Tcourse=this.$store.state.Tcourse
        console.log(this.$store.state.Tcourse)
      }else{
        var delay=setTimeout(async()=>{
          this.showToast=true
          data=(data!==" "?data:Tcourse_form)
          this.Tcourse=Tcourse_form
        },10000)
      }
       data= await this.$dataSource.tGetCourse("17031803")
        if(data.status==0){
          clearInterval(delay)
          this.showToast=true
          this.Tcourse=""
        }else{
          clearInterval(delay)
          this.$store.commit("setTcourse",JSON.stringify(data.info))
          this.Tcourse=this.$store.state.Tcourse
        }
      }
};
</script>


