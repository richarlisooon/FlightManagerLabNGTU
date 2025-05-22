function navigateTo(section) {
    const token = localStorage.getItem('authToken');
    if (!token) {
        window.location.href = '/html/StartPage.html';
        return;
    }
    let pagePath;
    switch(section) {
        case 'planes':
            pagePath = '/html/PlanePage.html';
            break;
        case 'airports':
            pagePath = '/html/AirportPage.html';
            break;
        case 'flights':
            pagePath = '/html/FlightPage.html';
            break;
        case 'dispatchers':
            pagePath = '/html/DispatcherPage.html';
            break;
        default:
            console.error('Unknown section:', section);
            return;
    }

    window.location.href = pagePath;
}
function logout() {
    localStorage.removeItem('authToken');
    window.location.href = '../html/StartPage.html';
}

document.addEventListener('DOMContentLoaded', function() {
    const token = localStorage.getItem('authToken');
    if (!token) {
        window.location.href = '../html/StartPage.html';
    }
});
let timeUpdateInterval;

document.addEventListener('DOMContentLoaded', function() {
    loadCurrentTime();
    timeUpdateInterval = setInterval(loadCurrentTime, 1000);
});

async function loadCurrentTime() {
    try {
        const response = await fetch('http://localhost:8080/api/time/get', {
            method: 'GET',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) throw new Error('Failed to load time');

        const currentTime = parseInt(await response.text());
        document.getElementById('currentTime').textContent = formatUnixTime(currentTime);
    } catch (error) {
        console.error('Error loading time:', error);
    }
}

function formatUnixTime(timestamp) {
    const date = new Date(timestamp * 1000);
    return date.toLocaleString('ru-RU', {
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        day: '2-digit',
        month: '2-digit',
        year: 'numeric'
    });
}


function openTimeModal() {
    document.getElementById('timeModal').style.display = 'block';
}

function closeTimeModal() {
    document.getElementById('timeModal').style.display = 'none';
}

async function skipTime() {
    const hours = document.getElementById('skipHours').value;
    if (!hours || hours < 1) {
        alert('Please enter valid number of hours');
        return;
    }

    try {
        const response = await fetch(`http://localhost:8080/api/time/skip?skip=${hours * 3600}`, {
            method: 'POST',
            headers: {
                'Authorization': localStorage.getItem('authToken')
            }
        });

        if (!response.ok) throw new Error('Failed to skip time');

        closeTimeModal();
        loadCurrentTime();
        alert(`Time skipped by ${hours} hours`);
    } catch (error) {
        console.error('Error skipping time:', error);
        alert('Error: ' + error.message);
    }
}


window.addEventListener('beforeunload', function() {
    clearInterval(timeUpdateInterval);
});