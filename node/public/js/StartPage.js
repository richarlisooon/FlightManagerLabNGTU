
function showMainContent() {
    document.getElementById('mainContent').style.display = 'flex';
    document.getElementById('loginForm').style.display = 'none';
    document.getElementById('registerForm').style.display = 'none';
}

function showLoginForm() {
    document.getElementById('mainContent').style.display = 'none';
    document.getElementById('loginForm').style.display = 'flex';
    document.getElementById('registerForm').style.display = 'none';
}

function showRegisterForm() {
    document.getElementById('mainContent').style.display = 'none';
    document.getElementById('loginForm').style.display = 'none';
    document.getElementById('registerForm').style.display = 'flex';
}

document.getElementById('loginFormElement').addEventListener('submit', async function(e) {
    e.preventDefault();

    const email = document.getElementById('loginEmail').value;
    const password = document.getElementById('loginPassword').value;

    try {
        const response = await fetch('http://localhost:8080/api/auth/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                email: email,
                password: password
            })
        });

        if (response.ok) {
            const data = await response.json();
            localStorage.setItem('authToken', data.token);
            localStorage.setItem('userId', data.id);
            window.location.href = '../html/MainPage.html';
        } else {
            const error = await response.json();
            alert(`Ошибка: ${error.message}`);
        }
    } catch (err) {
        alert('Ошибка сети: ' + err.message);
    }
});

document.getElementById('registerFormElement').addEventListener('submit', async function(e) {
    e.preventDefault();

    const email = document.getElementById('regEmail').value;
    const firstName = document.getElementById('regFirstName').value;
    const lastName = document.getElementById('regLastName').value;
    const password = document.getElementById('regPassword').value;
    const confirmPassword = document.getElementById('regConfirmPassword').value;

    if (password !== confirmPassword) {
        alert('Пароли не совпадают!');
        return;
    }

    try {
        const response = await fetch('http://localhost:8080/api/auth/register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                email: email,
                firstName: firstName,
                lastName: lastName,
                password: password,
                roles: ["DISPATCHER"]
            })
        });

        if (response.ok) {
            const data = await response.json();
            localStorage.setItem('authToken', data.token);
            window.location.href = '../html/MainPage.html';
        } else {
            const error = await response.json();
            alert(`Ошибка: ${error.message}`);
        }
    } catch (err) {
        alert('Ошибка сети: ' + err.message);
    }
});

document.querySelector('.plane-animation i').addEventListener('mouseover', function() {
    this.style.animationPlayState = 'paused';
});

document.querySelector('.plane-animation i').addEventListener('mouseout', function() {
    this.style.animationPlayState = 'running';
});
