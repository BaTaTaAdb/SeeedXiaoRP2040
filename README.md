# CANHELP DOCUMENTATION

---

## 🚀 Introduction
This README provides guidance on setting up the Arduino-Pico board with the PlatformIO plugin in VSCode, specifically for boards not officially supported by PlatformIO.

## 📋 Prerequisites
- Visual Studio Code

## ⚙️ Installation Steps

### 1️⃣ Install PlatformIO in VSCode
- Open VSCode.
- Navigate to Extensions and search for "PlatformIO".
- Install the PlatformIO IDE extension.

### 2️⃣ Configure Windows for Long Paths (Windows Users Only)
- Enable long paths in Git and Windows OS.
- Click Window key and type `gpedit.msc`, then press the Enter key. This launches the Local Group Policy Editor.
- Navigate to `Local Computer Policy > Computer Configuration > Administrative Templates > System > Filesystem`.
- Double click `Enable NTFS long paths`.
- Reboot your system after these changes.

![Enable NTFS long paths](https://www.microfocus.com/documentation/filr/filr-4/filr-desktop/graphics/enable_ntfs.png)

### 3️⃣ Clone the Repository
To get started with the CanHelp project, clone the repository using the following command:

```cmd
git clone https://github.com/BaTaTaAdb/CanHelp.git
```
