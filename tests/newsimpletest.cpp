/* 
 * File:   newsimpletest.cpp
 * Author: malcolm
 *
 * Created on 19/06/2014, 06:02:48 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Disk_File.h"
/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << " Creando archivos" << std::endl;
    Disk_File* file1 = new Disk_File("AAAUsers", "users");
    Disk_File* file2 = new Disk_File("AAAUsers", "users2");
    std::cout << " Escribiendo registros" << std::endl;
    file1->setSchema("{{<username>,<Char-array>,<64>},{<password>,<Char-array>,<64>},{<id>,<Int>,<4>},{<admin>,<Byte>,<1>}}");
    file2->setSchema("{{<pathFile>,<Char-array>,<512>},{<userId>,<Int>,<4>},{<owner>,<Byte>,<1>}}");
    file1->addReg("{{<username>,<Gonzo>},{<password>,<heloo132*>},{<id>,<1>},{<admin>,<1>}}");
    file2->addReg("{{<username>,<Yoda>},{<password>,<y0ur3Next@>},{<id>,<2>},{<admin>,<1>}}");
}

void test2() {
    std::cout << "newsimpletest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

