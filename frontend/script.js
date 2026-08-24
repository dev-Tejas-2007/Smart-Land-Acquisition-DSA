// ==========================================
// LANDWISE - Dashboard JavaScript
// ==========================================


// LIVE CLOCK

function updateTime() {

    const now = new Date();

    const time = now.toLocaleTimeString("en-IN", {
        hour: "2-digit",
        minute: "2-digit",
        second: "2-digit"
    });

    const syncTime = document.getElementById("syncTime");

    if (syncTime) {
        syncTime.textContent =
            "Last synchronized: " + time;
    }
}

setInterval(updateTime, 1000);
updateTime();


// SIDEBAR NAVIGATION

const navLinks = document.querySelectorAll("nav a");

navLinks.forEach(link => {

    link.addEventListener("click", function(event) {

        event.preventDefault();

        navLinks.forEach(item => {
            item.classList.remove("active");
        });

        this.classList.add("active");

        console.log(
            "Navigation:",
            this.innerText.trim()
        );
    });
});


// SEARCH

const searchButton =
    document.getElementById("searchBtn");

if (searchButton) {

    searchButton.addEventListener("click", function() {

        const surveyNumber = prompt(
            "Enter Survey Number to search:"
        );

        if (
            surveyNumber &&
            surveyNumber.trim() !== ""
        ) {

            alert(
                "LANDWISE SEARCH ENGINE\n\n" +
                "Searching for: " +
                surveyNumber +
                "\n\n" +
                "DSA Algorithm: Hash Table\n" +
                "Average Search Complexity: O(1)"
            );
        }
    });
}


// NOTIFICATIONS

const notificationButton =
    document.getElementById("notificationBtn");

if (notificationButton) {

    notificationButton.addEventListener("click", function() {

        alert(
            "LANDWISE ALERTS\n\n" +
            "🔴 3 critical land cases\n" +
            "🟡 17 cases approaching deadline\n" +
            "🟢 42 compensation payments processed"
        );
    });
}


// MAP

const mapButton =
    document.getElementById("mapBtn");

if (mapButton) {

    mapButton.addEventListener("click", function() {

        alert(
            "NATIONAL GIS MAP\n\n" +
            "The GIS module will display:\n\n" +
            "• Acquired land parcels\n" +
            "• Pending parcels\n" +
            "• Critical cases\n" +
            "• Project boundaries\n" +
            "• Connected locations"
        );
    });
}


// DSA ENGINE

const dsaButton =
    document.getElementById("dsaBtn");

if (dsaButton) {

    dsaButton.addEventListener("click", function() {

        const choice = prompt(
            "LANDWISE DSA ENGINE\n\n" +
            "Select Algorithm:\n\n" +
            "1 → Hash Search\n" +
            "2 → Priority Queue\n" +
            "3 → Dijkstra Shortest Path\n" +
            "4 → BFS / DFS\n\n" +
            "Enter number:"
        );


        switch (choice) {

            case "1":

                alert(
                    "HASH SEARCH\n\n" +
                    "Data Structure: Hash Table\n" +
                    "Average Complexity: O(1)\n\n" +
                    "Used for rapid land-record lookup."
                );

                break;


            case "2":

                alert(
                    "PRIORITY QUEUE\n\n" +
                    "Data Structure: Max Heap\n" +
                    "Insertion: O(log n)\n" +
                    "Deletion: O(log n)\n\n" +
                    "Used for urgent case prioritization."
                );

                break;


            case "3":

                alert(
                    "DIJKSTRA ALGORITHM\n\n" +
                    "Complexity: O(E log V)\n\n" +
                    "Used for shortest route calculation."
                );

                break;


            case "4":

                alert(
                    "GRAPH TRAVERSAL\n\n" +
                    "Algorithms: BFS / DFS\n" +
                    "Complexity: O(V + E)\n\n" +
                    "Used for connected land and project analysis."
                );

                break;


            default:

                alert(
                    "Please select a valid option."
                );
        }
    });
}


// PROGRESS BAR ANIMATION

const progressBars =
    document.querySelectorAll(".progress-bar div");

progressBars.forEach(bar => {

    const finalWidth = bar.style.width;

    bar.style.width = "0%";

    setTimeout(() => {

        bar.style.transition =
            "width 1.2s ease";

        bar.style.width = finalWidth;

    }, 300);
});


// PRIORITY CASE DETAILS

const priorityItems =
    document.querySelectorAll(".priority-item");

priorityItems.forEach(item => {

    item.addEventListener("click", function() {

        const caseNumber =
            this.querySelector(
                ".case-info strong"
            )?.innerText;

        const score =
            this.querySelector(
                ".score strong"
            )?.innerText;

        alert(
            "CASE DETAILS\n\n" +
            "Case: " + caseNumber + "\n" +
            "Priority Score: " + score + "\n\n" +
            "Priority calculated using:\n" +
            "• Deadline proximity\n" +
            "• Project impact\n" +
            "• Compensation status\n" +
            "• Acquisition urgency"
        );
    });
});


// CONSOLE INFORMATION

console.log(
    "%cLANDWISE DSA ENGINE INITIALIZED",
    "color:#5ee59b;font-size:16px;font-weight:bold;"
);

console.log("Hash Search → O(1)");
console.log("Priority Queue → O(log n)");
console.log("Dijkstra → O(E log V)");
console.log("BFS / DFS → O(V + E)");