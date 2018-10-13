<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <ExpCard v-for = "n in num"></ExpCard>
    </div>
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import ExpCard from "../components/ExpCard.vue";
export default {
  name: "Cours  e",
  components: {
    Header,
    Footer,
    ExpCard
  },
  data: () => ({
    num: 5
  }),
  methods: {}
};
</script>


