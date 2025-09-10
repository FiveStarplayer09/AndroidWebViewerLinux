# AndroidWebViewerLinux
AndroidWebViewerLinux

**Wellcome:** This Project created **using VS 2022** and **C++** and **QT** lib...


# Android Web Viewer for Linux

This project is a simple, lightweight web browser built with C++ and the Qt framework. It is designed to mimic an Android browser's user agent and behavior, allowing users to view the mobile version of websites on a Linux desktop.

This repository contains the source code originally developed in Visual Studio 2022, now adapted for building on a Linux environment.

## Features

- **Android User Agent Spoofing**: Identifies itself as a Google Pixel 7 to receive mobile-optimized web pages.
- **Advanced Fingerprint Spoofing**: Uses JavaScript injection to mask browser properties like `navigator.platform`, `webdriver`, etc., to minimize bot detection.
- **Touch-like Scrolling**: Implements kinetic scrolling, allowing users to scroll by clicking and dragging, similar to a touch device.
- **Persistent Data**: Saves cookies and session data to provide a consistent browsing experience and avoid repeated CAPTCHAs.

## How to Build a `.deb` Package from this Source Code

These instructions are for a Debian-based Linux environment, such as Ubuntu. You can easily build the project using a cloud environment like GitHub Codespaces.

### Step 1: Set Up the Environment

First, you need to install the necessary tools and Qt6 libraries. Open a terminal and run the following commands:

```bash
# Update package list and install build tools
sudo apt-get update
sudo apt-get install -y build-essential libgl1-mesa-dev

# Install required Qt6 development packages
sudo apt-get install -y qt6-base-dev qt6-webengine-dev
```

### Step 2: Compile the Application

Once the environment is set up, you can compile the source code using `qmake6` and `make`.

```bash
# Generate the Makefile from the .pro file
qmake6 FiveStarPlayerVS.pro

# Compile the source code using all available CPU cores
make -j$(nproc)
```

After a successful compilation, an executable file named `FiveStarPlayerVS` will be created in the project directory.

### Step 3: Create the `.deb` Package

Now, we will package the compiled application into a `.deb` installer file.

```bash
# 1. Create the necessary directory structure
mkdir -p my-app-package/DEBIAN
mkdir -p my-app-package/usr/local/bin
mkdir -p my-app-package/usr/share/applications

# 2. Copy the executable to the correct location
cp FiveStarPlayerVS my-app-package/usr/local/bin/

# 3. Create the control file with package metadata
cat <<EOF > my-app-package/DEBIAN/control
Package: fivestarplayer
Version: 1.0.0
Section: web
Priority: optional
Architecture: amd64
Depends: libqt6core6, libqt6gui6, libqt6widgets6, libqt6webenginewidgets6
Maintainer: Your Name <youremail@example.com>
Description: Android Web Viewer
 A simple browser that mimics an Android device for web browsing.
EOF

# 4. Create a .desktop file for the application menu shortcut
cat <<EOF > my-app-package/usr/share/applications/fivestarplayer.desktop
[Desktop Entry]
Version=1.0
Name=Android Web Viewer
Comment=Browse websites with an Android-like experience
Exec=/usr/local/bin/FiveStarPlayerVS
Icon=utilities-terminal
Terminal=false
Type=Application
Categories=Network;WebBrowser;
EOF

# 5. Set the correct permissions for the DEBIAN directory
chmod 755 my-app-package/DEBIAN

# 6. Build the final .deb package
dpkg-deb --build my-app-package
```

After these steps, a file named `my-app-package.deb` will be created. You can download this file and install it on any Ubuntu/Debian-based system.

### How to Install

To install the package on a Linux machine, copy the `.deb` file to it, open a terminal, navigate to the file's location, and run:

```bash
sudo apt install ./my-app-package.deb
```


Github માં સેવ કરવા માટે:

0. જો .gitignore` ફાઇલ ન હોય તો     `touch .gitignore` બનાવો:
    ```bash
    touch .gitignore
    ```


1.  **બધા ફેરફારોને સેવ લિસ્ટમાં ઉમેરો** (આ વખતે `README.md` માટે):
    ```bash
    git add .
    ```
2.  **ફેરફારોનું વર્ણન કરો:**
    ```bash
    git commit -m "Update README.md with build instructions"
    ```
3.  **બધું જ GitHub પર મોકલી દો:**
    ```bash
    git push
    ```

હવે તમારી GitHub રિપોઝિટરી સંપૂર્ણપણે તૈયાર, અપડેટેડ અને ખૂબ જ વ્યાવસાયિક દેખાશે