window.addEventListener("load", function () {
    // darkmode
    var dark = false;
    document.getElementById("nightmode").addEventListener("click", togglen);

    function night() {
        document.body.style.color = "white";
        document.body.style.backgroundColor = "rgb(20,20,20)";
        dark = true;
    }

    function day() {
        document.body.style.color = "black";
        document.body.style.backgroundColor = "#2f80ed";
        dark = false;
    }

    function togglen() {
        dark ? day() : night();
    }
// timer
    function startTime() {
        const today = new Date();
        let h = today.getHours();
        let m = today.getMinutes();
        let s = today.getSeconds();
        m = checkTime(m);
        s = checkTime(s);
        document.getElementById('clock').innerHTML =  h + ":" + m + ":" + s;
        document.getElementById('clock').textContent =  h + ":" + m + ":" + s;
        setTimeout(startTime, 1000);
    }

    function checkTime(i) {
        if (i < 10) {i = "0" + i};
        return i;
    }
    startTime()

    // dropdown
    document.getElementById("dropdown").addEventListener("click", togglemenu);

    function togglemenu(){
        var x = document.getElementById("links");
        if (x.style.display === "block") {
            x.style.display = "none";
        } else {
            x.style.display = "block";
        }
    }
});
