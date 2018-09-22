<template>
    <div>
        <Header></Header>
        <md-content class="article">
            <md-card>
                <md-card-header>
                    <div class="md-title">Card without hover effect</div>
                </md-card-header>
                <md-card-content v-html="compiledMarkdown"></md-card-content>
            </md-card>
        </md-content>
    </div>
</template>

<script>
import Header from "../components/Header.vue";
import marked from "marked";

import article from "../template/article";

export default {
  components: {
    Header
  },
  data: () => ({
    content: ""
  }),
  computed: {
    compiledMarkdown: function() {
      return marked(article, { sanitize: true });
    }
  },
  methods: {}
};
</script>
<style>
@media (max-width: 600px) {
  .article {
    width: 100% !important;
  }
}
.article {
  width: 75%;
  margin: auto;
}
</style>
 