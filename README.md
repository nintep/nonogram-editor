<h1 align="center">
  <br>
  Nonogram Editor
  <br>
</h1>

<h4 align="center">A desktop tool for creating and solving nonogram puzzles.</h4>

<p align="center">
  <img src="https://img.shields.io/badge/CMake-3.22.1-blue" 
         alt="C++">
  <img src="https://img.shields.io/badge/QT-5-green"
         alt="C++">
</p>

<p align="center">
  <a href="#features">Features</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#license">License</a>
</p>

![screenshot](/images/header.gif)

## Features

### Edit Mode

* Create and edit nonograms of various sizes
* Nonogram clues are calculated automatically
* Save nonograms for future editing

### Solve Mode

* Solve existing nonograms
* Solutions are checked automatically

## How To Use
To use Nonogram Editor, you will need to have [CMake](https://cmake.org/download/) and [QT](https://www.qt.io/download-open-source) installed. To build and run the application, run the following commands:

```bash
# Clone the repository
$ git clone https://github.com/nintep/nonogram-editor

# Go into the repository
$ cd nonogram-editor

# Create and enter build directory
$ mkdir build
$ cd build

# Build the application
$ cmake ..
$ make

# Run the application
$ ./nonogram-editor
```
## License

GNU General Public License v3.0

---

[Project Github](https://github.com/nintep/nonogram-editor)