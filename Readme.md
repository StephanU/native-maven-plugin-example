# native-maven-plugin-example

Simple example showing one possibility to use the (Native Maven Plugin|https://www.mojohaus.org/maven-native/native-maven-plugin/) to build and deploy C++ static libraries (including header files) to a Maven repository and build and deploy C++ executables (having dependencies to deployed static libraries).

The project provides three Maven parent pom's.
- A parent pom for the generic configuration of the Native Maven Plugin: com.acme.mavenmaster.cpp:mavenmaster:0.0.1-SNAPSHOT
- A parent pom with specific configurations for building static libraries: com.acme.mavenmaster.cpp.staticLibrary:mavenmaster:0.0.1-SNAPSHOT
- A parent pom with specific configurations for building executables: com.acme.mavenmaster.cpp.executable:mavenmaster:0.0.1-SNAPSHOT

Additionally, two Maven archetypes are provided:
- com.acme.archetype.cpp:staticLibrary:0.0.1-SNAPSHOT to easily create a project for a static library
- com.acme.archetype.cpp:executable:0.0.1-SNAPSHOT to easily create a project for a executable