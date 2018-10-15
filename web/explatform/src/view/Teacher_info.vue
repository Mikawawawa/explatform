<template>
    <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <md-content style="height:95vh!important">
      <TeacherList v-bind:info="this.users"></TeacherList>
    </md-content>

    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import TeacherList from "../components/TeacherList.vue";

import form from "../template/student_form";
export default {
  name: "Info",
  components: {
    Header,
    Footer,
    TeacherList
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
