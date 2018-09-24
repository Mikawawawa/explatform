<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <Studentcard v-bind="1"></Studentcard>
    </div>
    <!-- <md-content class="list" style="margin-left:auto">
        

    </md-content> -->
    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Studentcard from "../components/Studentcard.vue";
export default {
  name: "Student_course",
  components: {
    Header,
    Footer,
    Studentcard
  },
  data: () => ({
    num: 1
  }),
  methods: {}
};
</script>
