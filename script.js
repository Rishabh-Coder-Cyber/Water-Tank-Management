import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-analytics.js";
import { getDatabase, ref, onValue, set} from "https://www.gstatic.com/firebasejs/10.13.0/firebase-database.js";

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyDaqyBSqjt3DY0HP_f8rnTPbRJO_KoAp_Y",
    authDomain: "water-flow-management.firebaseapp.com",
    databaseURL: "https://water-flow-management-default-rtdb.firebaseio.com",
    projectId: "water-flow-management",
    storageBucket: "water-flow-management.appspot.com",
    messagingSenderId: "1037671472023",
    appId: "1:1037671472023:web:9bd0a6c35da02eeff7c2d2",
    measurementId: "G-GGDVND0MDT"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const database = getDatabase(app);

const waterLevelRef = ref(database, 'Data/WaterLevel');

// Listen for changes to the WaterLevel data
onValue(waterLevelRef, (snapshot) => {
    const waterLevel = snapshot.val();
    document.getElementById('water-level').innerText = `Water Level: ${waterLevel}`;
    
    // Ensure the value is within 0 to 100 range
    const percentage = waterLevel;
    const strokeDasharray = `${percentage}, ${100 - percentage}`;
    
    const progressCircle = document.getElementById('circle');
    const percentageText = document.getElementById('percentage');
    
    // Update SVG
    if (progressCircle && percentageText) {
        percentageText.innerHTML = `${percentage}%`;
        progressCircle.setAttribute('stroke-dasharray', strokeDasharray);
    } else {
        console.error("SVG elements not found.");
    }
});

const waterLevelRefSwitch = ref(database, 'Control/Switch');

document.getElementById('turn_on').addEventListener('click', (event) => {
    event.preventDefault(); // Prevent the form from submitting the default way

    // const waterLevelInput = document.getElementById('water-level-input').value;
    const waterLevel = "on";

    
        // Write data to Firebase
        set(waterLevelRefSwitch, waterLevel)
            .then(() => {
                console.log('Water level updated successfully.');
            })
            .catch((error) => {
                console.error('Error updating water level:', error);
            });
    
});