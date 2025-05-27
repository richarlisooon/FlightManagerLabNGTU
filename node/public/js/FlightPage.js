let flights = [];
let currentAction = 'add';

document.addEventListener('DOMContentLoaded', function() {
    loadFlights();

    document.getElementById('flightForm').addEventListener('submit', function(e) {
        e.preventDefault();
        if (currentAction === 'add') {
            createFlight();
        }
    });
});


async function loadFlights() {
    try {
        const response = await fetch('http://localhost:8080/api/flights/getAll', {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        flights = await response.json();
        renderFlights();
    } catch (error) {
        console.error('Error loading flights:', error);
        alert('Failed to load flights: ' + error.message);
    }
}

function renderFlights() {
    const tableBody = document.getElementById('flightTableBody');
    tableBody.innerHTML = '';

    flights.forEach(flight => {
        const row = document.createElement('tr');

        row.innerHTML = `
            <td>${flight.id}</td>
            <td>${flight.dispatcherId}</td>
            <td>${flight.airportId}</td>
            <td>${flight.planeId}</td>
            <td>${formatTimestamp(flight.timestampStart)}</td>
            <td>${formatTimestamp(flight.timestampEnd)}</td>
        `;

        tableBody.appendChild(row);
    });
}

function formatTimestamp(timestamp) {
    if (!timestamp) return 'N/A';
    return new Date(timestamp * 1000).toLocaleString();
}

function openAddModal() {
    currentAction = 'add';
    document.getElementById('modalTitle').textContent = 'Add New Flight';
    document.getElementById('flightForm').reset();
    document.getElementById('flightId').value = '';
    document.getElementById('flightModal').style.display = 'block';
}

function closeModal() {
    document.getElementById('flightModal').style.display = 'none';
}

async function createFlight() {
    try {
        const flight = {
            dispatcherId: parseInt(document.getElementById('dispatcherId').value),
            airportId: parseInt(document.getElementById('airportId').value),
            planeId: parseInt(document.getElementById('planeId').value),
            timestampStart: 0,
            timestampEnd: 0,
        };

        const response = await fetch('http://localhost:8080/api/flights/create', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(flight)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        await loadFlights();
        alert('Flight created successfully!');
    } catch (error) {
        console.error('Error creating flight:', error);
        alert('Failed to create flight: ' + error.message);
    }
}
function logout() {
    localStorage.removeItem('authToken');
    window.location.href = '/html/LoginPage.html';
}