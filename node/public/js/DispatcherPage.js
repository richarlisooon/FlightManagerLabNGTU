let dispatchers = [];
let currentAction = 'view';
let currentUserId = null;

document.addEventListener('DOMContentLoaded', async function() {
    await loadCurrentDispatcher();
    await loadAllDispatchers();

    document.getElementById('dispatcherForm').addEventListener('submit', function(e) {
        e.preventDefault();
        updateDispatcher();
    });
});

async function searchDispatcher() {
    const searchId = document.getElementById('search').value;
    if (!searchId) {
        await loadAllDispatchers();
        return;
    }

    try {
        const response = await fetch(`http://localhost:8080/api/dispatcher/get?id=${searchId}`, {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) throw new Error('Dispatcher not found');

        const dispatcher = await response.json();
        dispatchers = [dispatcher];
        renderDispatchers();

    } catch (error) {
        console.error('Search error:', error);
        alert('Error: ' + error.message);
        await loadAllDispatchers();
    }
}

async function loadAllDispatchers() {
    try {
        const response = await fetch('http://localhost:8080/api/dispatcher/getAll', {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (response.status === 401) {
            await loadCurrentDispatcher();
            return;
        }

        if (!response.ok) throw new Error('Failed to load dispatchers');
        document.getElementById('searchCont').style.display='';
        dispatchers = await response.json();
        renderDispatchers();
    } catch (error) {
        console.error('Error loading dispatchers:', error);
        alert('Loading error: ' + error.message);
    }
}

async function loadCurrentDispatcher() {
    currentUserId = localStorage.getItem("userId");
    if (!currentUserId) return;

    try {
        const response = await fetch(`http://localhost:8080/api/dispatcher/get?id=${currentUserId}`, {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) throw new Error('Failed to load current dispatcher');

        const dispatcher = await response.json();
        dispatchers = [dispatcher];
        renderDispatchers();

    } catch (error) {
        console.error('Error loading current dispatcher:', error);
        alert('Loading error: ' + error.message);
    }
}

function renderDispatchers() {
    const tableBody = document.getElementById('dispatcherTableBody');
    tableBody.innerHTML = '';

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
        document.getElementById('dispatcherModal').style.display = 'block';
    }
}

function closeModal() {
    document.getElementById('dispatcherModal').style.display = 'none';
}

async function updateDispatcher() {
    const id = document.getElementById('dispatcherId').value;
    const updateParams = "firstName,lastName,email,password";

    const dispatcher = {
        id: parseInt(id),
        firstName: document.getElementById('dispatcherFirstName').value,
        lastName: document.getElementById('dispatcherLastName').value,
        email: document.getElementById('dispatcherEmail').value,
        password: document.getElementById('dispatcherPassword').value !== '********'
            ? document.getElementById('dispatcherPassword').value
            : undefined
    };

    try {
        const response = await fetch(`http://localhost:8080/api/dispatcher/update?update=${updateParams}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': localStorage.getItem('authToken')
            },
            body: JSON.stringify(dispatcher)
        });

        if (!response.ok) {
            const errorData = await response.json();
            throw new Error(errorData.message || 'Update failed');
        }

        closeModal();
        await loadAllDispatchers();
        alert('Dispatcher updated successfully!');
    } catch (error) {
        console.error('Update error:', error);
        alert('Update error: ' + error.message);
    }
}

function logout() {
    localStorage.removeItem('authToken');
    window.location.href = '/html/StartPage.html';
}