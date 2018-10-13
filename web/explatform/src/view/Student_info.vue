<template>
    <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <!-- <CourseCard v-for="n in num" v-bind="n"></CourseCard> -->
    <md-content style="height:95vh!important">
      <Studentcourse v-bind:info="this.experiment"></Studentcourse>
    </md-content>

    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";
import Studentcourse from "../components/Studentcourse.vue";

import exp_form from "../template/experiment_form";
export default {
  name: "Experiment_info",
  components: {
    Header,
    Footer,
    Card,
    Studentcourse
  },
  data: () => ({
    search: null,
    searched: [],
    experiment: exp_form
  }),
  methods: {},
  created() {
    this.searched = this.experiment;
  }
};
</script>

<style>
md-table-content {
  height: 80vh !important;
  max-height: 100vh !important;
}
</style>