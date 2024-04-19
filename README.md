# astral ⭐

A dynamically-typed, single-pass, recursive descent interpreter without AST generation.

## Table of Contents

1. [Getting Started](#getting-started)
   1. [Docker](#docker)
   2. [Linux](#linux-builds)
      1. [Fedora / RHEL](#fedora--rhel)
      2. [Ubuntu / Debian](#ubuntu--debian)
      3. [Installing Astral on Linux](#installing-astral-on-linux)
   3. [Windows](#windows-builds)
   4. [Visual Studio Code Extension](#visual-studio-code-extension)
2. [Documentation](#documentation)
   1. [Astral Index](#astral-index)
   1. [Test Suite](#test-suite)
   2. [Code Examples](#code-examples)
      1. [Cellular Automata](#cellular-automata)
      2. [Project Euler](#project-euler)
      3. [Web Application](#web-application)
      4. [Temporary Script](#temporary-script)
3. [Contributions](#contributions)
4. [License](#license)

## Getting Started

To start using Astral, please follow the instructions below. 

### Docker

Experiment with Astral in a Docker container.

```bash
sudo docker build -t astral-lang .
sudo docker run -it -v $(pwd):/workspace astral-lang
```

### Linux Builds

To build Astral, use your favorite C++ compiler.

This repo uses GCC and Make.

#### Fedora / RHEL

```bash
sudo dnf update
sudo dnf install gcc-c++
sudo dnf install make
```

#### Ubuntu / Debian

```bash
sudo apt update
sudo apt-get install g++
sudo apt-get install make
```

Then build with Make.

```bash
make
```

#### Installing Astral on Linux

Clone and build Astral.  Run `sudo make install` to build Astral and run the installation script.

```bash
git clone https://github.com/fuseraft/astral.git
cd astral
sudo make install
```

### Windows Builds

You can find a 64-bit build (named **`astral.exe`**) in the latest release.

To build on Windows, you need to open a [64-bit hosted developer command prompt](https://learn.microsoft.com/en-us/cpp/build/how-to-enable-a-64-bit-visual-cpp-toolset-on-the-command-line?view=msvc-170).

Then navigate to the source code and run [`build.bat`](build.bat).

```cmd
cd path\to\astral
build.bat
```

*Note: The Windows build does not support `.⭐` files (use the `.star` extension).*

### Visual Studio Code Extension

You can install the [extension](https://marketplace.visualstudio.com/items?itemName=fuseraft.astral-lang) for syntax-highlighting in VS Code.

Launch VS Code Quick Open (<kbd>Ctrl</kbd>+<kbd>P</kbd>), paste the following command, and press enter.
```
ext install fuseraft.astral-lang
```

## Documentation

### Astral Index

You can find detailed information on language features in the [Astral Index](docs/README.md).

### Test Suite

Explore the [tests](tests/) directory for a collection of test scripts. 

To run the test suite, execute:

```shell
astral test
```

To build and run the test suite, execute:

```shell
make test
```

### Code Examples

#### Cellular Automata

- [Rule 30](examples/ca.⭐)
- [Conway's Game of Life](examples/life.⭐)

#### Project Euler

- [Project Euler examples](examples/project_euler/).

#### Web Application

Below is a simple HTTP web application. You can find the [example project here](examples/webapp/app.⭐).

```ruby
import "@astral/web" as web
import "@astral/fs" as fs

# HTML helpers
html = {
  "shared": fs.read("templates/shared.html"),
  "index": fs.read("templates/index.html"),
  "contact": fs.read("templates/contact.html")
}

# A simple template engine.
def build_html(data)
  return html.shared.replace("<%content%>", data)
end

# GET /
web.get(["/", "/index"], with (req) do
  return web.ok(build_html(html.index), "text/html")
end)

# GET /contact
web.get("/contact", with (req) do
  return web.ok(build_html(html.contact), "text/html")
end)

# POST /contact
web.post("/contact", with (req) do  
  println("Received content from client:\nbody: ${req.body}\nparams: ${req.params}")
  return web.redirect("/")
end)

# serve static content
web.public("/", "./public")

# server and port configuration
host = "0.0.0.0", port = 8080

# start the web server
println("Starting Astral Web Server at http://${host}:${port}")
web.listen(host, port)
```

#### Temporary Script

Below is a script that generates a temporary script and executes it.

```ruby
import "@astral/fs" as fs
import "@astral/math" as math
import "@astral/sys" as sys

try
  # Look for a temporary directory. Fail fast.
  if !fs.exists(fs.tmpdir())
    println("Could not find temporary directory.")
    exit(1)
  end
  
  # Generate a random temporary file path.
  filename = math.random("0123456789ABCDEF", 10)
  path = fs.combine(fs.tmpdir(), "${filename}.⭐")

  # Write a little ⭐ script.
  fs.write(path, "
    /#
    This script will delete itself and let you know it was there.
    #/
    import \"@astral/fs\" as fs
    fs.remove(\"${path}\")
    println(\"Astral was here running as ${fs.filename(path)}.\")
  ")

  # Run the ⭐ script.
  sys.exec("astral ${path}")
catch (err)
  println("An error occurred: ${err}")
end
```

## Contributions

I welcome and appreciate any and all contributions to the Astral project! Here's how you can contribute:

1. **Join the Discord**: [The Astral Programming Language](https://discord.com/channels/1221516965743431841/1221553678104920195)
2. **Fork the Repository**: Fork the project to your GitHub account.
3. **Clone the Forked Repository**: Clone it to your machine.
4. **Set Up Your Environment**: Follow the "Getting Started" section.
5. **Make Changes**: Implement your features or fixes.
6. **Test Your Changes**: Ensure all tests pass.
7. **Create a Pull Request**: Submit it from your fork to the main Astral repository.

For more details, please read [CONTRIBUTING.md](CONTRIBUTING.md).

## License

This project is licensed under the [MIT License](LICENSE).
