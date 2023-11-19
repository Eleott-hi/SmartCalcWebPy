const { app, BrowserWindow } = require('electron');
const { spawn } = require('child_process');

function createWindow() {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
    },
  });

//   // Start Django server
  // const djangoProcess = spawn('python', ['manage.py', 'runserver']);
  const djangoProcess = spawn('docker', ['manage.py', 'runserver']);

//   // Handle Django server output
//   djangoProcess.stdout.on('data', (data) => {
//     console.log(`Django Server: ${data}`);
//   });

//   djangoProcess.stderr.on('data', (data) => {
//     console.error(`Django Server Error: ${data}`);
//   });

  // Load your Django server URL in Electron app
  win.loadURL('http://localhost:8000'); // Change the port if your Django server is running on a different port

  // Open the DevTools.
  win.webContents.openDevTools();

  // Event handler for when the window is closed.
//   win.on('closed', () => {
//     // Stop the Django server when the Electron app is closed.
//     djangoProcess.kill();
//     app.quit();
//   });
}

app.whenReady().then(createWindow);

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
