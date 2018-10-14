<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <Card v-for="value in course" v-bind:name="value.name" info="2"></Card>
    </div>
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";
export default {
  name: "Course2",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    msg:[],
    course:[
      {name:"示波器的使用"},
      {name:"迈克尔分析"},
      {name:"伏安法测电流"}
    ]
  }),
  methods: {

  },
  created(){  
    let routerParams = this.$route.query.dataobj
    // 将数据放在当前组件的数据内
    this.msg = routerParams
    if(this.msg=="数电实验"){
        this.course=[
          {name:"差分方程"},
          {name:"数电分析"},
          {name:"小信号模型"}
        ]
      }
    else if(this.msg=="电分实验"){
        this.course=[
          {name:"差分方程"},
          {name:"电路分析"},
          {name:"小信号模型"}
        ]
      }
      else{
        this.course=[
          {name:"差分方程"},
          {name:"模电分析"},
          {name:"小信号模型"}
        ]
      }
  }
};
</script>


