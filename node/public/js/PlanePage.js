let planes = [];
let currentAction = 'add';
let planeUpdateInterval;

document.addEventListener('DOMContentLoaded', function() {
    loadPlanes();
    planeUpdateInterval = setInterval(loadPlanes, 1000);

    document.getElementById('planeForm').addEventListener('submit', function(e) {
        e.preventDefault();
        if (currentAction === 'add') {
            createPlane();
        } else {
            updatePlane();
        }
    });
});

window.addEventListener('beforeunload', function() {
    clearInterval(planeUpdateInterval);
});

async function loadPlanes() {
    try {
        const response = await fetch('http://localhost:8080/api/plane/getAll', {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        planes = await response.json();
        renderPlanes();
    } catch (error) {
        console.error('Error loading planes:', error);
        alert('Failed to load planes: ' + error.message);
    }
}

async function createPlane() {
    try {
        const plane = {
            name: document.getElementById('planeName').value,
            pilot: document.getElementById('planePilot').value,
            builtYear: parseInt(document.getElementById('planeBuiltYear').value),
            speed: parseInt(document.getElementById('planeSpeed').value),
            minAirportSize: parseInt(document.getElementById('planeMinSize').value),
        };

        const response = await fetch('http://localhost:8080/api/plane/create', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(plane)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        await loadPlanes();
    } catch (error) {
        console.error('Error creating plane:', error);
        alert('Failed to create plane: ' + error.message);
    }
}

async function updatePlane() {
    try {
        const id = document.getElementById('planeId').value;
        const updateParams = "name,pilot,builtYear,speed,minAirportSize";
        const plane = {
            id: parseInt(id),
            name: document.getElementById('planeName').value,
            pilot: document.getElementById('planePilot').value,
            builtYear: parseInt(document.getElementById('planeBuiltYear').value),
            speed: parseInt(document.getElementById('planeSpeed').value),
            minAirportSize: parseInt(document.getElementById('planeMinSize').value)
        };

        const response = await fetch(`http://localhost:8080/api/plane/update?update=${updateParams}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(plane)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        await loadPlanes();
    } catch (error) {
        console.error('Error updating plane:', error);
        alert('Failed to update plane: ' + error.message);
    }
}

async function deletePlane(id) {
    if (!confirm('Are you sure you want to delete this plane?')) return;

    try {
        const response = await fetch(`http://localhost:8080/api/plane/delete?id=${id}`, {
            method: 'DELETE',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        await loadPlanes();
    } catch (error) {
        console.error('Error deleting plane:', error);
        alert('Failed to delete plane: ' + error.message);
    }
}

function renderPlanes() {
    const tableBody = document.getElementById('planeTableBody');
    tableBody.innerHTML = '';

    planes.forEach(plane => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${plane.id}</td>
            <td>${plane.name}</td>
            <td>${plane.pilot}</td>
            <td>${plane.builtYear}</td>
            <td>${plane.speed}</td>
            <td>${plane.minAirportSize}</td>
            <td>${plane.brokenPercentage}</td>
            <td class="coordinates-cell">
                <span class="coordinates">${plane.x}, ${plane.y}</span>
            </td>
            <td>
                <button class="action-btn edit-btn" onclick="openEditModal(${plane.id})">
                    <i class="fas fa-edit"></i> Edit
                </button>
                <button class="action-btn delete-btn" onclick="deletePlane(${plane.id})">
                    <i class="fas fa-trash"></i> Delete
                </button>
            </td>
        `;
        tableBody.appendChild(row);
    });
}

function openAddModal() {
    currentAction = 'add';
    document.getElementById('modalTitle').textContent = 'Add New Plane';
    document.getElementById('planeForm').reset();
    document.getElementById('planeId').value = '';
    document.getElementById('planeModal').style.display = 'block';
}

function openEditModal(id) {
    currentAction = 'edit';
    const plane = planes.find(p => p.id === id);

    if (plane) {
        document.getElementById('modalTitle').textContent = 'Edit Plane';
        document.getElementById('planeId').value = plane.id;
        document.getElementById('planeName').value = plane.name;
        document.getElementById('planePilot').value = plane.pilot;
        document.getElementById('planeBuiltYear').value = plane.builtYear;
        document.getElementById('planeSpeed').value = plane.speed;
        document.getElementById('planeMinSize').value = plane.minAirportSize;
        document.getElementById('planeModal').style.display = 'block';
    }
}

function closeModal() {
    document.getElementById('planeModal').style.display = 'none';
}

function logout() {
    localStorage.removeItem('authToken');
    window.location.href = '/html/StartPage.html';
}
