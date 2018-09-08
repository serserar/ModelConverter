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

void generateDataSet(){
    vector<string> modelsPath;
    vector<string> skeletonsPath;
    std::regex model_regex("(\\model_)");
    std::regex skeleton_regex("(\\skeleton_)");
    string sourcePath = "../samples/out";
}

int main(int argc, char** argv) {
    generateSamples();
    //generateDataSet();
    return 0;
}

