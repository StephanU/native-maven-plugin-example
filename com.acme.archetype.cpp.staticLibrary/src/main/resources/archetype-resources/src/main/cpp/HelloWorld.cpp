/*
 * TestClass.cpp
 *
 *  Created on: 21.09.2018
 *      Author: stephan
 */

#include <iostream>
#include "header/HelloWorld.hpp"

namespace StaticLib {

void HelloWorld::greet() {
	std::cout << "Hello, world!" << std::endl;
}

} /* namespace StaticLib */
