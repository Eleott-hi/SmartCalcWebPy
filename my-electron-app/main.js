const { app, BrowserWindow } = require('electron');
const { spawn } = require('child_process');

function startDjangoServer() {
  // Use spawn to run the Django server start command
  const serverProcess = spawn('make', { cwd: '../src' });

  // Log server output to the console
  serverProcess.stdout.on('data', (data) => {
    console.log(`Django Server output: ${data}`);
  });

  // Log server errors to the console
  serverProcess.stderr.on('data', (data) => {
    console.error(`Django Server error: ${data}`);
  });

  // Log when the server process closes
  serverProcess.on('close', (code) => {
    console.log(`Django Server process exited with code ${code}`);
  });

  return serverProcess;
}

function createWindow() {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true
    }
  });

  win.loadURL('http://localhost:8000/');
}

app.whenReady().then(() => {
  const serverProcess = startDjangoServer();

  serverProcess.stdout.on('data', (data) => {
    if (data.includes('Starting development server at http://127.0.0.1:8000/')) {
      createWindow();
    }
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
