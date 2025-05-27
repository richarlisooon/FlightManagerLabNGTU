let airports = [];
let currentAction = 'add';

document.addEventListener('DOMContentLoaded', function() {
    loadAirports();

    document.getElementById('airportForm').addEventListener('submit', function(e) {
        e.preventDefault();
        if (currentAction === 'add') {
            createAirport();
        } else {
            updateAirport();
        }
    });
});

async function loadAirports() {
    try {
        const response = await fetch('http://localhost:8080/api/airport/getAll', {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        airports = await response.json();
        renderAirports();
    } catch (error) {
        console.error('Error loading airports:', error);
        alert('Failed to load airports: ' + error.message);
    }
}

function renderAirports() {
    const tableBody = document.getElementById('airportTableBody');
    tableBody.innerHTML = '';

    airports.forEach(airport => {
        const row = document.createElement('tr');

        row.innerHTML = `
                <td>${airport.id}</td>
                <td>${airport.name}</td>
                <td>${airport.size}</td>
                <td>${airport.x}</td>
                <td>${airport.y}</td>
                <td>
                    <button class="action-btn edit-btn" onclick="openEditModal(${airport.id})">
                        <i class="fas fa-edit"></i> Edit
                    </button>
                    <button class="action-btn delete-btn" onclick="deleteAirport(${airport.id})">
                        <i class="fas fa-trash"></i> Delete
                    </button>
                </td>
            `;

        tableBody.appendChild(row);
    });
}

function openAddModal() {
    currentAction = 'add';
    document.getElementById('modalTitle').textContent = 'Add New Airport';
    document.getElementById('airportForm').reset();
    document.getElementById('airportId').value = '';
    document.getElementById('airportModal').style.display = 'block';
}

function openEditModal(id) {
    currentAction = 'edit';
    const airport = airports.find(a => a.id === id);

    if (airport) {
        document.getElementById('modalTitle').textContent = 'Edit Airport';
        document.getElementById('airportId').value = airport.id;
        document.getElementById('airportName').value = airport.name;
        document.getElementById('airportSize').value = airport.size;
        document.getElementById('airportX').value = airport.x;
        document.getElementById('airportY').value = airport.y;
        document.getElementById('airportModal').style.display = 'block';
    }
}

function closeModal() {
    document.getElementById('airportModal').style.display = 'none';
}

async function createAirport() {
    const airport = {
        name: document.getElementById('airportName').value,
        size: parseInt(document.getElementById('airportSize').value),
        x: parseInt(document.getElementById('airportX').value),
        y: parseInt(document.getElementById('airportY').value)
    };

    try {
        const response = await fetch('http://localhost:8080/api/airport/create', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(airport)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        loadAirports();
        alert('Airport created successfully!');
    } catch (error) {
        console.error('Error creating airport:', error);
        alert('Failed to create airport: ' + error.message);
    }
}

async function updateAirport() {
    const id = document.getElementById('airportId').value;
    const airport = {
        id: parseInt(id),
        name: document.getElementById('airportName').value,
        size: parseInt(document.getElementById('airportSize').value),
        x: parseInt(document.getElementById('airportX').value),
        y: parseInt(document.getElementById('airportY').value)
    };
    const updateParams = "name,size,x,y";

    try {
        const response = await fetch(`http://localhost:8080/api/airport/update?update=${updateParams}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(airport)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        await loadAirports();
        alert('Airport updated successfully!');
    } catch (error) {
        console.error('Error updating airport:', error);
        alert('Failed to update airport: ' + error.message);
    }
}

async function deleteAirport(id) {
    if (!confirm('Are you sure you want to delete this airport?')) return;

    try {
        const response = await fetch(`http://localhost:8080/api/airport/delete?id=${id}`, {
            method: 'DELETE',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        loadAirports();
        alert('Airport deleted successfully!');
    } catch (error) {
        console.error('Error deleting airport:', error);
        alert('Failed to delete airport: ' + error.message);
    }
}

function logout() {
    localStorage.removeItem('authToken');
    window.location.href = '/html/StartPage.html';
}