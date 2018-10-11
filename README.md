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

Since there are two main components to our project, we present their building instructions separately. The first component is a local desktop application written in C, and as such has very specific instructions for compilation and execution. The second is a Web application encased in a Docker image, and as such should be straightforward to setup and use.

### FEUP-8 fantasy console

#### Windows
##### with Visual Studio 2017
- install `Visual Studio 2017`
- install `git`
- run following commands in `cmd`
```
git clone --recursive https://gitlab.com/ldso18-19/t5g2
cd t5g2/FEUP-8
cmake -G "Visual Studio 15 2017 Win64"
```
- open `TIC-80.sln` and build
- enjoy :)

##### with MinGW
- install `mingw-w64` (http://mingw-w64.org) and add `.../mingw/bin` path to the *System Variables Path*
- install `git`
- install `cmake` (https://cmake.org)
- run following commands in `terminal`
```
git clone --recursive https://gitlab.com/ldso18-19/t5g2
cd t5g2/FEUP-8
cmake -G "MinGW Makefiles"
mingw32-make -j4
```

#### Linux (Ubuntu 14.04)
run the following commands in the Terminal
```
sudo apt-get install git cmake libgtk-3-dev libgles1-mesa-dev libglu-dev -y
git clone --recursive https://gitlab.com/ldso18-19/t5g2 && cd t5g2/FEUP-8
cmake . && make -j4
```

to install the latest CMake:
```
wget "https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh"
sudo sh cmake-3.12.0-Linux-x86_64.sh --skip-license --prefix=/usr
```

#### Mac
install `Command Line Tools for Xcode` and `brew` package manager

run the following commands in the Terminal
```
brew install git cmake
git clone --recursive https://gitlab.com/ldso18-19/t5g2
cd t5g2/FEUP-8
cmake . && make -j4
```

### FEUP-8 Website

#### To run the website locally:

* 1st Time:

```
git clone --recursive https://gitlab.com/ldso18-19/t5g2.git
cd t5g2/Website
composer install
php artisan serve
```

* After the first time, simply run:

```
php artisan serve
```

#### To push to docker:

```
docker build nadiacarvalho/ldso-t5g2 .
docker push nadiacarvalho/ldso-t5g2:latest
```

#### To run the integrated website via docker:

```
docker pull nadiacarvalho/ldso-t5g2
docker run --rm -d -p 8000:8000/tcp nadiacarvalho/ldso-t5g2:latest
```


## Related Projects

Please refer to our Wiki page on [market analysis](https://gitlab.com/ldso18-19/t5g2/wikis/Market-analysis) to know more about other projects similar to FEUP-8.


## License

Licensed under the [MIT](LICENSE) License.
