// ======================================================
// LANDWISE - FINAL DASHBOARD JAVASCRIPT
// ======================================================

document.addEventListener("DOMContentLoaded", () => {

    // ==================================================
    // LIVE TIME
    // ==================================================

    function updateTime() {

        const now = new Date();

        const time = now.toLocaleTimeString("en-IN", {
            hour: "2-digit",
            minute: "2-digit",
            second: "2-digit"
        });

        const footer = document.querySelector("#syncTime");

        if (footer) {
            footer.textContent = "Last synchronized: " + time;
        }
    }

    updateTime();
    setInterval(updateTime, 1000);


    // ==================================================
    // SIDEBAR NAVIGATION
    // ==================================================

    const navLinks = document.querySelectorAll("nav a");

    const pages = document.querySelectorAll(".page-section");

    function hideAllPages() {

        pages.forEach(page => {
            page.classList.remove("active-page");
        });
    }

    navLinks.forEach(link => {

        link.addEventListener("click", function (event) {

            event.preventDefault();

            navLinks.forEach(item => {
                item.classList.remove("active");
            });

            this.classList.add("active");

            const pageName =
                this.innerText.trim().toLowerCase();

            hideAllPages();

            // If extra pages exist
            if (pageName.includes("land records")) {

                const page =
                    document.querySelector("#landRecordsPage");

                if (page) page.classList.add("active-page");

            } else if (pageName.includes("project map")) {

                const page =
                    document.querySelector("#mapPage");

                if (page) page.classList.add("active-page");

            } else if (pageName.includes("priority")) {

                const page =
                    document.querySelector("#priorityPage");

                if (page) page.classList.add("active-page");

            } else if (pageName.includes("analytics")) {

                const page =
                    document.querySelector("#analyticsPage");

                if (page) page.classList.add("active-page");

            } else if (pageName.includes("reports")) {

                const page =
                    document.querySelector("#reportsPage");

                if (page) page.classList.add("active-page");

            }

            console.log("Opened:", pageName);
        });

    });


    // ==================================================
    // SEARCH
    // ==================================================

    const searchButton =
        document.querySelector("#searchBtn");

    if (searchButton) {

        searchButton.addEventListener("click", () => {

            const surveyNumber =
                prompt("Enter Survey Number:");

            if (!surveyNumber ||
                surveyNumber.trim() === "") {
                return;
            }

            alert(
                "LANDWISE SEARCH\n\n" +
                "Survey Number: " +
                surveyNumber +
                "\n\n" +
                "Searching land records...\n\n" +
                "DSA: Hash Table\n" +
                "Average Complexity: O(1)"
            );

        });
    }


    // ==================================================
    // NOTIFICATION
    // ==================================================

    const notificationButton =
        document.querySelector("#notificationBtn");

    if (notificationButton) {

        notificationButton.addEventListener("click", () => {

            alert(
                "LANDWISE ALERT CENTER\n\n" +
                "🔴 3 critical land cases\n\n" +
                "🟡 17 cases approaching deadline\n\n" +
                "🟢 42 compensation payments processed"
            );

        });

    }


    // ==================================================
    // MAP BUTTON
    // ==================================================

    const mapButton =
        document.querySelector("#mapBtn");

    if (mapButton) {

        mapButton.addEventListener("click", () => {

            const mapPage =
                document.querySelector("#mapPage");

            if (mapPage) {

                hideAllPages();

                mapPage.classList.add("active-page");

                navLinks.forEach(link => {

                    link.classList.remove("active");

                    if (
                        link.innerText
                            .toLowerCase()
                            .includes("project map")
                    ) {
                        link.classList.add("active");
                    }

                });

                window.scrollTo({
                    top: 0,
                    behavior: "smooth"
                });

            } else {

                alert(
                    "NATIONAL GIS MAP\n\n" +
                    "Acquired parcels\n" +
                    "Pending parcels\n" +
                    "Critical cases\n" +
                    "Project boundaries\n" +
                    "Connected locations"
                );

            }

        });

    }


    // ==================================================
    // DSA ENGINE
    // ==================================================

    const dsaButton =
        document.querySelector("#dsaBtn");

    if (dsaButton) {

        dsaButton.addEventListener("click", () => {

            const choice = prompt(
                "LANDWISE DSA ENGINE\n\n" +
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
                        "Used to calculate shortest routes\n" +
                        "between project locations."
                    );

                    break;


                case "4":

                    alert(
                        "GRAPH TRAVERSAL\n\n" +
                        "BFS / DFS\n\n" +
                        "Complexity: O(V + E)\n\n" +
                        "Used to identify connected\n" +
                        "land parcels and dependencies."
                    );

                    break;


                default:

                    alert(
                        "Please select a valid option."
                    );

            }

        });

    }


    // ==================================================
    // PRIORITY CARDS
    // ==================================================

    const priorityItems =
        document.querySelectorAll(".priority-item");

    priorityItems.forEach(item => {

        item.addEventListener("click", () => {

            const caseNumber =
                item.querySelector(
                    ".case-info strong"
                )?.innerText || "Unknown";

            const score =
                item.querySelector(
                    ".score strong"
                )?.innerText || "0";

            alert(
                "CASE DETAILS\n\n" +
                "Case: " + caseNumber +
                "\n" +
                "Priority Score: " + score +
                "\n\n" +
                "Priority calculated using:\n" +
                "• Deadline proximity\n" +
                "• Project impact\n" +
                "• Compensation status\n" +
                "• Acquisition urgency"
            );

        });

    });


    // ==================================================
    // PROGRESS BAR ANIMATION
    // ==================================================

    const progressBars =
        document.querySelectorAll(
            ".progress-bar div"
        );

    progressBars.forEach(bar => {

        const finalWidth =
            bar.style.width;

        bar.style.width = "0%";

        setTimeout(() => {

            bar.style.transition =
                "width 1.2s ease";

            bar.style.width =
                finalWidth;

        }, 300);

    });


    // ==================================================
    // STAT CARD CLICK
    // ==================================================

    const statCards =
        document.querySelectorAll(".stat-card");

    statCards.forEach(card => {

        card.addEventListener("click", () => {

            const title =
                card.querySelector(
                    ".stat-top span"
                )?.innerText;

            const value =
                card.querySelector(
                    "h2"
                )?.innerText;

            if (title && value) {

                console.log(
                    "Selected:",
                    title,
                    value
                );

            }

        });

    });


    // ==================================================
    // KEYBOARD SHORTCUTS
    // ==================================================

    document.addEventListener("keydown", event => {

        // "/" opens search
        if (
            event.key === "/" &&
            document.activeElement.tagName !== "INPUT"
        ) {

            event.preventDefault();

            if (searchButton) {
                searchButton.click();
            }

        }

        // Escape
        if (event.key === "Escape") {

            console.log(
                "LANDWISE: Escape pressed"
            );

        }

    });


    // ==================================================
    // CONSOLE
    // ==================================================

    console.log(
        "%cLANDWISE DSA ENGINE READY",
        "color:#35d889;font-size:16px;font-weight:700;"
    );

    console.log(
        "Hash Search → O(1)"
    );

    console.log(
        "Priority Queue → O(log n)"
    );

    console.log(
        "Dijkstra → O(E log V)"
    );

    console.log(
        "BFS / DFS → O(V + E)"
    );

});