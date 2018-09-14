<template>
    <div>
        <Header></Header>
        <md-content>
            <Editor></Editor>
        </md-content>
    </div>
</template>

<script>
import Editor from "../components/Editor.vue"
import Header from "../components/Header.vue"
export default {
  components: {
    Header,
    Editor
  },
  data: () => ({
    input: "#hello"
  }),
  computed: {},
  methods: {}
};
</script>
 <style>
#editor {
  margin: 0;
  height: 95vh;
  font-family: "Helvetica Neue", Arial, sans-serif;
  color: #333;
}
</style>
 