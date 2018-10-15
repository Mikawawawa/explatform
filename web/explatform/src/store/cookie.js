export default{
    set: function (cname, cvalue) {
        let date = new Date();
        date.setTime(date.getTime() + (30 * 60 * 1000));
        let expires = "expires=" + date.toUTCString();
        document.cookie = cname + "=" + cvalue + "; " + expires;
    },
    //获取cookie
    get: function (cname) {
        let name = cname + "=";
        let ca = document.cookie.split(';');
        for (let i = 0; i < ca.length; i++) {
            let c = ca[i];
            while (c.charAt(0) == ' ')
                c = c.substring(1);
            if (c.indexOf(name) != -1)
                return c.substring(name.length, c.length);
        }
        return "";
    },
    clear: function (cname) {
        this.set(cname, "", -1);
    },
}