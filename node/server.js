const express = require('express');
const { createProxyMiddleware } = require('http-proxy-middleware');
const path = require('path');

const app = express();
const PORT = 3000;

// Middleware
app.use(express.static(path.join(__dirname, 'public')));

// Proxy
app.use('/api', createProxyMiddleware({
    target: process.env.API_BASE_URL,
    changeOrigin: true,
    pathRewrite: { '^/api': '' }
}));

// All other routes
app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'html', 'MainPage.html'));
});

// Start server
app.listen(PORT, '0.0.0.0', () => {
    console.log(`Server running on http://localhost:${PORT}`);
    console.log(`Proxying API requests to: ${process.env.API_BASE_URL}`);
});