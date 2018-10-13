<template>
    <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <!-- <CourseCard v-for="n in num" v-bind="n"></CourseCard> -->
    <md-content style="height:95vh!important">
      <StudentInfo v-bind:info="this.users"></StudentInfo>
    </md-content>

    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import CourseCard from "../components/CourseCard.vue";
import StudentInfo from "../components/StudentInfo.vue";

import form from "../template/student_form";
export default {
  name: "Info",
  components: {
    Header,
    Footer,
    CourseCard,
    StudentInfo
  },
  data: () => ({
    search: null,
    searched: [],
    users: form
  }),
  methods: {},
  created() {
    this.searched = this.users;
  }
};
</script>

<style>
md-table-content {
  height: 80vh !important;
  max-height: 100vh !important;
}
</style>
