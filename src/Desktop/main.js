const { app, BrowserWindow } = require('electron');
const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

let serverProcess;

const print_dir = (win) => {
    const files_fs = fs.readdirSync(__dirname);
    const files = fs.readdirSync('./');
    const managePath = path.resolve(__dirname);
    const here_dir = path.resolve('./');

    files.forEach((file) => {
        win.webContents.executeJavaScript(`console.log('File:', '${file}')`);
    });

    files.files_fs((file) => {
        win.webContents.executeJavaScript(`console.log('File fs:', '${file}')`);
    });

    win.webContents.executeJavaScript(`console.log('Path --dirname:', '${managePath}')`);
    win.webContents.executeJavaScript(`console.log('Path ./:', '${here_dir}')`);
};

const server_up = (win) => {
    const managePath = path.resolve(__dirname, '..');
    const command = managePath + '/manage/manage'

    console.log('Manage Path:', command);
    win.webContents.executeJavaScript(`console.log('Manage Path:', '${command}')`);

    serverProcess = spawn(
        command,
        ['runserver', 'localhost:8000', '--noreload'],
    );

    serverProcess.stdout.on('data', (data) => { console.log(`Server stdout: ${data}`); });
    serverProcess.stderr.on('data', (data) => { console.error(`Server stderr: ${data}`); });
    serverProcess.on('close', (code) => { console.log(`Server process exited with code ${code}`); });
};

const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 600
    });

    server_up(win);

    setTimeout(() => {
        // win.loadFile('index.html');
        // print_dir(win);
        win.loadURL('http://localhost:8000');
        // win.webContents.openDevTools();

    }, 3000)

};

app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });

    app.on('before-quit', () => {
        if (serverProcess) {
            serverProcess.kill('SIGTERM');
        }
    });
});

app.on('window-all-closed', () => {
    app.quit();
});
