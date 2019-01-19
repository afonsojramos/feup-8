# FEUP-8 - Open Source 8-bit Game Development Platform

## Motivation

[PICO-8](https://www.lexaloffle.com/pico-8.php) is a fantasy console for making, sharing and playing tiny games and other computer programs. When you turn it on, the machine greets you with a shell for typing in Lua commands and provides simple built-in tools for creating your own cartridges.

This tool was used during 2018 to teach young programmers with ages ranging from 11 to 14 years old at University of Porto's Junior University, and for dynamizing game construction at Game Jams. However, PICO-8 is a paid platform; and for that reason during the [Software Development Laboratory](https://sigarra.up.pt/feup/en/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=281226) course we were tasked with presenting an open-source alternative, that also allows for better flexibility by being more suitable for education.

As such, we decided to implement a free open-source clone of PICO-8 adapted to our requirements. After conduction a [market analysis](https://gitlab.com/ldso18-19/t5g2/wikis/Market-analysis) we stumbled upon an open-source clone of PICO-8 already implemented, [TIC-80](https://github.com/nesbox/TIC-80/wiki), which we then decided to adapt and extend to our purposes, thus creating the FEUP-8 platform.

## Product vision

We expect to achieve a product that can be used in education of younger people as introduction to programming. The project will hopefully be used in the next iterations of FEUP's Junior University, replacing the aforementioned PICO-8, however with our work we believe that it can be used for more purposes as long as connected to education in the first contacts with programming.
Younger people will be attracted by the game itself and at the same time will be learning how to program in an introductory language like Lua.
Our product will have the advantage of being free and open source which allows everyone to use it and implement new features allowing it to improve over time.
In a most deep way our product will provide features beyond the TIC-80 educational resources, it will have a tests platform that allow teachers to make exercises and tests to it via a Web app. This way, younger developers can test his code to check if it is correct and receive feedback for it.

## Feedback

* Request a new feature on GitLab
* File a bug in [GitLab Issues](https://gitlab.com/ldso18-19/t5g2/issues).

## Development Team

This is being developed by the following team, feel free to contact any of us at any time.

| <img src="https://assets.gitlab-static.net/uploads/-/system/user/avatar/2846743/avatar.png" height="75px" width="75px"/>  | [`@afonsojramos`](https://github.com/afonsojramos)|        
<img src="https://assets.gitlab-static.net/uploads/-/system/user/avatar/2846741/avatar.png" height="75px" width="75px"/> | [`@NadiaCarvalho`](https://gitlab.com/NadiaCarvalho) | <img src="https://secure.gravatar.com/avatar/40f5ded910f5f5a744db1ad56887a46a?s=180&d=identicon" height="75px" width="75px"/>  | [`@up201503995`](https://gitlab.com/up201503995)| <img src="https://secure.gravatar.com/avatar/147062fb337b447edbe58d1a6c16f458?s=180&d=identicon"      height="75px" width="75px"/> | [`@tiagolascasas`](https://gitlab.com/tiagolascasas)
--|--|--|--|--|--|--|--|
| <img src="https://secure.gravatar.com/avatar/f492e5707cbf0fca0f3225e0fcdbf52b?s=180&d=identicon" height="75px" width="75px"/>  | [`@Lantaros`](https://gitlab.com/Lantaros)| <img src="https://secure.gravatar.com/avatar/8dacc894429b1c487a94acfbe447c078?s=180&d=identicon"      height="75px" width="75px"/> | [`@TrocaTudo95`](https://gitlab.com/TrocaTudo95) | <img src="https://secure.gravatar.com/avatar/b9f320d003766e6ab9e859c6364d7744?s=180&d=identicon" height="75px" width="75px"/>  | [`@up201504196`](https://gitlab.com/up201504196)| <img src="http://4sqday.com/wp-content/uploads/2012/07/Pointing_Finger.jpg"   height="75px" width="75px"/> | YOU

## Build instructions

Since there are two main components to our project, we present their building instructions separately.

### FEUP-8 fantasy console

Regardless of the OS, make sure that you are on the ```FEUP-8``` subfolder of the project during **every stage** of the following instructions.

#### Linux (Ubuntu 18.04.1 LTS)

Firstly, install CMake:
```
wget "https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh"
sudo sh cmake-3.12.0-Linux-x86_64.sh --skip-license --prefix=/usr
```

Then, run the following commands in the terminal
```
sudo apt-get install git cmake libgtk-3-dev libglvnd-dev:i386 libglvnd-dev libglu-dev lcov -y
git clone --recursive https://gitlab.com/ldso18-19/t5g2 && cd t5g2/FEUP-8
cmake . && make -j4
```

A binary executable will be generated in /bin.

After the initial install, simply run the ```build_and_run.sh``` script every time you want to compile and run.

These instructions, as said on the title, were only verified on Ubuntu 18.04.1 LTS. Other distros and versions may have slight differences in dependencies or package manager.

#### Mac

Firstly, install `Command Line Tools for Xcode` and `brew` package manager

Then, run the following commands in the Terminal
```
brew install git cmake
git clone --recursive https://gitlab.com/ldso18-19/t5g2
cd t5g2/FEUP-8
cmake . && make -j4
```

A binary executable will be generated in ```/bin```.

After the initial install, simply run the ```build_and_run_mac.sh``` script every time you want to compile and run.

#### Windows

Windows builds are no longer supported. The code coverage report generation required additional configuration of that build, and since Windows builds are not within the current scope of the project, we decided to deprecate it instead.

#### To run the tests and generate coverage report:

```
sh build_and_test.sh    # to run tests
sh run_coverage.sh      # to generate a coverage report
```

A coverage report will be generated in ```/tic80_coverage```.

#### To run the linter/automatic formatter:

```
sh lint.sh
```

If you don't have ```clang-format``` installed, the script will tell you in a friendly manner that you need to get it first.

On Ubuntu, this can be installed using ```sudo apt-get install clang-format```, though the package name may change in other distros or OS.

### FEUP-8 Website (Linux and Mac only)

Regardless of the OS, make sure that you are on the ```Website``` subfolder of the project during **every stage** of the following instructions.

#### To run the website locally:

Install the following dependencies using your distro's package manager. The following list has been validated using apt-get on Ubuntu 18.04.1 LTS, and it may differ slightly on other distros or OS. Install them one by one on this exact order to ensure maximal compatibility:

- php7.2
- php-xdebug
- composer
- php7.2-sqlite
- php7.2-mbstring
- php7.2-xml
- lua50
- luajit
- luarocks

Then, run the initial build:

```
git clone --recursive https://gitlab.com/ldso18-19/t5g2.git
cd t5g2/Website
sudo composer install   # use sudo only if you get permission errors, and only after you verify if you can't solve them with chmod
luarocks install luaunit
```

Now, you need to change the ```DB_DATABASE``` path in the ```.env``` file to the one on your local machine. Once that is done, run the following:

```
sudo sh setup.sh    # use sudo only if you get permission errors, and only after you verify if you can't solve them with chmod
php artisan serve
```

After the former first time setup, simply run:

```
php artisan serve
```

#### To run the unit tests and generate the coverage report:

```
sudo sh setup_tests.sh
vendor/bin/phpunit
```

A code coverage report will be generated on ```/report```.

#### To run the linter and automatic formatter:

```
sh lint.sh
```

## Run instructions

Using the generated release or the most recent stable version of [FEUP-8](https://gitlab.com/feup-tbs/ldso18-19/t5g2/uploads/718e827dc1a1ccfe8669afba9b5b37ac/feup8_release.zip) you can extract it

The following files should be generated:

* **libfeup8.so** - the application binary file
* **readme.txt** - some FEUP-8 important information
* **conf.ini** - since there are two main components to our project (client and server) the server address (ip or domain) and port must be specified in the client's configuration file. By default this is filled with the production server's values and needs to be altered to use another server. The protocol used is HTTP over TCP. 
* **FEUP-8.desktop** - FEUP-8 executable


## Web API Documentation 

The documentation  of the API that allows communication between the FEUP-8 app and the server can be found here:

**https://app.swaggerhub.com/apis-docs/dinisvale/LDSO/1.0.0**


## Related Projects

Please refer to our Wiki page on [market analysis](https://gitlab.com/ldso18-19/t5g2/wikis/Market-analysis) to know more about other projects similar to FEUP-8.


## License

Licensed under the [MIT](LICENSE) License.
