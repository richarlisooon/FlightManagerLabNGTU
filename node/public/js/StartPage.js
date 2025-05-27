document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('loginFormElement').addEventListener('submit', async function(e) {
        e.preventDefault();
        await handleLogin();
    });

    document.getElementById('registerFormElement').addEventListener('submit', async function(e) {
        e.preventDefault();
        await handleRegister();
    });
});

function showLoginForm() {
    document.getElementById('mainContent').style.display = 'none';
    document.getElementById('registerForm').style.display = 'none';
    document.getElementById('loginForm').style.display = 'flex';
}

function showRegisterForm() {
    document.getElementById('mainContent').style.display = 'none';
    document.getElementById('loginForm').style.display = 'none';
    document.getElementById('registerForm').style.display = 'flex';
}

function showMainContent() {
    document.getElementById('loginForm').style.display = 'none';
    document.getElementById('registerForm').style.display = 'none';
    document.getElementById('mainContent').style.display = 'flex';
}

async function handleLogin() {
    const email = document.getElementById('loginEmail').value;
    const password = document.getElementById('loginPassword').value;

    try {
        const response = await fetch('http://localhost:8080/api/auth/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ email, password })
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        const data = await response.json();
        localStorage.setItem('authToken', data.token);
        localStorage.setItem('userId', data.id);
        window.location.href = '/html/MainPage.html';

    } catch (error) {
        console.error('Login error:', error);
        alert('Login failed: ' + error.message);
    }
}

async function handleRegister() {
    const email = document.getElementById('regEmail').value;
    const firstName = document.getElementById('regFirstName').value;
    const lastName = document.getElementById('regLastName').value;
    const password = document.getElementById('regPassword').value;
    const confirmPassword = document.getElementById('regConfirmPassword').value;

    if (password !== confirmPassword) {
        alert('Passwords do not match!');
        return;
    }

    try {
        const response = await fetch('http://localhost:8080/api/auth/register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                email,
                firstName,
                lastName,
                password
            })
        });

        if (!response.ok) {
            const errorMessage = await response.text();
            throw new Error(errorMessage);
        }

        alert('Registration successful! Please login with your credentials.');
        showLoginForm();

    } catch (error) {
        console.error('Registration error:', error);
        alert('Registration failed: ' + error.message);
    }
}

document.querySelector('.plane-animation i').addEventListener('mouseover', function() {
    this.style.animationPlayState = 'paused';
});

document.querySelector('.plane-animation i').addEventListener('mouseout', function() {
    this.style.animationPlayState = 'running';
});
