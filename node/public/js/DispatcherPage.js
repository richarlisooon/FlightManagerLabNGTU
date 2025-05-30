let dispatchers = [];
let currentAction = 'view';
let currentUserId = null;

document.addEventListener('DOMContentLoaded', async function() {
    try {
        await loadCurrentDispatcher();

        if (dispatchers.length > 0 && dispatchers[0].roles && dispatchers[0].roles.includes("ADMIN")) {
            await loadAllDispatchers();
            document.getElementById('searchBtn').addEventListener('click', function() {
                handleApiCall(searchDispatcher, 'search dispatcher');
            });
        }

        document.getElementById('dispatcherForm').addEventListener('submit', function(e) {
            e.preventDefault();
            handleApiCall(updateDispatcher, 'update dispatcher');
            return false;
        });

        document.getElementById('logoutBtn').addEventListener('click', logout);

    } catch (error) {
        console.error('Initialization error:', error);
        alert('Failed to load page: ' + error.message);
    }
});

async function searchDispatcher() {
    const searchId = document.getElementById('search').value;
    if (!searchId) {
        alert("Please enter id to search");
        return;
    }

    try {
        const response = await fetch(`http://localhost:8080/api/dispatcher/get?id=${searchId}`, {
            method: 'GET',
            headers: {
                'Authorization': getAuthToken()
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        const dispatcher = await response.json();
        dispatchers = [dispatcher];
        renderDispatchers();
    } catch (error) {
        console.error('Search error:', error);
        alert('Failed to search dispatcher: ' + error.message);
    }
}

async function loadAllDispatchers() {
    try {
        const response = await fetch('http://localhost:8080/api/dispatcher/getAll', {
            method: 'GET',
            headers: {
                'Authorization': getAuthToken()
            }
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        dispatchers = await response.json();
        document.getElementById('searchCont').style.display = '';
        renderDispatchers();
    } catch (error) {
        console.error('Error loading dispatchers:', error);
        alert('Failed to load dispatchers: ' + error.message);
    }
}

async function updateDispatcher() {
    try {
        const id = document.getElementById('dispatcherId').value;
        const updateParams = "firstName,lastName,email,password";
        const currentDispatcher = dispatchers.find(d => d.id == id);
        const passwordInput = document.getElementById('dispatcherPassword').value;
        const dispatcher = {
            id: parseInt(id),
            firstName: document.getElementById('dispatcherFirstName').value,
            lastName: document.getElementById('dispatcherLastName').value,
            email: document.getElementById('dispatcherEmail').value,
            password: passwordInput && passwordInput !== '********'
                ? passwordInput
                : currentDispatcher.password
        };

        const response = await fetch(`http://localhost:8080/api/dispatcher/update?update=${updateParams}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': getAuthToken()
            },
            body: JSON.stringify(dispatcher)
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        closeModal();
        await loadCurrentDispatcher();

        if (dispatchers.length > 0 && dispatchers[0].roles && dispatchers[0].roles.includes("ADMIN")) {
            await loadAllDispatchers();
        }
        alert('Dispatcher updated successfully!');
    } catch (error) {
        console.error('Error updating dispatcher:', error);
        alert('Failed to update dispatcher: ' + error.message);
    }
}

function getAuthToken() {
    const token = localStorage.getItem('authToken');
    if (!token) {
        throw new Error('No authentication token found');
    }
    return token;
}

function logout() {
    localStorage.removeItem('authToken');
    localStorage.removeItem('userId');
    window.location.href = '/html/StartPage.html';
}

async function loadCurrentDispatcher() {
    currentUserId = localStorage.getItem("userId");
    if (!currentUserId) return;

    try {
        const response = await fetch(`http://localhost:8080/api/dispatcher/get?id=${currentUserId}`, {
            method: 'GET',
            headers: {
                'Authorization': getAuthToken()
            }
        });

        if (!response.ok) throw new Error('Failed to load current dispatcher');

        const dispatcher = await response.json();
        dispatchers = [dispatcher];
        renderDispatchers();

    } catch (error) {
        console.error('Error loading current dispatcher:', error);
        alert('Failed to load current dispatcher: ' + error.message);
    }
}

function renderDispatchers() {
    const tableBody = document.getElementById('dispatcherTableBody');
    tableBody.innerHTML = '';

    if (dispatchers.length === 0) {
        const row = document.createElement('tr');
        row.innerHTML = '<td colspan="6" class="no-data">No dispatchers found</td>';
        tableBody.appendChild(row);
        return;
    }

    dispatchers.forEach(dispatcher => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${dispatcher.id}</td>
            <td>${dispatcher.firstName}</td>
            <td>${dispatcher.lastName}</td>
            <td>${dispatcher.email}</td>
            <td class="password-mask">********</td>
            <td>
                <button class="action-btn edit-btn" onclick="openEditModal(${dispatcher.id})">
                    <i class="fas fa-edit"></i> Edit
                </button>
            </td>
        `;
        tableBody.appendChild(row);
    });
}

function openEditModal(id) {
    currentAction = 'edit';
    const dispatcher = dispatchers.find(d => d.id === id);

    if (dispatcher) {
        document.getElementById('modalTitle').textContent = 'Edit Dispatcher';
        document.getElementById('dispatcherId').value = dispatcher.id;
        document.getElementById('dispatcherFirstName').value = dispatcher.firstName;
        document.getElementById('dispatcherLastName').value = dispatcher.lastName;
        document.getElementById('dispatcherEmail').value = dispatcher.email;
        document.getElementById('dispatcherPassword').value = dispatcher.password;
        document.getElementById('dispatcherModal').style.display = 'block';
    }
}

function closeModal() {
    document.getElementById('dispatcherModal').style.display = 'none';
}

window.openEditModal = openEditModal;
window.closeModal = closeModal;
window.searchDispatcher = searchDispatcher;
window.logout = logout;