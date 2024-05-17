#!/bin/bash

function info(){
    echo "Running Configuration: " $1
    echo $CI_PROJECT_DIR
    echo $CI_COMMIT_TAG
}

function build() {
    rm -rf build
    mkdir -p build
    cd build || exit 1
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
    clang-tidy ../src/*.cpp
    cmake --build . --config Release -j $(nproc)
}

function release() {
    rm -rf build
    mkdir -p build
    cd build || exit 1

    cmake .. -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
    cmake --build . --config Release -j $(nproc)

    ls -lah
    ls -lah ./bin/

    zip -j -r $CI_PROJECT_DIR/athena-release-$CI_COMMIT_TAG.zip $CI_PROJECT_DIR/build/bin/Athena

    echo "BUILD_JOB_ID="$CI_JOB_ID >> $CI_PROJECT_DIR/build.env
}

if [ $1 == "Release" ]; then
    info
    release
fi

if [ $1 == "Build-Only" ]; then
    info
    build
fi
