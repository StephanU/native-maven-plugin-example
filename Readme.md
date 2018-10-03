# native-maven-plugin-example

Simple example showing one possibility to use the [Native Maven Plugin](https://www.mojohaus.org/maven-native/native-maven-plugin/) to build and deploy C++ static libraries (including header files) to a Maven repository and build and deploy C++ executables (having dependencies to deployed static libraries).

The project provides three Maven parent pom's.
- A parent pom for the generic configuration of the Native Maven Plugin.
- A parent pom with specific configurations for building static libraries.
- A parent pom with specific configurations for building executables.

Additionally, two Maven archetypes are provided:
- com.acme.archetype.cpp:staticLibrary:0.0.1-SNAPSHOT to easily create a project for a static library
- com.acme.archetype.cpp:executable:0.0.1-SNAPSHOT to easily create a project for an executable

## Usage

### Install the parent pom's and the archetypes

1.  Clone this repository.
2.  Install the parent pom for the generic Native Maven Plugin configuration:
    ```
    cd com.acme.mavenmaster.cpp
    mvn install
    ```
3.  Install the parent pom with specific configurations for building static libraries:
    ```
    cd ../com.acme.mavenmaster.cpp.static
    mvn install
    ```
4.  Install the parent pom with specific configurations for building executables:
    ```
    cd ../com.acme.mavenmaster.cpp.executable
    mvn install
    ```
5.  Install the archetype for static libraries
    ```
    cd ../com.acme.archetype.cpp.staticLibrary
    mvn install
    ```
6.  Install the archetype for executables
    ```
    cd ../com.acme.archetype.cpp.executables
    mvn install
    ```

### Create an exectuable project using the executable archetype
The executable archetype is a basic skeleton for a C++ project to build an executable (tested on Linux and OSX) using the created parent pom's. The archetype provides a main function which prints out "Hello, world!".

1.  Create a new Maven project using the exectuable archetype
    ```
    mvn archetype:generate -DarchetypeGroupId=com.acme.archetype.cpp -DarchetypeArtifactId=executable -DarchetypeVersion=0.0.1-SNAPSHOT -DgroupId=com.acme.app -DartifactId=HelloWord -Dversion=0.0.1-SNAPSHOT
    ```
2.  Compile and execute the project:
    ```
    cd HelloWord
    mvn compile
    ```
    You should find the executable in the target folder of your project. Try it out:
    ```
    ./target/HelloWord.uexe 
    Hello, world!
    ```

Congratulations! You have just executed your first C++ program which was build using the Native Maven Plugin. ;)

### Create a static library project using the static library archetype
The static library archetype is a basic skeleton for a C++ project to build a static library using the created parent pom's. The archetype provides a class `HelloWorld`.

1.  Create a new Maven project using the static library archetype
    ```
    mvn archetype:generate -DarchetypeGroupId=com.acme.archetype.cpp -DarchetypeArtifactId=staticLibrary -DarchetypeVersion=0.0.1-SNAPSHOT -DgroupId=com.acme.app -DartifactId=libGreetingsEarhtlings -Dversion=0.0.1-SNAPSHOT
    ```
2.  Install the new static library to your local Maven repository:
    ```
    cd libGreetingsEarhtlings
    mvn install
    ```
    You should find the static library (.a file) and a .inczip file (which contains the header provided by the static library) in you local Maven repository.
    ```
    > ls -la ~/.m2/com/acme/app/libGreetingsEarthlings/0.0.1-SNAPSHOT/
    total 64
    drwxr-xr-x  7 stephan  staff    224  3 Okt 05:56 .
    <drwxr-xr-x  4 stephan  staff    128  3 Okt 05:56 ..
    -rw-r--r--  1 stephan  staff    274  3 Okt 05:56 _remote.repositories
    -rw-r--r--  1 stephan  staff  16040  3 Okt 05:56 libGreetingsEarthlings-0.0.1-SNAPSHOT.a
    -rw-r--r--  1 stephan  staff    266  3 Okt 05:56 libGreetingsEarthlings-0.0.1-SNAPSHOT.inczip
    -rw-r--r--  1 stephan  staff    815  3 Okt 05:52 libGreetingsEarthlings-0.0.1-SNAPSHOT.pom
    -rw-r--r--  1 stephan  staff    885  3 Okt 05:56 maven-metadata-local.xml
    ```

Congratulations! You have just deployed your first static library which was build using the Native Maven Plugin. ;) Now let's use that static library in our HelloWorld program.

### Modify the HelloWorld project to use the deployed static library

1.  Edit HelloWorld/pom.xml and add the following dependencies block (somewhere within the < project > tag):
    ```
    <dependencies>
      <dependency>
        <groupId>com.acme.app</groupId>
        <artifactId>libGreetingsEarthlings</artifactId>
        <version>0.0.1-SNAPSHOT</version>
        <type>inczip</type>
        <scope>compile</scope>
      </dependency>
      <dependency>
        <groupId>com.acme.app</groupId>
        <artifactId>libGreetingsEarthlings</artifactId>
        <version>0.0.1-SNAPSHOT</version>
        <type>a</type>
        <scope>compile</scope>
      </dependency>
    </dependencies>
    ```
    Note: You need to add a dependency to both the .inczip file which contains the headers provided by the static library (needed for compilation) and to the .a file (needed for linking). Maybe there is some other way to fetch both dependencies by defining just one dependency block, but I don't know it.
2.  Modify the main.cpp file of the HelloWorld project:
    ```
    #include <iostream>
    #include "HelloWorld.hpp"

    int main() {
      std::cout << "Hello, world!" << std::endl;

      HelloWorld helloWorld;
      helloWorld.greet();
    }
    ```
3.  Compile and execute the project:
    ```
    cd HelloWord
    mvn compile
    ./target/HelloWord.uexe 
    Hello, world!
    Greetings, earthlings!
    ```

Congratulations! You have just used a deployed static library. ;)
