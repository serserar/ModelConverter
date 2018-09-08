/*
 * File:   main.cpp
 * Author: serserar
 *
 * Created on February 21, 2016, 2:02 AM
 */

#include "ModelSamplerApp.h"
#include <regex>


void generateSamples(){
    ModelSamplerApp modelSamplerApp("../samples", "../samples/test-out", "samples-test.xml");
    modelSamplerApp.Run();
}

int main(int argc, char** argv) {
    generateSamples();
    return 0;
}

