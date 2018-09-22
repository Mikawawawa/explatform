<template>
        <div>
        <md-table v-model="searched" md-sort="name" md-sort-order="asc" md-fixed-header  style="height:100%!important">
          <md-table-toolbar>
              <div class="md-toolbar-section-start">
                <h1 class="md-title">Users</h1>
              </div>

              <md-field md-clearable class="md-toolbar-section-end">
                <md-input placeholder="Search by name..." v-model="search" @input="searchOnTable" />
              </md-field>
          </md-table-toolbar>

          <md-table-empty-state
              md-label="No users found"
              :md-description="`No user found for this '${search}' query. Try a different search term or create a new user.`">
              <md-button class="md-primary md-raised" @click="newUser">Create New User</md-button>
          </md-table-empty-state>

          <md-table-row slot="md-table-row" slot-scope="{ item }">
              <md-table-cell md-label="学号" md-sort-by="id" md-numeric>{{ item.id }}</md-table-cell>
              <md-table-cell md-label="姓名" md-sort-by="name">{{ item.name }}</md-table-cell>
              <md-table-cell md-label="实验分" md-sort-by="email">{{ item.email }}</md-table-cell>
              <md-table-cell md-label="报告分" md-sort-by="gender">
                <md-button class="md-size-1x md-icon-button" v-if="item.gender=='Male'" style="padding:0px" @click="goArticle()">
                  <md-icon>visibility</md-icon>
                </md-button>
                <md-button class="md-size-1x md-icon-button" v-else style="padding:0px" @click="goHome()">
                  <md-icon>visibility</md-icon>
                </md-button>
              </md-table-cell>
              <md-table-cell md-label="Unmarked" md-sort-by="title">
                <!-- {{ item.title }} -->
                <Mark5></Mark5>
              </md-table-cell>
          </md-table-row>
          
        </md-table>
    </div>
</template>

<script>
import Mark5 from "./GradeFive.vue";
export default {
  components: {
    Mark5
  },
  props: {
    info: {
      type: Array
    }
  },
  data: () => ({
    search: null,
    searched: []
  }),
  methods: {
    goArticle() {
      this.$router.push("/article");
    },
    newUser() {
      window.alert("Noop");
    },
    searchOnTable() {
      this.searched = this.searchByName(this.users, this.search);
    },
    searchByName(users, search) {
      return search == ""
        ? this.info
        : [
            {
              id: 1,
              name: "Shawna Dubbin",
              email: "sdubbin0@geocities.com",
              gender: "Male",
              title: "Assistant Media Planner"
            },
            {
              id: 2,
              name: "Odette Demageard",
              email: "odemageard1@spotify.com",
              gender: "Female",
              title: "Account Coordinator"
            }
          ];
    }
  },
  created() {
    this.searched = this.info;
  }
};
</script>

<style>
.md-table-content {
  max-height: 90vh !important;
  height: 90vh !important;
}
</style>


