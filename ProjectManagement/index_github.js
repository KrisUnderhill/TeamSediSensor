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
    const dispWidth  = 800; // TODO: Make this more general
    const dispHeight = 600;
    console.log(tasksJson);
    d3.select("svg#tasksDisplay")
        .attr("width", dispWidth)
        .attr("height", dispHeight)
    var lastx = 25;
    var lasty = 50;
    var maxNameLen = 200;
    var boxX = 25;
    var boxY = 25;
    let svg; let text;
    let firstIter = true;
    var nIter = 0;
    tasksJson.forEach(d => {
        svg = d3.select("svg#tasksDisplay");
        // Draw rectangles + text
        svg.append('rect')
            .attr('x', lastx)
            .attr('y', lasty)
            .attr('width', maxNameLen)
            .attr('height', boxY)
            .attr('stroke', 'whitesmoke')
            .attr('stroke-width', 2)
        text = svg.append('text').text(d.title)
            .attr('x', lastx + 5)
            .attr('y', lasty + 20)
            .attr('font-family', 'Noto Sans HK, sans-serif')
            .attr('font-size', 12)
            .attr('fill', "whitesmoke")
        lastx += maxNameLen;
        if(firstIter) {
            nIter = drawSVGDates(svg, lastx, lasty);
            firstIter = false;
        }
        for(let i=0; i<nIter; i++){
            svg.append('rect')
                .attr('x', lastx)
                .attr('y', lasty)
                .attr('width' , boxX)
                .attr('height', boxY)
                .attr('stroke', 'whitesmoke')
                .attr('stroke-width', 2)
            lastx += boxX;
        }
        lastx = 25; // Reset
        lasty+=boxY;
    });
}

function drawSVGDates(svg, lastx, lasty) {
    let boxX = 25; // TODO: Make a better way to pass variables
    let done = false; let startWeek = false;
    let count = 0;
    let day = new Date(); let dayNum = 0; let dateNum = 0;
    while(!done){
        // TODO: Decide whether or not to set day based on current day or beginning of tasks
        if(startWeek){
            text = svg.append('text').text((day.getMonth() + 1) + '/' + day.getDate())
                .attr('x', lastx - 15) // Since we take the first loop iteration to set the date
                                       // it starts drawing boxes, decrement the x position to put 
                                       // it in the right spots, This solution needs to be improved TODO
                .attr('y', lasty - 5)
                .attr('font-family', 'Noto Sans HK, sans-serif')
                .attr('font-size', 12)
                .attr('fill', "whitesmoke")
                .attr("transform", "rotate(-45,"+(lastx-15)+","+(lasty-5)+")")  // AW c'mon js has to have a better way for formatting strings than this TODO
            // Increment Date
            day.setDate(dateNum+=7);
            if(day.getDate() < dateNum){
                dateNum = day.getDate();
            }
            count++;
        } 
        else {
            // Set tracking Numbers
            dayNum = day.getDay(); 
            dateNum = day.getDate();
            // Set Day to Monday to start drawing stuff
            if(dayNum === 0) { day.setDate(++dateNum) } // sun => mon   
            else if (dayNum === 1) { /* Mon -- skip*/ }
            // TODO: Decide whether this should set to next monday or monday before
            else { day.setDate(dateNum + (8-dayNum)) } // >Mon => Next mon, Test on Tues etc
            // Set to Draw, aligned dates
            startWeek = true;
        }
        if (day.getMonth() === 0) { // Index at 0 => 11 === Jan
            done = true;
        }
        lastx += boxX
    }
    return count;
}
    
main()

