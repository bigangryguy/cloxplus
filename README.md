<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
    <h3 align="center">cloxplus</h3>
  <p align="center">
    C++ implementation of the Lox programming language
    <br />
    <a href="https://github.com/bigangryguy/cloxplus"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/bigangryguy/cloxplus/issues">Report Bug</a>
    ·
    <a href="https://github.com/bigangryguy/cloxplus/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project
A C++ implementation of the Lox programming language. This is an interpretation of the C implementation 
of clox in Section III of Bob Nystrom's site [Crafting Interpreters](https://craftinginterpreters.com/).

As the project grows, a standard library and new language features will be added. Expect this 
implementation to deviate from the original Lox specification in the future.


### Built With

* [{fmt}](https://fmt.dev/latest/index.html)
* [Catch2](https://github.com/catchorg/Catch2)


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps. The instructions assume you are on a
Linux or Unix-like system. I can verify this will work on macOS as well.

### Prerequisites

Cloxplus requires the {fmt} and Catch2 libraries to be installed and able to be found by cmake.
* {fmt} - Download and unzip the library first. You can follow the latest [instructions](https://fmt.dev/latest/usage.html) or try:
```shell script
$ cd fmt-7.0.3  # Change to the library directory
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make test
$ sudo make install
```
* Catch2 - Follow the latest [instructions](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository) or try:
```shell script
$ git clone https://github.com/catchorg/Catch2.git
$ cd Catch2
$ cmake -Bbuild -H. -DBUILD_TESTING=OFF
$ sudo cmake --build build/ --target install
```

### Installation

1. Clone the repo
```sh
git clone https://github.com/bigangryguy/cloxplus.git
```
2. Install prerequisites (see above)
3. Create your build files (run these commands in the cloxplus root directory)
```shell script
$ cmake -DCMAKE_BUILD_TYPE=Debug -G "YOUR_PREFERRED_IDE" PATH_TO_SOURCE
```



<!-- USAGE EXAMPLES -->
## Usage

For now, reference the Lox grammar [appendix](https://craftinginterpreters.com/appendix-i.html) on the 
Crafting Interpreters site. In the future, as cloxplus adds new features and forks from the original 
language specification, a full grammar reference will be included here.



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/bigangryguy/cloxplus/issues) for a list of proposed features 
(and known issues).

* Complete the virtual machine
* Implement the language


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

David Wilcox - [@davidtwilcox](https://twitter.com/davidtwilcox) - david@dtwil.co

Project Link: [https://github.com/bigangryguy/cloxplus](https://github.com/bigangryguy/cloxplus)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [Bob Nystrom](https://twitter.com/munificentbob) - Author of [Crafting Interpreters](https://craftinginterpreters.com/)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/bigangryguy/repo.svg?style=flat-square
[contributors-url]: https://github.com/bigangryguy/repo/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/bigangryguy/repo.svg?style=flat-square
[forks-url]: https://github.com/bigangryguy/repo/network/members
[stars-shield]: https://img.shields.io/github/stars/bigangryguy/repo.svg?style=flat-square
[stars-url]: https://github.com/bigangryguy/repo/stargazers
[issues-shield]: https://img.shields.io/github/issues/bigangryguy/repo.svg?style=flat-square
[issues-url]: https://github.com/bigangryguy/repo/issues
[license-shield]: https://img.shields.io/github/license/bigangryguy/repo.svg?style=flat-square
[license-url]: https://github.com/bigangryguy/repo/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/davidtwilcox
[product-screenshot]: images/screenshot.png
