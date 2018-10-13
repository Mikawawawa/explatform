<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <CourseCard v-for="value in course" v-bind:name="value.name"></CourseCard>
    </div>
    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import CourseCard from "../components/CourseCard.vue";
export default {
  name: "Course",
  components: {
    Header,
    Footer,
    CourseCard
  },
  data: () => ({
    num: 5,
    course:[
      {name:"数电实验"},
      {name:"电分实验"},
      {name:"模电实验"}
    ]
  }),
  methods: {}
};
</script>


