<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <md-content style="height:95vh!important">
      <md-empty-state
        v-if="this.Scourse==''"
        md-icon="book"
        md-label="未找到实验"
        md-description="可能是网络质量不佳，请耐心等待">
      </md-empty-state>
    
    </md-content>
    <md-snackbar :md-position="'center'" :md-active.sync="showToast" md-persistent>
        <span>抱歉，服务器吃饭去了，请重试</span>
        <md-button class="md-primary" @click="showToast = false">重试</md-button>
      </md-snackbar>
    <div class="md-layout md-gutter" style="padding:20px">
        <Card v-for="value in Scourse" v-bind:name="value.course_name"></Card>
    </div>
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";

// import Scourse_form from "../template/Texp_form";
const Scourse_form=[]
export default {
  name: "Student_course",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    showToast:false,
    search: null,
    searched: [],
    Scourse: []
  }),
  created:async function() {
      let data
      if(this.$store.state.Scourse ==""){
        this.Scourse=this.$store.state.Scourse
        console.log(this.$store.state.Scourse)
      }else{
        var delay=setTimeout(async()=>{
          this.showToast=true
          data=(data!==" "?data:Scourse_form)
          this.Scourse=Scourse_form
        },10000)
      }
        data= await this.$dataSource.sGetCourse("17041803")
        if(data.status==0){
          clearInterval(delay)
          this.showToast=true
          this.Scourse=""
        }else{
          clearInterval(delay)
          this.$store.commit("setTcourse",JSON.stringify(data.info))
          this.Scourse=this.$store.state.Scourse
        }
      }
};
</script>