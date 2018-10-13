<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <Card v-for="value in course" v-bind:name="value.name"></Card>
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
    course:[
      {name:"示波器的使用"},
      {name:"迈克尔分析"},
      {name:"伏安法测电流"}
    ]
  }),
  methods: {}
};
</script>


