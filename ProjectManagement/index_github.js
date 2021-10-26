// Valid fetch command that returns text from zen api
//fetch("https://api.github.com/zen")
//    .then(response => response.text().then(text => console.log(text)));
function main() {
    const url =  "https://api.github.com/repos/krisUnderhill/TeamSediSensor/issues";
    const Init = {
        method: 'GET',
        headers: {
            Authorization: "token ***Github Auth Token" // Replace with actual token
        },
        mode: 'cors',
        cache: 'default'
    };
    DrawNavBar()

    fetch(url, Init)
        .then(response => response.json().then(json => DrawGanttTasks(json)));
}
    
function DrawNavBar() {
    const header = document.getElementById("navBar");
    header.classList.add("nav-header-container")
    const navMenus = ["Project", "Documentation"]
    // Draw Img
    const logoDiv = document.getElementById("logo");
    logoDiv.classList.add("nav-header-elem");
    const logoLink = document.createElement("a");
    logoLink.href = "index.html";
    const logo = document.createElement("img");
    logo.src = "TSS_Logo.png";
    logo.width = 60;
    logo.height = 80;
    logo.alt = "TSS_Logo, Credit: Moses Yang";
    logoLink.appendChild(logo);
    logoDiv.appendChild(logoLink);
    // Draw Nav Items
    const navDiv = document.getElementById("nav");
    const nav = document.createElement("nav");
    navDiv.appendChild(nav);
            
    navMenus.forEach(menuItem => {
        var navMenuLink = document.createElement("a");
        navMenuLink.href = menuItem + ".html"; //TODO: Fix once there are more than one html
        navMenuLink.innerHTML = menuItem;
        navMenuLink.classList.add("nav-elem");
        nav.appendChild(navMenuLink);
    })
}

function DrawGanttTasks(tasksJson) {
    const table = document.getElementById("tasksDisplay_Div");
    days = genDates()
    var firstRow = document.createElement("tr");
    var emptyCell = document.createElement("td");
    firstRow.appendChild(emptyCell);
    days.forEach(day => {
        var dateCell = document.createElement("td");
        var dateDiv = document.createElement("div");
        dateDiv.innerHTML = day;
        dateDiv.classList.add("gantt-table-cell-date");
        dateCell.appendChild(dateDiv);
        firstRow.appendChild(dateCell);
    });
    table.appendChild(firstRow);

    tasksJson.forEach(task => {
        var row = document.createElement("tr")
        var task_cell = document.createElement("td");
        task_cell.innerHTML = task.title;
        task_cell.classList.add("gantt-table-cell-task")
        row.appendChild(task_cell);
        days.forEach(day => {
            var cell = document.createElement("td");
            var div = document.createElement("div");
            cell.appendChild(div);
            cell.classList.add("gantt-table-cell-center");
            row.appendChild(cell);
        });
        table.appendChild(row);
    });
}

function genDates() {
    let done = false; let startWeek = false;
    let dayHeaders = [];
    let day = new Date(); let dayNum = 0; let dateNum = 0;
    while(!done){
        // TODO: Decide whether or not to set day based on current day or beginning of tasks
        // should probably set on tasks -- that would be more general
        if(startWeek){
            dayHeaders.push((day.getMonth() + 1) + '/' + day.getDate())
            // Increment Date
            day.setDate(dateNum+=7);
            if(day.getDate() < dateNum){
                dateNum = day.getDate();
            }
        } 
        else {
            // Set tracking Numbers
            dayNum = day.getDay(); 
            dateNum = day.getDate();
            // Set Day to Monday to start drawing stuff
            if(dayNum === 0) { day.setDate(++dateNum) } // sun => mon   
            else if (dayNum === 1) { /* Mon -- skip*/ }
            else { day.setDate(dateNum - (dayNum-1)) } // >Mon => mon before , Test on Tues etc
            // Set to Draw, aligned dates
            startWeek = true;
        }
        if (day.getMonth() === 0) { // Index at 0 => 0 === until Jan
            done = true;
        }
    }
    return dayHeaders;
}
    
main()

